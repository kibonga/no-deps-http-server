//
// Created by pdjurdjic on 6.4.24..
//

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int domain = AF_INET;
    int type = SOCK_STREAM;
    int protocol = 0;

    // Create new CLIENT socket and get reference to file descriptor
    printf("Creating client socket...\n");
    int client_sock_fd = socket(domain, type, protocol);
    if(client_sock_fd == -1) {
        perror("failed to create client socket.\n");
        exit(EXIT_FAILURE);
    }
    printf("Created client socket.\n");

    // Connecting CLIENT socket
    short PORT = 8080;
    struct sockaddr_in server_addr;
    memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if((inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr)) <= 0) {
        perror("failed to convert text IP address to binary form.\n");
        exit(EXIT_FAILURE);
    }

    // Connect CLIENT socket to SERVER socket address
    printf("Connecting client socket...\n");
    int conn = connect(client_sock_fd, (struct sockaddr *)&server_addr, sizeof server_addr);
    if(conn == -1) {
        perror("failed to connect to server.\n");
        exit(EXIT_FAILURE);
    }
    printf("Client socket connected.\n");

    // Send message from CLIENT socket
    printf("Sending message from client socket...\n");
    char *client_hello_message = "Hello from client!";
    send(client_sock_fd, client_hello_message, strlen(client_hello_message), 0);
    printf("Message sent from client.\n");

    // Read server response from buffer
    char buffer[30000] = {0};
    printf("Reading server response from buffer...\n");
    read(client_sock_fd, buffer, 30000);
    printf("Read from buffer: %s\n", buffer);
}