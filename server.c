#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int domain = AF_INET;
    int type = SOCK_STREAM;
    int protocol = 0;

    // Create new SERVER socket and get reference to file descriptor
    printf("Creating server socket...\n");
    int sock_fd = socket(domain, type, protocol);
    if(sock_fd == -1) {
        perror("failed to create server socket\n");
        exit(EXIT_FAILURE);
    }
    printf("Created server socket.\n");

    // Naming a SERVER socket (binding)
    printf("Naming(binding) a server socket...\n");
    short PORT = 8080;
    struct sockaddr_in addr;
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    memset(addr.sin_zero, '\0', sizeof addr.sin_zero);

    int sock_bind = bind(sock_fd, (struct sockaddr *)&addr, sizeof addr);
    if(sock_bind == -1) {
        perror("failed to bind\n");
        exit(EXIT_FAILURE);
    }
    printf("Server socket bound.\n");

    // Preparing socket for incoming connection requests
    printf("Preparing socket for incoming requests...\n");
    int NUM_OF_CONN = 5;
    listen(sock_fd, NUM_OF_CONN);
    printf("Socket ready to listen.\n");

    char *server_hello_message = "Hello from server!";
    socklen_t addrlen = sizeof addr;
    int new_sock = 0;
    int val_read = 0;
    char buffer[30000] = {0};
    while(1) {
        printf("Waiting for new connection...\n");
        new_sock = accept(sock_fd, (struct sockaddr *)&addr, &addrlen);
        if(new_sock == -1) {
            perror("failed to create new socket.\n");
            exit(EXIT_FAILURE);
        }
        printf("New connection accepted.\n");

        // Read data sent from client
        printf("Reading client message...\n");
        read(new_sock, buffer, 30000);
        printf("Read from buffer: %s\n", buffer);

        // Write to client
        write(new_sock, server_hello_message, strlen(server_hello_message));
        printf("Response sent from server.\n");

        // Close client socket
        printf("Closing client socket...\n");
        close(new_sock);
        printf("Client socket closed.\n");
    }
}
