#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include "libft.h"

int     run_server2()
{
    uint16_t            port = 54000;
    
	// Create a socket
    int serv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(serv_socket == -1) return errno;

	// Bind  an ip address and port to the socket
    struct sockaddr_in  hint;
    hint.sin_addr.s_addr = INADDR_ANY;
    hint.sin_port = htons( port );
    hint.sin_family = AF_INET;
    if(bind(serv_socket,(struct sockaddr *)&hint , sizeof(hint)) < 0) return errno;
    
	// Tell the socker is for listening
    if(listen(serv_socket, SOMAXCONN) < 0)return errno;

	// Wait for a connection
    struct sockaddr_in  client;
    int client_size = sizeof(client);
    int client_socket = accept(serv_socket, (struct sockaddr *)&client, (socklen_t *)&client_size);

    if(client_socket == -1) return errno;

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    ft_memset(host, 0 , NI_MAXHOST);
    ft_memset(service, 0 , NI_MAXSERV);

    if (getnameinfo((struct sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        printf("%s connected on port %s\n", host, service);
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        printf("%s connected on port %d", host, ntohs(client.sin_port));
    }
	// Close listening socker
    close(serv_socket);

	// While loop: accept and eco message back to client
    char buf[4096];

    while (1)
    {
        ft_memset(buf, 0 , 4096);

        // Wait for client to send data
        int byte_received = recv(client_socket, buf, 4096, 0);

        if (byte_received == -1)
        {
            printf("Error in recv(). Quitting\n");
            break;
        }

        if (byte_received == 0)
        {
            printf("Client disconnected\n");
            break;
        }

        // RT

        // Return data back to client
        send(client_socket, buf, byte_received + 1, 0);
    }

	close(client_socket);
    return (0);
}