#include <fstream>
#include <string>
using namespace std;

class Parser
{
	private:
	ifstream file;
	string curr_line;
	enum LineType {A_COMMAND, C_COMMAND, L_COMMAND};
	
	
	public:
	Parser(const char* file_path);
	bool hasMoreCommands();
	void advance();
	void reset(const char* file_path);
	int commandType();
	string symbol();
	string dest();
	string comp();
	string jump();
};