/* Calistu 2020
 * Easy web connector
 *
 * compile with gcc:
 * gcc src/* example1.c -o example1 -I libs/ -g
 * 
 * this program example connect a reverse ip site and gets extern ip
 */
 
#include <httpConnect.h>

int main()
{
	FILE *output;
	printf("creating http connector...\n");
	HttpConnector *connector = CreateHttpConnector("ifconfig.me",80); // char *host, int port
	HttpBuffer ReceiveBuffer;
	if(connector == NULL)
	{
		printf("%s",connector);
		return 1;
	}

	HttpConnectorSetUserAgent(connector,"curl/7.54"); //set user-agent on http requisition - HttpConnector *connector,  char *data
	if(SendGetHttpConnector(connector,"/")!=0) //Send GET method requisition - HttpConnector *connector, char *data
		return 1;
	printf("sent...\n");

	output = fopen("myip.txt","w");
	if(output==NULL)
	{		
		printf("Cant open file\n");
		return 1;
	}

	printf("receiving...\n");	
	if((ReceiveBuffer = ReceiveHttpConnector(connector))==NULL) //HttpConnector *connector
	{
		printf("Receive error\n");
		return 1;
	}
	
	fprintf(output,ReceiveBuffer);	
	
	fclose(output);
		
	printf("content added to file successfully\n");
	return 0;
}

