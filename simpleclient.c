#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sockfd;
    int len;
    // This is the data type used to represent socket addresses in the Internet namespace
    struct sockaddr_in address;
    int result;
    char ch = 'A';

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // This identifies the address family or format of the socket address. 
    // You should store the value of AF_INET in this member. 
    address.sin_family = AF_INET;
    // This is the Internet address of the host machine.
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    // port number
    address.sin_port = htons(9734);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);

    if (result == -1)
    {
        perror("oops: client1");
        exit(1);
    }
    write(sockfd, &ch, 1);
    // The read() function attempts to read nbyte bytes from the file 
    // associated with the open file descriptor, fildes, into the buffer pointed to by buf.
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
    close(sockfd);
    exit(0);
}
