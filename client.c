#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    printf("+----------------------------------------------+\n");
	printf("|             Name: Utpal Kumar Dey            |\n");
	printf("|                 Client Program               |\n");
	printf("+----------------------------------------------+\n\n\n\n");

    int server_socket, port_number, message_length; ///Declaring variables for server socket, port number and message length.
    struct sockaddr_in server_address; ///Declaring variable for server address.
    struct hostent *server_name;    /// Declaring variable for server name.
    char sending_message[256], received_message[256]; ///Declaring variable for sending message to server and receiving message from server.
    int e, d, n; ///Declaring variable to store e,d and n.

    if (argc < 3) ///Checking whether initial input arguments are correct or not.
	{
		fprintf(stderr,"!!!ERROR!!!, Not enough input provided.\n\n\n");
		exit(0);
	}
	else
	{
	    printf("Input seems okay.\n\n\n");
	}

	port_number = atoi(argv[2]); ///Converting port number from character to integer.
	server_socket = socket(AF_INET, SOCK_STREAM, 0); ///Defining server socket.

	if (server_socket < 0) ///Checking whether server socket is opened properly or not.
	{
		perror("!!!ERROR!!!, Can not open server socket.\n\n\n");
	}
	else
	{
	    printf("Server socket opened successfully.\n\n\n");
	}

	server_name = gethostbyname(argv[1]); ///Getting the appropriate server name.

	if (server_name == NULL) ///Checking whether the hostname is correct or not.
	{
		fprintf(stderr,"!!!ERROR!!!, Host name is incorrect.\n\n\n");
		exit(EXIT_FAILURE);
	}
	else
	{
	    printf("Host name is correct.\n\n\n");
	}

	bzero((char*) &server_address, sizeof(server_address)); ///Initializing zero to server address variable.
	server_address.sin_family = AF_INET; ///Defining internet socket address family.
	bcopy((char*)server_name->h_addr, (char*)&server_address.sin_addr.s_addr, server_name->h_length); ///Copying server address.
	server_address.sin_port = htons(port_number); ///Assigning port number.

    if (connect(server_socket,(struct sockaddr*) &server_address,sizeof(server_address)) < 0) ///Checking whether connection with server is successful or not.
	{
		perror("!!!ERROR!!!, Can not connect with server.\n\n\n");
	}
	else
	{
	    printf("Connected with server successfully.\n\n\n");

        while(1)
        {
            printf("Enter Client Data (p and q prime, where p * q > 128): "); ///Asking user for appropriate values.
            bzero(sending_message,256); ///Initializing zero to sending message.
            fgets(sending_message,255,stdin); ///Reading in input.

            if(strcmp(sending_message,"\n") == 0) ///Checking for terminating condition.
            {
                printf("\n\n\nClient Disconnecting...\n\n");
                message_length = write(server_socket,sending_message,strlen(sending_message));
                break;
            }

            printf("\n\n\n");

            message_length = write(server_socket,sending_message,strlen(sending_message)); ///Sending the message to server and getting the length.

            if (message_length < 0) ///Checking whether the message has been sent ot not.
            {
                perror("!!!ERROR!!!, Can not send message to server.\n\n\n");
            }
            else
            {
                printf("Message delivered to server successfully.\n\n\n");
            }

            bzero(received_message,256); ///Initializing zero to received message.
            message_length = read(server_socket,received_message,255); ///Receiving message from server.

            if (message_length < 0) ///Checking whether the message has been received ot not.
            {
                perror("!!!ERROR!!!, No message received from server.\n\n\n");
            }
            else
            {
                printf("Message received from server successfully.\n\n\n");
            }

            if(strcmp(received_message, "INVALID (Not Prime or < 128)") == 0) ///Checking for invalid input.
            {
                printf("SERVER Message: %s\n\n\n",received_message); ///Printing out the error meesage.
            }
            else
            {
                sscanf(received_message, "%d %d %d", &e, &d, &n); ///Retrieving values from received message.
                printf("SERVER Message: %d     %d     %d     (e   d   n)\n", e, d, n); ///Printing out all the values.
                printf("PRIVATE KEY: e =     %5d     n =     %5d\n", e, n); ///Printing out the private key.
                printf("PUBLIC KEY:  d =     %5d     n =     %5d\n\n\n", d ,n); ///Printing out the public key.
            }
        }
	}

	close(server_socket);

    return 0;
}
