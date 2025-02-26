#include<bits/stdc++.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include<graphics.h>
#include <easyx.h>
#include"serget.cpp"
using namespace std;
int width=1120,height=700;
int sf = 1;
#include<fstream>
bool ishide = 0;
int port = 12345;
int readinfo(){
	ifstream ifs("sendinfo.txt");
	string s;
	ifs>>width>>height>>sf>>s>>port>>ishide;
	cout<<"is send to:"<<s<<endl;
	ifs.close();
}
int recvmain(){
	WSADATA wsaData;
    int startupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (startupResult != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    sockaddr_in localAddr;
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = INADDR_ANY;
    localAddr.sin_port = htons(port);
    if (bind(sock, (SOCKADDR*)&localAddr, sizeof(localAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
	char recvBuffer[6800];
	sockaddr_in remoteAddr;
	setlinecolor(BLACK);
	int remoteAddrSize = sizeof(remoteAddr);
	int zhen=0;
    for(int i = 0;;i++){
	    memset(recvBuffer,0,sizeof recvBuffer);
	    int line = 0;
	    int recvResult = recvfrom(sock, recvBuffer, sizeof(recvBuffer), 0, (SOCKADDR*)&remoteAddr, &remoteAddrSize);

	    string s = recvBuffer;
		if (recvResult == SOCKET_ERROR) {
	        cerr << "recvfrom failed: " << WSAGetLastError() << std::endl;
	        closesocket(sock);
	        WSACleanup();
	        return 1;
	    }
	    else{
	    	if(s.length()>=4)line = 1000*(s[0]-'0')+100*(s[1]-'0')+10*(s[2]-'0')+1*(s[3]-'0');
	    	else continue;
	    	//cout<<"recv i:"<<i<<" res:"<<recvResult<<" line:"<<line<<endl;
		}
		if(line==9999){
			zhen++;
			string s1 = "S"+s.substr(4);
			string s2 = "L"+currentDateToString();
			string s3 = to_string(zhen);
			outtextxy(0,height,s1.c_str());
			outtextxy(260,height,s2.c_str());
			outtextxy(507,height,s3.c_str());
			continue;
		}
		if(line==9998){
			zhen++;
			string s1 = s.substr(4);
			outtextxy(550,height,s1.c_str());
			continue;
		}
	    for(int j = 0;j<(recvResult-4)/3;j++){
	    	string t = s.substr(j*3+4,3);
	    	rgb col;
	    	col.set64color(t);
	    	//setfillcolor(col.tocolor());
	    	//fillrectangle(i*sf,j*sf,i*sf+sf,j*sf+sf);
	    	COLORREF cref = col.tocolor();
	    	putpixel(line,j,cref);
			/*
	    	for(int x = 0;x<sf;x++){
	    		for(int y = 0;y<sf;y++){
	    			putpixel(line*sf+x,j*sf+y,cref);
				}
			}*/
		}
	}

	return 0;
}
int main(){
	readinfo();
	initgraph(width,height+24,SHOWCONSOLE);
	settextstyle(24,12,"");
	setup();
	recvmain();
	while(1);
	return 0;
}
