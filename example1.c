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
	HttpConnector *connector = CreateHttpConnector("ifconfig.me",80);
	HttpBuffer ReceiveBuffer;

	if(connector == NULL)
	{
		printf("%s",connector);
		return 1;
	}

	HttpConnectorSetUserAgent(connector,"curl/7.54"); //set user-agent on http requisition
	SendGetHttpConnector(connector,"/"); //HttpConnector *connector, char *data
	printf("sent...\n");

	printf("receiving...\n");
	output = fopen("myip.txt","w");
	if(output==NULL)
	{		
		printf("Cant open file\n");
		return 1;
	}
	int cont=0;
	
	
	if((ReceiveBuffer = ReceiveHttpConnector(connector))==NULL) //HttpConnector *connector, int MAX_RESPONSE_LEN, char *data
	{
		printf("Receive error\n");
		return 1;
	}
	
	fprintf(output,ReceiveBuffer);	
	
	fclose(output);
	cont++;
		
	if(cont==0)
		printf("Nothing received\n");
	else
		printf("content added to file successfully\n");
	return 0;
}

