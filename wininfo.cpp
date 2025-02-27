#include<bits/stdc++.h>
#include <windows.h>
#include <cstring>
#pragma once
using namespace std;
string gethostname() {
    char hostname[256];
    DWORD size = sizeof(hostname);
    GetComputerName(hostname, &size);
    string s = hostname;
    return s;
}

string currentDateToString() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H:%M:%S", timeinfo);
	std::string str(buffer);

	return str;
}

int cpuhx(){
	SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwNumberOfProcessors;
}
string cpuinfo(){
	SYSTEM_INFO si;
    GetSystemInfo(&si);
    switch (si.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            return "amd64";
        case PROCESSOR_ARCHITECTURE_MIPS:
            return "mips";
        case PROCESSOR_ARCHITECTURE_ALPHA:
            return "alpha";
        case PROCESSOR_ARCHITECTURE_PPC:
            return "ppc";
        case PROCESSOR_ARCHITECTURE_SHX:
            return "shx";
        case PROCESSOR_ARCHITECTURE_IA64:
            return "ia64";
        case PROCESSOR_ARCHITECTURE_ALPHA64:
            return "alpha64";
        case PROCESSOR_ARCHITECTURE_MSIL:
            return "msil";
        case PROCESSOR_ARCHITECTURE_INTEL:
            return "intel";
        case PROCESSOR_ARCHITECTURE_ARM:
            return "arm";
        default:
            return to_string(si.wProcessorArchitecture);
    }
}
