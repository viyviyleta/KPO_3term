#include <fstream>
#include<iostream>
#include <vector>
#define HEADER ".586\n.MODEL FLAT, stdcall\nincludelib kernal32.lib\nExitProcess PROTO : DWORD\n.STACK 4096\n.CONST\n.DATA\nstdout DWORD ?\n"
#define FOOTER "\n.CODE\nmain PROC\nSTART:\npush 0\ncall ExitProcess\nmain ENDP\nend main\n"

using namespace std;

class Deserializer {
public:
	static vector<pair<int, char*>> Deserialize(ifstream& rd);
};