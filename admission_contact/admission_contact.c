#include "admission_contact.h"

#define IP_FILE_PATH "./IPs"
extern char myIp[16];
/*
//Iterate over IPs file and get the topology
int main() {

	struct Head_Node *topology = NULL;
	struct Node *node = NULL;
	FILE *fp = NULL;
	struct stat file_stat;
	int version = 0;
	time_t last_mtime = 0;
	
	while(1) {
		
		if(stat(IP_FILE_PATH, &file_stat) != -1) {
			if(last_mtime <= file_stat.st_mtime) {
				fp = fopen(IP_FILE_PATH, "r");
				(void)parse_IPs(fp, &topology, &version);
				fclose(fp);
			}
		}
		sleep(1);
	}
	return 0;
}
*/	

struct Head_Node *server_topology;	

int main() {

	int listenSocket, connectSocket, socketFlags, ret, clientSize;
	struct sockaddr_in myAddress, clientAddress;
	int i,j, bytes, numBytes, pid;
	server_topology = NULL;

	log_init();
        getIpAddr();	
	//server_topology = (struct Head_Node*)calloc(1, sizeof(struct Head_Node));
	
	payloadBuf *packet;
	int rc;
	
	clientSize = sizeof(clientAddress);

	//Create a listening socket..
	if((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error creating server socket. Dying ...\n");
		return 0;
	}
	printf("Socket Created\n");
	
	//Init the sockaddr structure..
	memset(&myAddress, 0, sizeof(myAddress));
	myAddress.sin_family	  = AF_INET;
	myAddress.sin_addr.s_addr = INADDR_ANY;
	myAddress.sin_port	  = htons(MY_PORT);
	
	
	//Now bind the socket..
	if((bind(listenSocket, (struct sockaddr *)&myAddress, sizeof(myAddress))) < 0) {
		printf("Error binding socket. Dying...\n");		
		return 0;
	}

	printf("Bind Created\n");
	
	//Listen on the socket for incoming connections..	
	if((listen(listenSocket, 10)) < 0) {
		printf("Error listening on socket. Dying...\n");
		return 0;
	}
	
	printf("Now listening\n");
	for(;;) {
		if ((connectSocket = accept(listenSocket, (struct sockaddr*)&clientAddress, &clientSize)) < 0) {
			printf("Error accepting connection. Dying...\n");
			return 0;
		} 
		
		printf("Before printing\n");
		
		
		printf("\nClient %d.%d.%d.%d connected\n", 
				(clientAddress.sin_addr.s_addr & 0xFF),  
				(clientAddress.sin_addr.s_addr & 0xFF00) >> 8,  
				(clientAddress.sin_addr.s_addr & 0xFF0000) >> 16,  
				(clientAddress.sin_addr.s_addr & 0xFF000000) >> 24 
			);
		
		//A client has connected.
		//I need to tell the topology to the client
		
		printf("Calling Message Decode\n");	
		rc = message_decode(connectSocket, &packet);
		printf("After message decode\n");
		if(rc == RC_SUCCESS)
			processPacket(connectSocket, packet);	
	
		
		//Now I need to tell other that a new node is about to join. 
		//First tell the nodes neigbors	
		close(connectSocket);
		
	}	
}

