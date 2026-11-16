#ifndef Server_H_
#define Server_H_

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

#include "agl/aglm.h"

class ServerSocket {
public:
    ServerSocket() {
        recvBuffer[0] = '\0';
        sendBuffer[0] = '\0';
        addrlen = sizeof(address);

        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET,
                    SO_REUSEADDR | SO_REUSEPORT, &opt,
                    sizeof(opt))) {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr*)&address,
                sizeof(address))
            < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((new_socket
            = accept(server_fd, (struct sockaddr*)&address,
                    &addrlen))
            < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
  
    }
    
    ~ServerSocket() {
        closeConnection();
    }
    
    void closeConnection() {
        // closing the connected socket
        close(new_socket);
    
        // closing the listening socket
        close(server_fd);
    }
        
    glm::vec3 readPos() {
        glm::vec3 pos(0);
        valread = read(new_socket, recvBuffer, 1024 - 1); 
        if (valread > 0) {
            printf("RECEIVED: %s (%ld)\n", recvBuffer, valread);
            int clientid;
            float x, y, z;
            sscanf(recvBuffer, "%d,%f,%f,%f", &clientid, &x, &y, &z);
            pos = glm::vec3(x, y, z);
            //snprintf(sendBuffer, sizeof(sendBuffer), "Echo: %s\n", recvBuffer);
            //send(new_socket, sendBuffer, strlen(sendBuffer), 0);
        }
        return pos;
    }

    int server_fd, new_socket;
    ssize_t valread;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen;
    char recvBuffer[1024];
    char sendBuffer[2048];
};

#endif