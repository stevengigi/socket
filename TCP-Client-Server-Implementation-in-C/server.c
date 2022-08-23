#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <Winsock2.h>
#include<stdbool.h>

int main(){

  //初始化 WINDOWS SOCKETS DLL
  WSADATA wasData;
  WORD version = MAKEWORD(2,1); //VERSION
  //用 WSAStartup 開始 Winsocket-DLL
  int iresult = WSAStartup(MAKEWORD(2,2),&wasData);
  if(iresult!=0){
    printf("initial  error !!!\n");
  }
  SOCKADDR_IN addr;
  int addrlen = sizeof(addr);
  SOCKET sListen; //listening for an incoming connection
  SOCKET sConnect; //operating if a connection was found

  //AF_INET(IPV4)：表示建立的 socket 屬於 internet family
  //SOCK_STREAM(TCP)：表示建立的 socket 是 connection-oriented socket
  sConnect = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  //設定位址資訊的資料
  addr.sin_addr.s_addr=inet_addr("127.0.0.1");  // 設定 IP
  // addr.sin_addr.s_addr = INADDR_ANY; // 若設定 INADDR_ANY 表示任何 IP
  addr.sin_family=AF_INET;
  addr.sin_port=htons(8896); // 設定 port

  // 設定 Listen
  sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
  // 監聽連線
  listen(sListen, SOMAXCONN);//SOMAXCONN: listening without any limit

  //等待連線
  SOCKADDR_IN clinetAddr;
  while(true)
    {
        printf("...waiting..\n");

        if(sConnect = accept(sListen, (SOCKADDR*)&clinetAddr, &addrlen))
        {
            printf("a connection was found\n");
            printf("server: got connection from %s\n", inet_ntoa(addr.sin_addr));

            //傳送訊息給 client 端
            char *sendbuf = "sending data test";
            send(sConnect, sendbuf, (int)strlen(sendbuf), 0);

        }
    }
}