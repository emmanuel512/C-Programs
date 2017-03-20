// Simple client/server program will allow at chat interface between client and server
// IPV4 only!!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_MESSAGE_LENGTH 50

int main(int argc, char **argv)
{
	printf("Starting up client.....\n");
	int sockfd, error; 
	char recvBuf[MAX_MESSAGE_LENGTH]; // Receive buffer for replies
	char sendMsg[MAX_MESSAGE_LENGTH]; // Send buffer for send messages

	// Make socket 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// Make struct for destination address and port
	struct sockaddr_in dest;
	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(4008);
	dest.sin_addr.s_addr = htonl(INADDR_ANY);
	socklen_t dest_socksize = sizeof(dest);

	printf("Connecting to server.....\n");
	// Connect to server

	error = connect(sockfd, (struct sockaddr *)&dest, dest_socksize);
	if(error == -1)
	{
		printf("Error connecting to server\n");
		exit(1);
	}

	printf("Connected to server\n");

	while(1)
	{

		printf("\n");

		// clear recvBuf 
		memset(recvBuf, 0, sizeof(recvBuf));
		recv(sockfd, recvBuf, MAX_MESSAGE_LENGTH, 0);
		printf("Server: %s\n", recvBuf);
		
		printf("Enter client msg: ");
		
		// clear sendMsg Buffer
		memset(sendMsg, 0, sizeof(sendMsg));
		fgets(sendMsg, MAX_MESSAGE_LENGTH, stdin);
		
		// Check if is bye message

		if(strcmp(sendMsg, "Good Bye\n") == 0)
		{
			// Send bye message and close socket
			
			short msg_len = strlen(sendMsg);
			send(sockfd, sendMsg, msg_len, 0);
					
			recv(sockfd, recvBuf, MAX_MESSAGE_LENGTH, 0);
			printf("%s\n", recvBuf);
			
			// Close connection
			close(sockfd);
			printf("End of client program\n");
			exit(1);
		}

		short msg_len = strlen(sendMsg);
		send(sockfd, sendMsg, msg_len, 0);
	}

}
