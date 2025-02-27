#include<bits/stdc++.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include"serget.cpp"
#include"wininfo.cpp"
using namespace std;
int width=1120,height=700;
int sf=2;
WSADATA wsaData;
SOCKET sock;
HDC hdcMem;
sockaddr_in destAddr;
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
int sendmsg(string s){
	const char* data = s.c_str();
	int dataSize = strlen(data);
	int sent = sendto(sock, data, dataSize, 0, (SOCKADDR*)&destAddr, sizeof(destAddr));
	if (sent == SOCKET_ERROR) {
	    cerr << "Send failed: " << WSAGetLastError() << endl;
	    closesocket(sock);
	    WSACleanup();
	    return 1;
	}
	return 0;
}
string sendline(int i){
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
	return s.c_str();
	/*
	const char* data = s.c_str();
	int dataSize = strlen(data);
	int sent = sendto(sock, data, dataSize, 0, (SOCKADDR*)&destAddr, sizeof(destAddr));
	if (sent == SOCKET_ERROR) {
	    cerr << "Send failed: " << WSAGetLastError() << endl;
	    closesocket(sock);
	    WSACleanup();
	    return 1;
	}*/
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
	destAddr.sin_port = htons(port);
	destAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int cnt = 0;
	while(1){
		cnt++;
		//bitblt
	    hdcMem = CreateCompatibleDC(hdc); // 创建兼容的内存DC
	    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width*sf, height*sf); // 创建兼容的位图
	    HGDIOBJ oldBitmap = SelectObject(hdcMem, hBitmap); // 选择位图到内存DC中
	    BitBlt(hdcMem, 0, 0, width*sf, height*sf, hdc, 0, 0, SRCCOPY);
		//
		string st = "";
		for(int i = 0;i<width;i++){
			st+=sendline(i);
			if(i%10==0||i==width-1){
				sendmsg(st);
				st = "";
			}
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
		if(cnt%5==0){
			s = "9998"+gethostname()+";"+to_string(height)+"x"+to_string(width)+";"+to_string(cpuhx());
			const char* data1 = s.c_str();
			int dataSize1 = strlen(data1);
			int sent1 = sendto(sock, data1, dataSize1, 0, (SOCKADDR*)&destAddr, sizeof(destAddr));
			if (sent1 == SOCKET_ERROR) {
			    cerr << "Send failed: " << WSAGetLastError() << endl;
			    closesocket(sock);
			    WSACleanup();
			    return 1;
			}
		}

	}

	closesocket(sock);
	WSACleanup();
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

