#include <iostream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <mutex>
#include <atomic>
#include <list>
#include <thread>
#include "GUI.hpp"
#define CHUNK_SIZE 65536
#define MAXRECV 1000

int     recv_image(int recv_sock, unsigned char *pixels, uint32_t size)
{
    unsigned char buf[PIXEL_BUFSIZE];  //10Kb fixed-size buffer
    unsigned char buffer[MAXRECV];  //temporary buffer

    unsigned char* temp_buf = buf;
    unsigned char* end_buf = buf + sizeof(buf);
    int iByteCount = 0;
    int sum = 0;
    do
    {       
        iByteCount = recv(recv_sock, buffer,MAXRECV,0);   
        sum += iByteCount;
        if ( iByteCount > 0 )
        {
            //make sure we're not about to go over the end of the buffer
            if (!((temp_buf + iByteCount) <= end_buf))
                break;

            printf("Bytes received: %d\n",iByteCount);
            memcpy(temp_buf, buffer, iByteCount);
            temp_buf += iByteCount;
        }
        else if ( iByteCount == 0 )
        {

            memcpy(pixels, buf, PIXEL_BUFSIZE);
            break;

        }
        else
        {
            fprintf(stderr, "recv failed: ");
            break;
        }
    } while(iByteCount > 0 && temp_buf < end_buf);  //check for end of buffer
    printf("%d\n", sum);
    // int send_rc;

    // while (size > 0)
    // {
    //     send_rc = send(recv_sock, data, size, 0);
    //     if (send_rc == -1)
    //         break;

    //     size -= send_rc;
    //     data += send_rc;
    //     printf("Bytes sent: %d\n", send_rc);
    // }   /* End While Loop */
    // return (0);



}


// void	run_client(std::mutex &p_mutex, std::list<t_raytrace_data> &filenames, std::atomic<bool> &isRunning)
void     run_client(const char *ipAddress, 
                    std::mutex &recv_mutex,
                    std::list<t_raytrace_data> &updates,
                    std::atomic<bool> &isRunning,
                    std::atomic<bool> &imageLoaded,
                    uint32_t *shared_pixels)
{
    // std::string ipAddress = std::string(ipaddr);     // Server ip Address
    int port = 54000;                        // Listening port # on the server

    // Init socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        std::cerr << "Can't create socket, ERRNO #" << errno;
        isRunning = false;
        return ;
    }

    // Fill in a hint structure
    struct sockaddr_in hint;
    hint.sin_addr.s_addr = INADDR_ANY;
    hint.sin_port = htons( port );
    hint.sin_family = AF_INET;
    inet_pton(AF_INET, ipAddress, &hint.sin_addr);

    // Connect to server
    int connResult = connect(sock, (sockaddr *)&hint, sizeof(hint));
    if (connResult == -1)
    {
        std::cerr << "Can't connect to server, ERRNO #" << errno << std::endl;
        close(sock);
        isRunning = false;
        return ;
    }

    // Do-while loop to send and receive data
    
    // char buf[buffsize];

    while (isRunning)
    {
        if (!updates.empty())   // Make sure the user has typed in something
        {
            int sendResult = send(sock, &(updates.back()), sizeof(t_raytrace_data), 0);
            if (sendResult != -1)
            {
                uint32_t *pxl_copy = shared_pixels;
                std::lock_guard<std::mutex> lock(recv_mutex);
                recv_image(sock, (unsigned char *)shared_pixels, PIXEL_BUFSIZE);
                imageLoaded = true;
                updates.pop_back();
            }
        }
    }
    
    close(sock);
    return ;
}


int main()
{
	std::mutex l_mutex;
	std::list<t_raytrace_data> updates;
	std::atomic<bool> isRunning;
	std::atomic<bool> imageLoaded;
	uint32_t			shared_pixels[500*500];
	GUI gui;
	
	isRunning = true;
	imageLoaded = false;
	gui.setPixels(shared_pixels);
	std::thread clientThread
	( &run_client
		, "127.0.0.1"
		, std::ref(l_mutex)
		, std::ref(updates)
		, std::ref(isRunning)
		, std::ref(imageLoaded)
		, std::ref(shared_pixels)
	);
    
    while (true)
    {
        t_raytrace_data trd;
        for (int i = 0; i < 100; i++)
        {
            updates.push_back(trd);
            sleep(10); 
        }
    }
}