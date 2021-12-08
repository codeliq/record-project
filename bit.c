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
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


#define PORTNUM 9002

int main(int argc, char *argv[]) {
	char buf[1024] = {0};
	char buf2[1024] = {0};
	char read_buf[1024] = {0};
	int len, ns;
	int rd;
	int split, find_line;
	int buy_album, left_num;
	FILE* file;
	FILE* wfile;
	ns = atoi(argv[1]);



	
	while(1) {
			//printf("count\n");
			
			strcpy(buf, "\n\n< Hello, Welcome to the record site. >\n++++++++++++++++\n1.Show record list\n2.Check quantity\n3.purchase\n4.Service center\n++++++++++++++++\n\n");
			
			buf[strlen(buf)-1] = '\0';
			//printf("%ld\n",sizeof(buf));
			if((send(ns, buf, sizeof(buf), 0)) == -1) {
				perror("send");
				exit(1);
			}
			
			//printf("send!!!!!!!!\n");
			
			if((recv(ns, buf2, sizeof(buf2), 0)) == -1) {
				perror("recv");
				exit(1);
			}
			//printf("recv!!!!!!!!\n");
			//printf("From Client: %s\n", buf2);

			
			if(strcmp(buf2, "1") == 0) {
				printf("- Client requested a list of albums\n");
				if(( rd = open("./record_list", O_RDONLY)) == -1) {
					perror("open1");
					exit(1);
				}
				read(rd, read_buf, 1023);
				read_buf[strlen(read_buf)-1] = '\0';
				if((send(ns, read_buf, strlen(read_buf), 0)) == -1) {
					perror("send");
					exit(1);
				}
				//printf("send!!!!!!!!\n");
				
				close(rd);
			}
			
			if(strcmp(buf2, "2") == 0) {	
				printf("- Client requested a num of albums\n");
				if((recv(ns, buf2, sizeof(buf2), 0)) == -1) {
					perror("recv");
					exit(1);
				}
				
				file = fopen("./record_num", "r");
				if (file == NULL) {
					printf("fopen");
					return 1;
				}

				find_line = 0;
				
				//printf("%s\n",buf2);
				while (fgets(read_buf, sizeof(read_buf), file) != NULL ) {
					//printf("%s", read_buf);
					
					find_line++;
					
					if(find_line == atoi(buf2)) {
						if((send(ns, read_buf, strlen(read_buf), 0)) == -1) {
							perror("send");
							exit(1);
						}
					}
					
					
				}
				fclose(file);

			}
			
			if(strcmp(buf2, "3") == 0) {	
				printf("- Client requested a purchase\n");
				if((recv(ns, buf2, sizeof(buf2), 0)) == -1) {
					perror("recv");
					exit(1);
				}
				
				buy_album = atoi(buf2);
				
				if((recv(ns, buf2, sizeof(buf2), 0)) == -1) {
					perror("recv");
					exit(1);
				}
				
				file = fopen("./record_num", "r");
				if (file == NULL) {
					printf("fopen");
					return 1;
				}
				
				if((wfile = fopen("temp", "w")) == NULL ) {
					printf("fopen2");
					return 1;
				}

				find_line = 0;
				
				//printf("%s\n",buf2);
				while (fgets(read_buf, sizeof(read_buf), file) != NULL ) {
					//printf("%s", read_buf);
					
					find_line++;
					
					
					if(find_line == buy_album) {
						sprintf(read_buf, "%d", atoi(read_buf)-atoi(buf2));
						fputs(read_buf, wfile);
						fputs("\n", wfile);
					}
					
					else fputs(read_buf, wfile);
					
					
				}
				fclose(file);
				fclose(wfile);
				
				if ( remove( "./record_num") == -1)  {
	      				printf("remove");
	      				exit(1);
				}
				
				if ( rename( "./temp", "record_num") == -1) {
	      				printf("rename");
	      				exit(1);
				}
				
				
			}
			
			if(strcmp(buf2, "4") == 0) {
				printf("- Client requested a Service Center\n");
				printf("+++++++++++++++++++++++++++++++++\n");
				strcpy(buf, "Hello, What do you want?\n");
				buf[strlen(buf)-1] = '\0';
				
				while(1) {
					if((send(ns, buf, sizeof(buf), 0)) == -1) {
						perror("send");
						exit(1);
					}
					
					if((recv(ns, buf2, sizeof(buf2), 0)) == -1) {
						perror("recv");
						exit(1);
					}
					
					printf("From Client: %s\n", buf2);
					
					
					printf("Enter message : ");
													
					fgets(buf, sizeof(buf), stdin);
					buf[strlen(buf)-1] = '\0';
					
					if(strcmp(buf, "EXIT") == 0) {
						memset(buf, '\0', sizeof(buf));
						memset(buf2, '\0', sizeof(buf2));
						break;
					}
				
				}
				printf("+++++++++++++++++++++++++++++++++\n");
			}
			

			
	}		
	
	close(ns);
	
	return 0;

}
		
