#include "Parser.h"
using namespace std;

Parser::Parser(const char* file_path){
	file.open(file_path);
}

bool Parser::hasMoreCommands(){
	char next_char = file.peek();
	if(next_char==EOF){
		return false;
	} else {
		return true;
	}
}


void Parser::advance(){
	getline(file,curr_line);
	
	// Remove comments.
	size_t comm_pos = curr_line.find("//");
	if (comm_pos != string::npos) {
		curr_line = curr_line.substr(0,comm_pos);
	}
	
	// Trim line of whitespaces.
	while(curr_line.size() && isspace(curr_line.back())){
        curr_line.pop_back();
	}
	while(curr_line.size() && isspace(curr_line.front())){
        curr_line.erase(curr_line.begin());
	}
}

void Parser::reset(const char* file_path){
	file.close();
	file.open(file_path);
}

#include <iostream>
int Parser::commandType(){
	if (curr_line[0] == '@') {
		return A_COMMAND;
	} else if (((curr_line.find('=') != string::npos) || 
				(curr_line.find(';') != string::npos)) &&
				(curr_line[0]!='/')) {
		return C_COMMAND;
	} else {
		return L_COMMAND;
	}
}


string Parser::symbol(){
	if (commandType() == A_COMMAND) {
		return curr_line.substr(1);
	} else if (commandType() == L_COMMAND) {
		size_t leftpar = curr_line.find('(');
		if(leftpar==0){
			size_t rightpar = curr_line.find(')');
			return curr_line.substr(leftpar+1,rightpar-leftpar-1);
		} else {
			throw invalid_argument("Comment or empty line.");
		}
	} else {
		throw invalid_argument("Line was not an A or L command.");
	}
}


string Parser::dest(){
	if (commandType() == C_COMMAND) {
		int eq_pos = curr_line.find('=');
		if (eq_pos != string::npos) {
			return curr_line.substr(0,eq_pos);
		} else {
			return "";
		}
	} else {
		throw invalid_argument("Line was not a C command.");
	}
}


string Parser::comp(){
	if (commandType() == C_COMMAND) {
		size_t eq_pos = curr_line.find('=');
		size_t sc_pos = curr_line.find(';');
		

		if (eq_pos != string::npos && sc_pos != string::npos) {
			// Zero indexing and difference.
			return curr_line.substr(eq_pos+1, sc_pos-eq_pos-1);
		} else if (eq_pos != string::npos && sc_pos == string::npos ) {
			return curr_line.substr(eq_pos+1);
		} else if (eq_pos == string::npos && sc_pos != string::npos) {
			return curr_line.substr(0,sc_pos);
		}
	} else {
		throw invalid_argument("Line was not a C command.");
	}
}


string Parser::jump(){
	if (commandType() == C_COMMAND) {
		int sc_pos = curr_line.find(';');
		if (sc_pos != string::npos) {
			// If a jump command exists, it spans 3 chars.
			// Magic number, but protects from whitespaces.
			return curr_line.substr(sc_pos+1, 3);
		} else {
			return "";
		}
	} else {
		throw invalid_argument("Line was not a C command.");
	}
}