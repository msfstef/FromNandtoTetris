#include "Code.h"
#include <iostream>
using namespace std;

string Code::comp(string comp_mnem){
	return comp_code[comp_mnem];
}

string Code::dest(string dest_mnem){
	return dest_code[dest_mnem];
}

string Code::jump(string jump_mnem){
	return jump_code[jump_mnem];
}