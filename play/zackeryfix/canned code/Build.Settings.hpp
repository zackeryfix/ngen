/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Project: _build
 * Version: 0.1
 * Usage: Executed
 * Author: zackeryfix@gmail.com
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef __BUILD__SETTINGS_HPP__
#define __BUILD__SETTINGS_HPP__

#include "Build.External.hpp"

using namespace std;

struct Settings {
	map<string, string> KVs;

	Settings(int length) : KVs(length) {
	}

	string& operator[](string key) {
		return KVs[key];
	}
}

struct BuildSettings : Settings {
	static BuildSettings Default() {
		return BuildSettings("../bin", "obj", "include", ".");
	};

	/** 
	 * @brief Constructor.
	 * @param binGenDir Directory where the binary file will be exported.
	 * @param objGenDir Directory where object code will be generated before being linked into a binary.
	 * @param headerDir Directory where all the header files for the component-build are located.
	 * @param sourceDir Directory where all the source files for the component-build are located.
	 */
	BuildSettings(string binGenDir, string objGenDir, string headerDir, string sourceDir, string compilerFlags) :Settings(6) {
		KVs["Refrences"] = "";
		KVs["BinGenDirectory"] = binGenDir;
		KVs["ObjGenDirectory"] = objGenDir;
		KVs["HeaderDirectory"] = headerDir;
		KVs["SourceDirectory"] = sourceDir;
		KVs["CompilerFlags"] = compilerFlags;
	}

	/** 
	 * @brief Constructor.
	 * @param refrences Names of each shared-component that is a dependency of the configuring component.
    * @example auto refs = "NgenFramework[Ngen,Ngen.Diagnostics] MyPackage[Cool,Cool.Aid]"
	 */
	BuildSettings(string refrences, string binGenDir, string objGenDir, string headerDir, string sourceDir, string compilerFlags) :Settings(6) {
		KVs["Refrences"] = refrences;
		KVs["BinGenDirectory"] = binGenDir;
		KVs["ObjGenDirectory"] = objGenDir;
		KVs["HeaderDirectory"] = headerDir;
		KVs["SourceDirectory"] = sourceDir;
		KVs["CompilerFlags"] = compilerFlags;
	}

	/** 
	 * @brief Copy Constructor.
	 */
	BuildSettings(const BuildSettings& copy) : Settings::KVs(copy.Settings::KVs) {
	}
};
#endif
