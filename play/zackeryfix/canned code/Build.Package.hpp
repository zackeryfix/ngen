/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Project: _build
 * Version: 0.1
 * Usage: Executed
 * Author: zackeryfix@gmail.com
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef __BUILD__PACKAGE_HPP__
#define __BUILD__PACKAGE_HPP__

#include "Build.Component.hpp"

struct Package : Settings {
	vector<Component> Components;

	Package() : Settings(3), Components(0) {
		KVs["Name"] = "";
		KVs["Version"] = "";
		KVs["Site"] = "";
	}

	Package(const Package& copy) : Settings::KVs(copy.KVs), Components(copy.Components) {
	}

	Package(string path) : Settings(3), Components(0) {
		KVs["Name"] = "";
		KVs["Version"] = "";
		KVs["Site"] = "";
	}
};


string _find_next_structure(string input, string type, string& name) {
	string result = "";

	int loc = result.find(type);
	
	for(int i = loc+type.length(); i < input.length(); ++i) {
		char c = input[i];
		
		if(c != '(') {
			return "ERROR IN PARSER";
		}
	}
	
	return result;
}

#endif
