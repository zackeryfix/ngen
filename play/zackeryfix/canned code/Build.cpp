/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Project: _build
 * Version: 0.1
 * Usage: Executed
 * Author: zackeryfix@gmail.com
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Build.External.hpp"

using namespace std;

char* _find_next_structure(const char* input, const char* type, char*& name) {
	char* result = "";

	int loc = result.find(type);
	
	for(int i = loc+type.length(); i < input.length(); ++i) {
		char c = input[i];
		
		if(c != '(') {
			return "ERROR IN PARSER";
		}
	}
	
	return result;
}


int main() {
	string text = "Project(Name) {\n\tComponent(Name) {\n\t\t.Version\t=0.3 } }";
	string n;
	cout << _fns(text, "Component", n);
	cout << endl;
	cin.get();
	return 0;

}
