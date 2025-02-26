#include<bits/stdc++.h>
#include <windows.h>
#include <cstring>
using namespace std;
string gethostname() {
    char hostname[256];
    DWORD size = sizeof(hostname);
    GetComputerName(hostname, &size);
    string s = hostname;
    return s;
}
