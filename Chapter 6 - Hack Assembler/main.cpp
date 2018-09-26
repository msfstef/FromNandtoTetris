#include "Parser.h"
#include <iostream>
using namespace std;


int main(){
	Parser a("./text.txt");
	for(int i = 0; i<10; i++){
		a.advance();
		cout<<a.jump()<<endl;
	}
	return 0;
}