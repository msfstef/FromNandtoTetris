#include <unordered_map>
#include <string>
using namespace std;

class SymbolTable
{
	private:
	unordered_map<string,int> stable {
		{"SP",0x0},
		{"LCL",0x1},
		{"ARG",0x2},
		{"THIS",0x3},
		{"THAT",0x4},
		{"R0",0x0},
		{"R1",0x1},
		{"R2",0x2},
		{"R3",0x3},
		{"R4",0x4},
		{"R5",0x5},
		{"R6",0x6},
		{"R7",0x7},
		{"R8",0x8},
		{"R9",0x9},
		{"R10",0xa},
		{"R11",0xb},
		{"R12",0xc},
		{"R13",0xd},
		{"R14",0xe},
		{"R15",0xf},
		{"SCREEN",0x4000},
		{"KBD",0x6000}
	};
	
	public:
	void addEntry(string symbol, int address);
	bool contains(string symbol);
	int getAddress(string symbol);
	
};