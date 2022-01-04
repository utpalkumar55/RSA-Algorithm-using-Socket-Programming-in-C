#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int check_prime(int number) ///This functions checks whether a given number is prime or not.
{
    int i;
    for(i=2;i<number;i++)
    {
        if(number%i==0)
        return 0;
    }
    return 1;
}

int find_gcd(int a, int b) ///This function calculates greatest common divisor of two given numbers.
{
    int temp;
    while(1)
    {
        temp = a%b;
        if(temp == 0)
        {
            return b;
        }
        a = b;
        b = temp;
    }
    return 1;
}

int find_e(int phi) ///This function calculates the value of e while the value of phi is given.
{
    int e;
    for(e = 2; e < phi; e++)
    {
        if(find_gcd(e, phi) == 1)
        {
            break;
        }
    }
    return e;
}

int find_d(int phi, int e) ///This function calculates the value of d while the value of phi and e is given
{
    int d, temp, i;
    for(i = 1; 1; i++)
    {
        temp = (phi * i) + 1;
        if(temp % e == 0)
        {
            d = temp/e;
            break;
        }
    }
    return d;
}

int main(int argc, char *argv[])
{
    printf("+----------------------------------------------+\n");
	printf("|             Name: Utpal Kumar Dey            |\n");
	printf("|                 Server Program               |\n");
	printf("+----------------------------------------------+\n\n\n\n");

	int server_socket, client_socket, port_number, message_length; ///Declaring variables for both server socket and client socket, port number and message length.
	socklen_t client_address_length; ///Declaring variable for client socket address length.
	char received_message[256], sending_message[256]; ///Declaring character array to store received message from client to server and sending message from server to client respectively.
	int p, q, n, e, d, phi; ///Declaring variable to store p, q, n, e, d and phi respectively.
	struct sockaddr_in server_address, client_address; ///Declaring variable for server socket address and client socket address respectively.

	if(argc < 2) ///Checking whether initial input arguments are correct or not.
	{
	    fprintf(stderr,"!!!ERROR!!!, Not enough input provided.\n\n\n");
		exit(1);
	}
	else
	{
	    printf("Input seems okay.\n\n\n");
	}

	server_socket = socket(AF_INET, SOCK_STREAM, 0); ///Defining server socket.

	if (server_socket < 0) ///Checking whether server socket is opened properly or not.
	{
		perror("!!!ERROR!!!, Can not open server socket.\n\n\n");
	}
	else
	{
	    printf("Server socket opened successfully.\n\n\n");
	}

	bzero((char*) &server_address, sizeof(server_address)); ///Initializing zero to server address variable.
	port_number = atoi(argv[1]); ///Converting port number from character to integer.
	server_address.sin_family = AF_INET; ///Defining internet socket address family.
	server_address.sin_addr.s_addr = INADDR_ANY; ///Defining internet address.
	server_address.sin_port = htons(port_number); ///Assigning port number.

	if (bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) ///Checking whether server socket is bind properly or not.
	{
		perror("!!!ERROR!!!, Can not bind server socket.\n\n\n");
	}
	else
	{
	    printf("Server socket bind successfully.\n\n\n");
	    printf("Waiting for connection.....\n\n\n");
	}

	listen(server_socket,5); ///Waiting for connection to be established.
	client_address_length = sizeof(client_address); ///Calculating length of client address.
	client_socket = accept(server_socket, (struct sockaddr*) &client_address, &client_address_length); ///Establishing server socket with client socket.

    if (client_socket < 0) ///Checking whether connection with client is successful or not.
    {
        perror("!!!ERROR!!!, Can not connect with client.\n\n\n");
    }
    else
    {
        printf("Connected with client successfully.\n\n\n");
    }

	while(1) ///Looping for multiple message transfer.
	{
        bzero(received_message,256); ///Initializing zero to received message.
        message_length = read(client_socket,received_message,255); ///Receiving message from client.

        if(strcmp(received_message,"\n") == 0) ///Checking for termination condition.
        {
            printf("Client Disconnected\n\n");
            break;
        }
        else
        {
            printf("Message received from client successfully.\n");
            sscanf(received_message, "%d %d", &p, &q); ///Extracting p and q from received message.

            if(!check_prime(p) || !check_prime(q) || p*q < 128) ///Checking whether p and q are prime or not and whether p*q is less than 128 or not.
            {
                bzero(sending_message,256); ///Initializing zero to sending message.
                strcpy(sending_message,"INVALID (Not Prime or < 128)"); ///Copying error message to sending message.
                message_length = write(client_socket,sending_message,strlen(sending_message)); ///Sending the message to client and getting the length.

                if (message_length < 0) ///Checking whether the message has been sent ot not.
                {
                    perror("!!!ERROR!!!, Can not send message to client.\n\n\n");
                }
                else
                {
                    printf("\n\nMessage delivered to client successfully.\n\n\n");
                }
            }
            else
            {
                n = p * q; ///Calculating n.
                phi = (p - 1) * (q - 1); ///Calculating phi
                e = find_e(phi); ///Calculating e
                d = find_d(phi, e); ///Calculating d
                printf("p = %d     q = %d     n = %d     e = %d     phi = %d     d = %d.\n\n\n", p, q, n, e, phi, d); ///Printing out the calculated value.

                bzero(sending_message,256); ///Initializing zero to sending message.
                sprintf(sending_message, "%d %d %d", e, d, n); ///Putting values into sending message.
                printf("Sending Public-Private Key (e, d, n) to Client.\n\n\n");

                message_length = write(client_socket,sending_message,strlen(sending_message)); ///Sending the message to client and getting length.

                if (message_length < 0) ///Checking whether the message has been sent ot not.
                {
                    perror("!!!ERROR!!!, Can not send message to client.\n\n\n");
                }
                else
                {
                    printf("Message delivered to client successfully.\n\n\n");
                }
            }
        }

	}

    close(client_socket); ///Closing client socket
	close(server_socket); ///Closing server socket

	return 0;
}
