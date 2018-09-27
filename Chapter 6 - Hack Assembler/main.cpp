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
	
	if (file_loc == NULL) {
		cerr << "Not a valid file name." << endl;
		throw runtime_error("Invalid file name");
	}
	
	string compiled(file_loc);
	compiled = compiled.substr(0,compiled.find('.'));
	
	ofstream hackfile;
	hackfile.open("./"+compiled+".hack");
	cout << "Assembling..." <<endl;
	
	
	Code code;
	SymbolTable symbs;
	int mem_cnt = 0x10;
	enum LineType {A_COMMAND, C_COMMAND, L_COMMAND};
	
	Parser pass(file_loc);
	int line_cnt = 0;
	
	
	// Filling symbol table with L-COMMAND symbols.
	while(pass.hasMoreCommands()){
		pass.advance();
		//cout<<pass.commandType()<<endl;
		switch (pass.commandType()){
			case A_COMMAND:
				line_cnt++;
				break;
			
			case C_COMMAND:
				line_cnt++;
				break;
			
			case L_COMMAND:
				{
				try {
				string symbol = pass.symbol();
				if(!symbs.contains(symbol)){
					symbs.addEntry(symbol, line_cnt);
				} else {
					cout<<symbol<<endl;
					throw runtime_error("ROM adddress symbol assigned twice.");
				}
				} catch (invalid_argument) {}
				}
				break;
		}
	}
	
	
	pass.reset(file_loc);
	
	// Filling symbol table with A-COMMAND symbols.
	while(pass.hasMoreCommands()){
		pass.advance();
		switch (pass.commandType()){
			case A_COMMAND:
				{
				string symbol = pass.symbol();
				try {
					stoi(symbol);
				} catch (invalid_argument) {
				if(!symbs.contains(symbol)){
					symbs.addEntry(symbol, mem_cnt);
					mem_cnt++;
				}
				}
				}
				break;
			
			case C_COMMAND:
				break;
			
			case L_COMMAND:
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
				//cout<<curr_symb<<endl;
				try {
					//cout << bitset<16>(stoi(curr_symb)) << endl;
					hackfile << bitset<16>(stoi(curr_symb)) << endl;
				} catch (invalid_argument) {
					int val = symbs.getAddress(curr_symb);
					//cout << bitset<16>(val) << endl;
					hackfile << bitset<16>(val) << endl;
				}
				}
				break;
			
			case C_COMMAND:
				{
				string comp_part = code.comp(pass.comp());
				string dest_part = code.dest(pass.dest());
				string jump_part = code.jump(pass.jump());
				//cout<< pass.comp()<<endl;
				string command_inst = "111" + comp_part + dest_part + jump_part;
				//cout << command_inst << endl;
				hackfile << command_inst << endl;
				}
				break;
			
			case L_COMMAND:
				break;
		}
	}

	hackfile.close();
	cout << "Saved assembled program as "+compiled+".hack." << endl;
	
	return 0;
}
