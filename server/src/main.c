/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 17:36:52 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/20 18:03:49 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>

#define MAX_FD 32

void print_image(Uint32 *pixels)
{
	int counter = 0;

	for (int i = 0; i < WIN_HEIGHT; i++)
	{
		for (int j = 0; j < WIN_WIDTH; j++)
		{
			printf("%d ", pixels[counter]);
			counter++;

		}
		printf("\n");
	}
}

void	ft_freedata(t_rt *rt)
{
	int	i;

	i = -1;
	while (++i < TEXTURES_COUNT)
		SDL_FreeSurface(rt->texture[i]);
	rt_clean(rt);
}

int     send_image(int server_sock, void *data, uint32_t size)
{
    // print_image(data);
    int send_rc;
    int sum = 0;
    while (size > 0)
    {
        send_rc = send(server_sock, data, 1000, 0);
        if (send_rc == -1)
            break;

        size -= send_rc;
        data += send_rc;
        // printf("Bytes sent: %d\n", send_rc);
        sum += send_rc;
    }   /* End While Loop */
    printf("Total bytes sent: %d\n", sum);
    return (0);
}

int     run_server()
{
    uint16_t            port = 54000;
    
	// Create a socket
    int listening_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(listening_sock == -1) return errno;

	// Bind  an ip address and port to the socket
    struct sockaddr_in  hint;
    hint.sin_addr.s_addr = INADDR_ANY;
    hint.sin_port = htons( port );
    hint.sin_family = AF_INET;
    if(bind(listening_sock,(struct sockaddr *)&hint , sizeof(hint)) < 0) return errno;
    
	// Tell the socker is for listening
    if(listen(listening_sock, SOMAXCONN) < 0)return errno;

    fd_set master;
    FD_ZERO(&master);
    FD_SET(listening_sock, &master);

    // t_rt	*rt = (t_rt *)malloc(sizeof(t_rt) * MAX_FD);
    t_rt rt[MAX_FD];
	while (true)
    {
        fd_set copy = master;
        int socketCount = select(MAX_FD, &copy, NULL, NULL, NULL);
        if (socketCount < 0)
        {
            printf("Error occured. Serever stops!\n");
            break;
        }
        else
        {
            printf("Socket count: %d\n", socketCount);
        }
        
        for (int i = 1; i <= MAX_FD; i++)
        {
            if (FD_ISSET(i, &copy))
            {
                int sock = i;
                if (sock == listening_sock)
                {
                    // Accept a new connection
                    int client = accept(listening_sock, NULL, NULL);
                    printf("Client connected! Sock: %d; i: %d; cleint: %d\n", sock, i, client);
                    // Add the new cnnection to the list of connected clients
                    FD_SET(client, &master);

                    // Init RT struct for new connection
                    if (!rt_parse_file(&(rt[client - 1]), "../scenes/pretty_room.json") || !load_textures(&(rt[client - 1])))
                        return -1;
                    if (!(rt[client - 1].pixels = (Uint32 *)malloc(WIN_WIDTH * WIN_HEIGHT * sizeof(Uint32))))
                    {
                        printf("Low memory\n");
                    }
                    check_light(&(rt[client - 1].lights));	// chec light
                    // neg_obj(&(rt[client - 1].objs));

                    // printf("Client connected! Sock: %d; i: %d; cleint: %d\n", sock, i, client);
                }
                else
                {
                    printf("Client speaks! Sock: %d; i: %d;\n", sock, i);
                    char buf[4096];
                    ft_memset(buf, 0 , 36);

                    // Wait for client to send data
                    int byte_received = recv(sock, buf, 36, 0);
                    if (byte_received <= 0)
                    {   
                        FD_CLR(sock, &master);
                        // Drop the client
                        shutdown(sock, 0);
                        close(sock);
                        
                        printf("Closed connection with client at socket %d.\n", sock);
                        ft_freedata(&(rt[sock - 1]));
                        free(rt[sock - 1].pixels);

                    }
                    else if (byte_received == 36)
                    {
                        t_raytrace_data flags_buf;
                        memcpy(&flags_buf, buf, 36);
                        
                        rt_thread_tracer(&(rt[sock - 1]));
                        visual_effects(rt + sock - 1, &flags_buf);
                        send_image(sock, rt[sock - 1].pixels, 500*500*sizeof(Uint32));
                    }
                }
            }
        }
        
    }
    free(rt);
    return (0);
}


// void test()
// {

// 	// Wait for a connection
//     struct sockaddr_in  client;
//     int client_size = sizeof(client);
//     int client_socket = accept(serv_socket, (struct sockaddr *)&client, (socklen_t *)&client_size);

//     if(client_socket == -1) return errno;

//     char host[NI_MAXHOST];
//     char service[NI_MAXSERV];
//     ft_memset(host, 0 , NI_MAXHOST);
//     ft_memset(service, 0 , NI_MAXSERV);

//     if (getnameinfo((struct sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
//     {
//         printf("%s connected on port %s\n", host, service);
//     }
//     else
//     {
//         inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
//         printf("%s connected on port %d", host, ntohs(client.sin_port));
//     }
// 	// Close listening socker
//     close(serv_socket);

// 	// While loop: accept and eco message back to client
//     char buf[4096];

// 	t_rt	rt;
// 	if (!rt_parse_file(&rt, "../scenes/dead_scene.json") || !load_textures(&rt))
// 		return -1;
// 	check_light(&rt.lights);	// chec light
// 	neg_obj(&rt.objs);			// check negative objects


// 	rt.pixels = (Uint32 *)malloc(WIN_WIDTH * WIN_HEIGHT * sizeof(Uint32));

//     while (1)
//     {
//         ft_memset(buf, 0 , 36);

//         // Wait for client to send data
//         int byte_received = recv(client_socket, buf, 36, 0);
//         if (byte_received < 0)
//         {   
//             printf("Error in recv(). Quitting.\n");
//             break;
//         }
//         if (byte_received == 36)
//         {
//             rt_thread_tracer(&rt);
//             send_image(client_socket, rt.pixels, 500*500*sizeof(Uint32));
//             // byte_received = 0;
//         }
//         if (byte_received == 0)
//         {
//             printf("Client disconnected\n");
//             break;
//         }
//     }
// 	ft_freedata(&rt);


// }



bool	ft_check_input(int argc)
{
	if (argc != 2)
	{
		ft_putendl("Usage: ./RT scenes/[scene_name]");
		return (false);
	}
	return (true);
}



int		main()
{
    int ret = run_server();
	if (ret != 0)
        printf("Returned value after stopping server: %d\n", ret);
	return (0);
}



