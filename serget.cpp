#include <windows.h>
#include <wingdi.h>
#include <iostream>
#include<ctime>
#include<iomanip>
#include<chrono>
#pragma comment(lib, "gdi32.lib")
#pragma once
using namespace std;
HDC hdc;
string ch = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+=-";

struct rgb {
	BYTE r,g,b;
	void set(BYTE r1,BYTE g1,BYTE b1) {
		r=r1;
		g=g1;
		b=b1;
	}
	string to64color() {
		string s;
		s+=ch[r/4];
		s+=ch[g/4];
		s+=ch[b/4];
		return s;
	}
	void set64color(string s) {
		if(s.length()<3) return;
		r = ch.find(s[0])*4;
		g = ch.find(s[1])*4;
		b = ch.find(s[2])*4;
	}
	COLORREF tocolor() {
		return RGB(r,g,b);
	}
	void setref(COLORREF color) {
		BYTE blue = GetBValue(color);
		BYTE green = GetGValue(color);
		BYTE red = GetRValue(color);
		set(red,green,blue);
	}
};
int setup() {
	hdc = GetDC(NULL);
	if (hdc == NULL) {
		cerr << "无法获取设备上下文" << endl;
		return 1;
	}
	cout<<"getted hdc\n";
	return 0;
}
string currentDateToString() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
	std::string str(buffer);

	return str;
}
rgb getrgb(int x,int y) {
	COLORREF color = GetPixel(hdc, x, y);
	BYTE blue = GetBValue(color);
	BYTE green = GetGValue(color);
	BYTE red = GetRValue(color);
	rgb res;
	res.set(red,green,blue);
	//cout<<(int)red<<" "<<(int)green<<" "<<(int)blue<<endl;
	return res;
}
