#include<bits/stdc++.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include"serget.cpp"
using namespace std;
int width=1120,height=700;
int sf=2;
WSADATA wsaData;
SOCKET sock;
HDC hdcMem;
sockaddr_in destAddr;
int sendline(int i){
	string s="";
	s+=char(i/1000+'0');
	s+=char((i%1000)/100+'0');
	s+=char((i%100)/10+'0');
	s+=char(i%10+'0');
	//cout<<"send line "<<s<<endl;
	for(int j = 0;j<height;j++){
		//rgb t = getrgb(i*sf,j*sf);
		rgb t ;
		t.setref(GetPixel(hdcMem, i*sf,j*sf));
		s+=t.to64color();
	}
	const char* data = s.c_str();
	int dataSize = strlen(data);
	int sent = sendto(sock, data, dataSize, 0, (SOCKADDR*)&destAddr, sizeof(destAddr));
	if (sent == SOCKET_ERROR) {
	    cerr << "Send failed: " << WSAGetLastError() << endl;
	    closesocket(sock);
	    WSACleanup();
	    return 1;
	}
	//if(i%25==0) cout<<"send:"<<i<<" size:"<<dataSize<<endl;
}
int sendudp(){
	int result = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (result != 0) {
	    cerr << "WSAStartup failed: " << result << endl;
	    return 1;
	}
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) {
	    cerr << "Could not create socket: " << WSAGetLastError() << endl;
	    WSACleanup();
	    return 1;
	}
	ZeroMemory(&destAddr, sizeof(destAddr));
	destAddr.sin_family = AF_INET;
	destAddr.sin_port = htons(12345);
	destAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	while(1){
		//bitblt
	    hdcMem = CreateCompatibleDC(hdc); // 创建兼容的内存DC
	    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width*sf, height*sf); // 创建兼容的位图
	    HGDIOBJ oldBitmap = SelectObject(hdcMem, hBitmap); // 选择位图到内存DC中
	    BitBlt(hdcMem, 0, 0, width*sf, height*sf, hdc, 0, 0, SRCCOPY);
		//
		for(int i = 0;i<width;i++){
			sendline(i);
		}
		string s = "9999"+currentDateToString();
		const char* data = s.c_str();
		int dataSize = strlen(data);
		int sent = sendto(sock, data, dataSize, 0, (SOCKADDR*)&destAddr, sizeof(destAddr));
		if (sent == SOCKET_ERROR) {
		    cerr << "Send failed: " << WSAGetLastError() << endl;
		    closesocket(sock);
		    WSACleanup();
		    return 1;
		}
		Sleep(50);
	}

	closesocket(sock);
	WSACleanup();
}
#include<fstream>
bool ishide = 0;
int readinfo(){
	ifstream ifs("sendinfo.txt");
	string s;
	ifs>>width>>height>>sf>>s>>ishide;
	cout<<"is send to:"<<s<<endl;
	ifs.close();
}
#include<windows.h>
int hidewin(){
	HWND hwnd =  GetForegroundWindow();
    if (hwnd == NULL) {
        MessageBox(NULL, "Window not found!", "Error", MB_ICONERROR);
        return 0;
    }
    ShowWindow(hwnd, SW_HIDE);
}
int main(){
	readinfo();
	if(ishide)hidewin();
	setup();
	sendudp();
	return 0;
}

