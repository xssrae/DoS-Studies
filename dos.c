#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[]){
    
    if (argc != 3){
        fprintf(stderr, "Usage: %s <destination> <number of connections>\n", argv[0]);
        exit(1);
    }

    const char *destination = argv[1];
    struct in_addr inp;

    if (inet_pton(AF_INET, destination, &inp) == 0){
        fprintf(stderr, "Invalid IPv4 address\n");
        exit(1);
    }

    int number_of_connections = atoi(argv[2]);
    int port = 80;

    for (int i = 0; i < number_of_connections; i++){
        int mysocket = socket(AF_INET, SOCK_STREAM, 0);
        if (mysocket == -1){
            perror("socket");
            exit(1);
        }

        struct sockaddr_in target;
        target.sin_family = AF_INET;
        target.sin_port = htons(port);
        target.sin_addr.s_addr = inet_addr(destination);

        int connect_result = connect(mysocket, (struct sockaddr *)&target, sizeof target);
        if (connect_result == 0){
            printf("Connection %d - status [SUCCESS] \n", i);
        }
    }
    
    return 0;
}