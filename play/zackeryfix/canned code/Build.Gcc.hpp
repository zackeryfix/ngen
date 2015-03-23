/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Project: build
 * Version: 0.1
 * Usage: Executed
 * Author: zackeryfix@gmail.com
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


//! Code is conditioned for correct arguments (todo: D.P.I.)

#ifndef __BUILD__GCC_HPP__
#define __BUILD__GCC_HPP__

#include "Build.Package.hpp"

using namespace std;

struct GnuCodeCompiler {
   const char* CMD = "g++";

	string Flags;
	string PackageDirectory;
	vector<string> SourceFiles;
	vector<string> IncludePaths;
	vector<string> LinkerPaths;
	vector<string> LinkerObjects;
	map<string, string> SourceFileFlags;

	GnuCodeCompiler(string packageDir) : PackageDirectory(packageDir) {
		Package package = Package(packageDir);


	}

	string CompileSourceFile(string inputCpp, string outputObj) const {
		string result = "";
		string cmd = CMD;
		cmd.append(" ");

		string include_switch = _createSwitchList("-I", IncludePaths);
		string library_switch = _createSwitchList("-L", LinkerPaths);
		

		return result;
   }

	string _createSwitchList(string switchChar, vector<string> args) const {
		if(args.length() <= 0) {
			return "";
		}

		string switchList = "";

		for(int i = 0; i < args.length(); ++i) {
			if(args[i].length <= 0) {
				continue;
			}

			string tmp = switchChar;
			tmp.append(args[i]);
			switchList.append(tmp);
		}

		return switchList;
	}
};

#endif
