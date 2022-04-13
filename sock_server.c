// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>

#define PORT 999
int receive_basic(int s)
{
	int size_recv , total_size= 0;
	char chunk[600000];
	
	//loop
	while(1)
	{
		memset(chunk ,0 , 600000);	//clear the variable
		if((size_recv =  recv(s , chunk , 600000 , 0) ) < 0)
		{
			break;
		}
		else
		{
			total_size += size_recv;
			 int out = open("data222", O_RDWR | O_CREAT | O_TRUNC, 777);
            write(out, chunk, 600000);
		}
	}
	
	return total_size;
}
int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    char *hello = "HTTP/1.1 200 OK\nContent-Type: image/png\nContent-Type: text/html\nContent-Length: 700\n\n<h1>Hello world!</h1><img src='/Users/fbouibao/Desktop/webserv/icons8-home-32.png' alt=''>";
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            close(new_socket);
            //exit(EXIT_FAILURE);
        }
        
        char *buffer = malloc(sizeof(char) * 600000);
        // valread = read( new_socket , buffer, 600000);
        int bytes = recv(new_socket, buffer, 600000, 0);
        // receive_basic(new_socket);
        char *suffix = malloc(2);
        suffix[1] = 0;
        suffix[0] = i + 48;
        // char *filename = malloc(20);
        // asprintf(&filename, "%s%s", "./data", suffix);
        // printf("file: %s\n", filename);
       
        i++;
        printf("reached\n");
        write(new_socket , hello , strlen(hello));
        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
    }
    return 0;
}





