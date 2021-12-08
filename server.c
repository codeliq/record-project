#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/times.h>
#include <time.h>

#define PORTNUM 9002

int main(void) {
	char buf[1024], port[10];
	struct sockaddr_in sin, cli;
	int sd, ns, clientlen = sizeof(cli);
	struct hostent *hent;
	in_addr_t addr;
	struct hostent *hp;
	struct in_addr in;
	time_t t;

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	if(bind(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("bind");
		exit(1);
	}

	if(listen(sd, 5)) {
		perror("listen");
		exit(1);
	}
	
	while(1) {
		if((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1) {
			perror("accept");
			exit(1);
		}
		
		printf("--- Accept Client ---\n");
		switch (fork()) {
			case 0:
				printf("--- Fork For Client ---\n\n");
				close(sd);
				sprintf(buf, "%d", ns);
				execlp("./bit",  "bit", buf, (char*)0);		
				
	
				close(ns);		
			}
			close(ns);		
		}



		return 0;

}
		
