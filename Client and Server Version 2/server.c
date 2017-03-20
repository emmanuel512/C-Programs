// Simple client/server program will allow at chat interface between client and server
//IPV4 only!!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORTNUM 4008
#define MAX_MESSAGE_LENGTH 50
#define MAX_CONNECTIONS 4

void print_incoming_address(struct sockaddr_in *host)
{
	char ip[INET_ADDRSTRLEN];
	struct in_addr *addr =  &(host->sin_addr);
	inet_ntop(AF_INET, addr, ip, INET_ADDRSTRLEN);
	printf("Connected to IP: %s on portnum: %d\n", ip, host->sin_port);
}

int main(int argc, char **argv)
{
	printf("Starting up server.....\n");

	int sockfd, newfd, error; // Socket file descriptor and error check value
	char recvBuf[MAX_MESSAGE_LENGTH]; // Receive buffer for replies
	char sendMsg[MAX_MESSAGE_LENGTH]; // Send buffer for send messages

	// Fill sock struct to hold server address and port
	struct sockaddr_in serv;
	memset(&serv, 0, sizeof(serv)); // Make sure the serv structure is empty
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(PORTNUM);
	socklen_t socksize = sizeof(serv);

	// Socket struct to hold incoming connection address and port
	struct sockaddr_in their_addr;

	// Make socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));

	printf("Binding socket.....\n");
	// Bind socket
	error = bind(sockfd, (struct sockaddr*)&serv, socksize);
	if(error == -1)
	{
		printf("Error binding socket!\n");
		exit(1);
	}

	printf("Listening for incoming connections.....\n");

	// Listen for incoming connections and que up only one 
	error = listen(sockfd, MAX_CONNECTIONS);
	if(error == -1)
	{
		printf("Error listening on socket\n");
		exit(1);
	}

	// Accept incoming connnection and print address 
	socklen_t addr_size = sizeof(their_addr);
	newfd =  accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

	print_incoming_address(&their_addr);

	// Clear send and recv buffer

	for(int i = 0; i < MAX_CONNECTIONS; i++)
	{
		while(newfd)
		{
			if(i != MAX_CONNECTIONS-1)
			{
				// Send and Receive messages 
				printf("Enter server msg: ");
				
				// clear sendMsg 
				memset(sendMsg, 0, sizeof(sendMsg));
				fgets(sendMsg, MAX_MESSAGE_LENGTH, stdin);

				short msg_len = strlen(sendMsg);
				send(newfd, sendMsg, msg_len, 0);

				printf("\n");

				// clear recvBuff 
				memset(recvBuf, 0, sizeof(recvBuf));
				recv(newfd, recvBuf, MAX_MESSAGE_LENGTH, 0);
				
				// Check if msg is bye
				if(strcmp(recvBuf, "Good Bye\n") == 0)
				{
					// Send bye message and close socket connection

					char *bye_message = "Server: Ok, Good Bye!\n";
					short msg_len = strlen(bye_message);
					send(newfd, bye_message, msg_len, 0);

					printf("\nEnd of client program\n");
					// Close connection
					close(newfd);
					printf("Accept next pending connection request...\n");
					socklen_t addr_size = sizeof(their_addr);
					newfd =  accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
					print_incoming_address(&their_addr); 
					break;  
				} 
				printf("Client: %s\n", recvBuf);
			}
					// Send and Receive messages 
			printf("Enter server msg: ");
			
			// clear sendMsg 
			memset(sendMsg, 0, sizeof(sendMsg));
			fgets(sendMsg, MAX_MESSAGE_LENGTH, stdin);

			short msg_len = strlen(sendMsg);
			send(newfd, sendMsg, msg_len, 0);

			printf("\n");

			// clear recvBuff 
			memset(recvBuf, 0, sizeof(recvBuf));
			recv(newfd, recvBuf, MAX_MESSAGE_LENGTH, 0);
			
			// Check if msg is bye
			if(strcmp(recvBuf, "Good Bye\n") == 0)
			{
				// Send bye message and close socket connection

				char *bye_message = "Server: Ok, Good Bye!\n";
				short msg_len = strlen(bye_message);
				send(newfd, bye_message, msg_len, 0);

				printf("\nEnd of server program\n");
				// Close connection
				close(newfd);
				close(sockfd);
				exit(1);
			} 
			printf("Client: %s\n", recvBuf);
		}
	}
}
