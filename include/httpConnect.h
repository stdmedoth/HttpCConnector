/* Calistu 2020
 * Easy web connector
*/
#ifndef __HTTPCON__
#define __HTTPCON__

#ifdef __linux__
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#endif

#ifdef WIN32
#include <winsock2.h>
#endif

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HOST_LEN 100
#define MAX_URL_LEN 1000
#define MAX_BUFFER_LEN 1000

typedef struct 
{
	int socket_fd;
	char host[MAX_HOST_LEN];
	char ip[MAX_HOST_LEN];
	char url[MAX_URL_LEN];
	char user_agent[MAX_URL_LEN];
	int port;
	struct sockaddr_in server;
	int sock_len;
	
	char response_buffer[MAX_BUFFER_LEN];
	int bytes_qnt;
	int response_code;
}HttpConnector;

typedef char * HttpBuffer;

extern HttpConnector *CreateHttpConnector(char *host, int port);

extern void HttpConnectorSetUserAgent(HttpConnector *connector, char *user_agent);

extern int SendGetHttpConnector(HttpConnector *connector, char *data);

unsigned long hex2int(char *a, unsigned int len);
extern HttpBuffer ReceiveHttpConnector(HttpConnector *connector);

#endif
