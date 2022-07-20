#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
	int listenfd,port,r;
	char buff[1024];
	struct sockaddr_in servaddr,cliaddr;
	socklen_t servlen;
	if(argc < 2) {
		printf("Usage : %s <port>\n",argv[0]);
		exit(0);
	}
	int arg1 = atoi(argv[1]);
	listenfd = socket(AF_INET,SOCK_DGRAM,0);
	if(listenfd==-1) {
		perror("Socket");
		return 0;
	}
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(arg1);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	sendto(listenfd,buff,sizeof(buff),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
	r=recvfrom(listenfd,buff,sizeof(buff),0,(struct sockaddr*)&servaddr,&servlen);
	buff[r]=0;
	printf(" The time received from the server:%s",buff);
	exit(0);
	return 0;
}
