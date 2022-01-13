# HttpCConnector

simple library with function, to send http requests in an easy and simple way.


HttpConnector *connector
Socket struct with destination url informations

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
  
HttpConnector *CreateHttpConnector
Returns an initialized HttpConnector pointer

    extern HttpConnector *CreateHttpConnector(char *host, int port);



void HttpConnectorSetUserAgent
Sets user-agent on requisition

    extern void HttpConnectorSetUserAgent(HttpConnector *connector, char *user_agent);


int SendGetHttpConnector
Send data to HttpConnector destination

    extern int SendGetHttpConnector(HttpConnector *connector, char *data);


HttpBuffer ReceiveHttpConnector
Receives data from HttpConnector destination to HttpBuffer

    extern HttpBuffer ReceiveHttpConnector(HttpConnector *connector);

HttpBuffer
same as char *

    typedef char * HttpBuffer;
