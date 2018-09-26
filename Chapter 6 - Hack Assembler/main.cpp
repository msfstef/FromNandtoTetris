#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"
#include <iostream>
#include <typeinfo>
#include <bitset>
using namespace std;

//Utility function to check str to int.
bool is_number(const string& s);

int main(){
	char* file_loc;
	cin >> file_loc;
	
	Code code;
	SymbolTable symbs;
	int mem_cnt = 0x10;
	enum LineType {A_COMMAND, C_COMMAND, L_COMMAND};
	
	Parser pass(file_loc);
	int line_cnt = 0;
	
	
	// Filling symbol table
	while(pass.hasMoreCommands()){
		pass.advance();
		switch (pass.commandType()){
			case A_COMMAND:
				{
				string symbol = pass.symbol();
				if(!symbs.contains(symbol)){
					symbs.addEntry(symbol, mem_cnt);
					mem_cnt++;
				}
				line_cnt++;
				}
				break;
			
			case C_COMMAND:
				line_cnt++;
				break;
			
			case L_COMMAND:
				{
				string symbol = pass.symbol();
				if(!symbs.contains(symbol)){
					symbs.addEntry(symbol, line_cnt);
				} else {
					throw runtime_error("ROM adddress symbol assigned twice.");
				}
				}
				break;
		}
	}
	
	
	pass.reset(file_loc);
	
	
	// Replacing symbols with numeric values
	while(pass.hasMoreCommands()){
		pass.advance();
		switch (pass.commandType()){
			case A_COMMAND:
				{
				string curr_symb = pass.symbol();
				bool isint = is_number(curr_symb);
				cout<<is_number(curr_symb)<<endl;
				cout<<curr_symb<<endl;
				if(isint){
					cout<<stoi(curr_symb)<<endl;
					cout << bitset<16>(stoi(curr_symb)) << endl;
				} else {
					int val = symbs.getAddress(curr_symb);
					cout << bitset<16>(val) << endl;
				}
				}
				break;
			
			case C_COMMAND:
				{
				string dest_part = code.dest(pass.dest());
				string comp_part = code.comp(pass.comp());
				string jump_part = code.jump(pass.jump());
				string command_inst = dest_part + comp_part + jump_part;
				cout << bitset<16>(stoi(command_inst)) << endl;
				}
				break;
			
			case L_COMMAND:
				break;
		}
	}

	
	return 0;
}


bool is_number(const string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !isdigit(c); }) == s.end();
}