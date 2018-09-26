#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"
#include <iostream>
using namespace std;


int main(){
	Parser a("./test.txt");
	Code b;
	SymbolTable c;
	for(int i = 0; i<10; i++){
		a.advance();
		cout<<b.jump(a.jump())<<endl;
		cout<<c.contains("SCREN")<<endl;
	}
	string test;
	cin >> test;
	cout << c.getAddress(test)<<endl;
	cin >> test;
	cout << c.contains(test)<<endl;
	return 0;
}