#ifndef client_H_
#define client_H_

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

class ClientSocket {
public:
   ClientSocket() {
       buffer[0] = '\0';
       sendBuffer[0] = '\0';

       if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
           printf("\n Socket creation error \n");
           return;
       }

       serv_addr.sin_family = AF_INET;
       serv_addr.sin_port = htons(PORT);

       // Convert IPv4 and IPv6 addresses from text to binary
       // form
       if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
           <= 0) {
           printf(
               "\nInvalid address/ Address not supported \n");
           return;
       }

       if ((status
           = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
           < 0) {
           printf("\nConnection Failed \n");
           return;
       }
   }
    
   ~ClientSocket() {
        closeConnection();
   }

   void closeConnection() {
       close(client_fd);
   }
   
   void sendPos(int clientId, float x, float y, float z) {
        sprintf(sendBuffer, "%d,%f,%f,%f", clientId, x, y, z);
        send(client_fd, sendBuffer, strlen(sendBuffer), 0);
        //valread = read(client_fd, buffer, 1024 - 1); 
        //printf("%s\n", buffer);
   }

   int status, valread, client_fd;
   struct sockaddr_in serv_addr;
   char buffer[1024];
   char sendBuffer[1024];
};

#endif