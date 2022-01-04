# RSA-Algorithm-using-Socket-Programming-in-C
This project implements simple implementation of RSA algorithm in C language using socket programming. This project contains a complete C program to a client/server model using Linus sockets. You will find two C programs in this repository which are client.c and server.c. server.c program contains the implenetation RSA key generation algorithm with data passed in from the client. server.c and client.c programs will need to be run in two different machines within the same network. The functionalities of server and client are given below.

Server-->
* The server establishes a socket connection over TCP using a port number passed in as an argument to the program.
* The server receives two prime numbers p and q from the client. Then the server calculates the value of n, phi(n), e, and d using the RSA key generation algorithm. An explanation of RSA key generation algorithm is given after this section. The product of p and q needs to be greater or equal to 128 to be valid. The server returns the text "INVALID" back to the client if p and q are invalid for some reason otherwise returns the values of e, d, and n.
* The server provides status updates of connection events, messages being sent and received, and so on.
* The server recognizes when the client has disconnected and subsequently closes the socket and terminate the program.
A sample output of the server program is given below.

![server_output](https://user-images.githubusercontent.com/3108754/147995560-a43399f7-665b-4538-949b-dd9c6fe8fc7a.JPG)


Client-->
* The client connects to the server using the hostname and port number (the same port number that the server used) passed in as arguments to the program.
* The client reads in the values of p and q manually from the user using stdin. Then the client sends this values to the server and the server sends back the values of n, e, and d if the values of p and q are valid. The client can send as many values of p and q combinations to the server as desired.
* The client prints out an appropriate error message if the server sends an "INVALID" message. Otherwise, the client prints out public-private key data with appropriate message.
* The client provides status updates of connection events, messages being sent and received, and so on.
* The client can quit and desconnect from the server when the user simply enters a carriage return (the [ENTER] key).
A sample output of the client program is given below.

![client_output](https://user-images.githubusercontent.com/3108754/147996935-fd38d0aa-3fc6-4ace-9a17-6c633b7ef39d.JPG)



An explanation of the RSA key generation algorithm is given below.
* Randomly choose two prime numbers p and q such that (p * q >= 128).
* Compute n = (p * q) and phi(n) = (p-1)(q-1).
* Randomly choose an odd number e (1 < e < phi(n)) that is co-prime to phi(n) such that greatest common divisor if e and phi(n) becomes 1 (gcd(e, phi(n)) = 1).
* Compute d (1 < d < phi(n)) such that d is the modular multiplicative inverse of e (
![Capture](https://user-images.githubusercontent.com/3108754/147998040-116a6d73-20bd-46d5-a4ac-3c98a6a4c8ab.JPG)).
