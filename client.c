#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 9002

int main(void){
	int sd;
	char buf[1024] = {0};
	char buf2[1024] = {0};
	
	struct sockaddr_in sin;

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	if(connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("connect");
		exit(1);
	}
	
	/*
	printf("Client or admin? \n");
	fgets(buf2, sizeof(buf2), stdin);
	buf2[strlen(buf2)-1] = '\0';
	if(strcmp(buf2, 
	*/
	
	while(1) {
		//printf("count\n");
		
		if(recv(sd, buf, sizeof(buf), 0) == -1) {
			perror("recv");
			exit(1);
		}	
		
		//printf("recv!!!!!!!!\n");
		
		//printf("- - - - - - - - - - - - - - - -\n");
		printf("%s\n", buf);
		//sleep(1);
		printf("Choose Menu : ");
		fgets(buf2, sizeof(buf2), stdin);
		buf2[strlen(buf2)-1] = '\0';
		
		if(send(sd, buf2, strlen(buf2), 0) == -1) {
			perror("send");
			exit(1);
		}
		//printf("send!!!!!!!!\n");
		
		if(strcmp(buf2, "1") == 0) {	
			printf("\n++++++++ Record List ++++++++\n");
		}
		
		if(strcmp(buf2, "2") == 0) {
			printf("Choose the album you want to check the quantity : ");
			fgets(buf2, sizeof(buf2), stdin);
			buf2[strlen(buf2)-1] = '\0';
			if(send(sd, buf2, strlen(buf2), 0) == -1) {
				perror("send");
				exit(1);
			}
			
			memset(buf, '\0', sizeof(buf));
			if(recv(sd, buf, sizeof(buf), 0) == -1) {
				perror("recv");
				exit(1);
			}
			buf[strlen(buf)-1] = '\0';
			printf("----- album left >>> %s\n", buf);
			
			memset(buf, '\0', sizeof(buf));
			memset(buf2, '\0', sizeof(buf2));
			
		}
		
		
		if(strcmp(buf2, "3") == 0) {
			printf("Choose the album you want to purchase : ");
			fgets(buf2, sizeof(buf2), stdin);
			buf2[strlen(buf2)-1] = '\0';
			if(send(sd, buf2, strlen(buf2), 0) == -1) {
				perror("send");
				exit(1);
			}
			
			printf("Enter the amount you want to purchase : ");
			fgets(buf2, sizeof(buf2), stdin);
			buf2[strlen(buf2)-1] = '\0';
			if(send(sd, buf2, strlen(buf2), 0) == -1) {
				perror("send");
				exit(1);
			}
			
			memset(buf, '\0', sizeof(buf));
			memset(buf2, '\0', sizeof(buf2));
			sleep(1);
		
		}
		
		if(strcmp(buf2, "4") == 0) {
			printf("----------Service Center-----------\n");
			while(1) {
					if((recv(sd, buf, sizeof(buf), 0)) == -1) {
						perror("recv");
						exit(1);
					}
						
					printf("From Service Center : %s\n", buf);					
					printf("Enter message : ");
					fgets(buf2, sizeof(buf2), stdin);
					buf2[strlen(buf2)-1] = '\0';
					
					if((send(sd, buf2, strlen(buf2), 0)) == -1) {
						perror("send");
						exit(1);
					}
					
					if(strcmp(buf2, "EXIT") == 0) {
						memset(buf, '\0', sizeof(buf));
						memset(buf2, '\0', sizeof(buf2));
						break;
						
					}
					

					
						
					
			}
			printf("-----------Service END-----------\n");
		}
		
		
		
		//sleep(1);
		
		
		//if(strcmp(buf, "<QUIT>") == 0) break;
		
	
	}
	
	
	close(sd);

	return 0;
}
