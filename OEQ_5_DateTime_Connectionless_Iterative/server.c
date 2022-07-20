#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>

int main(int argc, char* argv[])
{
	int sfd,r,bi,port;
	char buff[1024];
	struct sockaddr_in servaddr,cliaddr;
	socklen_t clilen;
	if(argc < 2) {
		printf("Usage : %s <port>\n",argv[0]);
		exit(0);
	}
	int arg1 = atoi(argv[1]);
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd==-1) {
		perror("Socket");
		return 0;
	}
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(arg1);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	bi=bind(sfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if(bi==-1) {
		perror("Bind()");
		return 0;
	}
	clilen = sizeof(cliaddr);
	while(1) {
		r=recvfrom(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,&clilen);
		buff[r]=0;
		time_t ticks;
		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%24s\r",ctime(&ticks));
		sendto(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
	}
	return 0;
}
