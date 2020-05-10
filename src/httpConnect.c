/* Calistu 2020
 * Easy web connector
*/
#include <httpConnect.h>

#define MAX_OUTP_BUF 200

char *HttpFormatRequisition [] = {"GET ","HTTP/1.1","Host: ","User-Agent:","Accept: */*"};

void HttpConnectorSetUserAgent(HttpConnector *connector, char *user_agent)
{
	strcpy(connector->user_agent,user_agent);
	return ;
}

int SendGetHttpConnector(HttpConnector *connector, char *data)
{
	int err;
	char SendBuffer[MAX_BUFFER_LEN];
	sprintf(SendBuffer,"%s%s %s\r\n%s%s\r\n%s %s\r\n%s\r\n\r\n",
	HttpFormatRequisition[0],
	data,                     //REQUEST TYPE and PATH
	HttpFormatRequisition[1], //HTTP VERSION
	HttpFormatRequisition[2],
	connector->host,          //HOST
	HttpFormatRequisition[3],
	connector->user_agent,    //USER AGENT
	HttpFormatRequisition[4]);
	
	err = send(connector->socket_fd,SendBuffer,strlen(SendBuffer),0);
	if( err < 0 )
	{
		fprintf(stderr,"send: %s\n",strerror(errno));
		return 1;
	}
	return 0;
}

HttpBuffer ReceiveHttpConnector(HttpConnector *connector)
{
	HttpBuffer HttpHeaderBuffer = malloc(48000);
	HttpBuffer HttpReceiveBuffer = malloc(1);
	HttpBuffer HttpTotalBuffer = malloc(48000);
	char *fim;
	int pos=0,ascii,bytes=0;
	int response_qnt=0;
	char *hexa_qnt = malloc(20);
	if(recv(connector->socket_fd,HttpHeaderBuffer,48000,0)==-1) // gets headers
		return HttpHeaderBuffer;

	hexa_qnt = strstr(HttpHeaderBuffer,"\r\n\r\n")+4;
	if(hexa_qnt==NULL)
		return NULL;
	while(1)
	{
		ascii = hexa_qnt[pos];
		if(ascii=='\n'||ascii=='\r')
		{
			hexa_qnt[pos] = '\0';
			break;
		}
		if(pos>=48000)
		{
			return HttpHeaderBuffer;
			break;
		}
		pos++;
	}
		
	connector->bytes_qnt = response_qnt;
	HttpTotalBuffer = malloc(response_qnt+strlen(HttpHeaderBuffer));
	sprintf(HttpTotalBuffer,"%s",HttpHeaderBuffer);
	while(bytes<=response_qnt)
	{
		
		recv(connector->socket_fd, HttpReceiveBuffer, 1, MSG_WAITALL);
		printf("%s",HttpReceiveBuffer);
		sprintf(HttpTotalBuffer,"%s%s",HttpTotalBuffer,HttpReceiveBuffer);
		
		bytes++;
	}
	
	return HttpTotalBuffer;
}

HttpConnector *CreateHttpConnector(char *host, int port)
{
	HttpConnector *connector;
	int socket_fd=0,status=0;
	char stdout_buf[MAX_OUTP_BUF];
	struct hostent *st_hosts;
	struct timeval time_value;
	
	st_hosts = gethostbyname(host);
	if(st_hosts == NULL)
	{
		fprintf(stderr,"gethostbyname: %s\n",strerror(errno));
		return NULL;
	}
	
	connector = malloc(sizeof(HttpConnector));
	strcpy((connector->host),host);
	strcpy((connector->ip),inet_ntoa(*(struct in_addr *)st_hosts->h_addr_list[0]));
	connector->port = port;
	connector->server.sin_family = AF_INET;
	connector->server.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)st_hosts->h_addr_list[0]));
	connector->server.sin_port = htons(connector->port);
	memset(connector->server.sin_zero,0,8);
	connector->sock_len = sizeof(struct sockaddr_in);
	connector->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	#ifdef __HTTP_DEBUG__
	fprintf(stdout,"struct information:\nhost: %s\nip: %s\nport: %i\n",connector->host, connector->ip, connector->port);
	#endif
	
	if(socket_fd < 0)
	{
		fprintf(stderr,"socket: %s\n",strerror(errno));
		return NULL;
	}
	
	status = connect(connector->socket_fd, (struct sockaddr*)&connector->server, sizeof(connector->server));
	if(status < 0)
	{
		fprintf(stdout,"connect: %s\n",strerror(errno));
		return NULL;
	}
//	time_value.tv_sec = 2;
//	time_value.tv_usec = 0;
//	setsockopt(connector->socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*) &time_value, sizeof(time_value));
	
	return connector;	
}

