#include "Parser.h"
#include "Code.h"
#include <iostream>
using namespace std;


int main(){
	Parser a("./test.txt");
	Code b;
	for(int i = 0; i<10; i++){
		a.advance();
		cout<<b.jump(a.jump())<<endl;
	}
	return 0;
}