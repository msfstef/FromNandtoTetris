#include "SymbolTable.h"
using namespace std;

void SymbolTable::addEntry(string symbol, int address){
	stable.insert({symbol,address});
}

bool SymbolTable::contains(string symbol){
	if(stable.count(symbol)){
		return true;
	} else {
		return false;
	}
}

int SymbolTable::getAddress(string symbol){
	int lookup = stable[symbol];
	if(lookup>0){
		return lookup;
	} else if (symbol == "R0" || symbol == "SP") {
		return lookup;
	} else {
		throw runtime_error("No address for given symbol");
	}
}