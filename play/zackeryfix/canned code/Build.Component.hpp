/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Project: _build
 * Version: 0.1
 * Usage: Executed
 * Author: zackeryfix@gmail.com
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef __BUILD__COMPONENT_HPP__
#define __BUILD__COMPONENT_HPP__

#include "Build.Settings.hpp"

struct Component {
	string Name;
	string Version;
	string Author;
	string Usage;

   BuildSettings Build;

	
	/** 
	 * @brief Constructor.
	 * @param flags Custom compiler flags for the component.
	 */
	Component(string name, string version, string author, string usage, BuildSettings build, CompilerSettings compiler) : 
		Name(name), Version(version), Author(author), Usage(usage),{
	}

	/** 
	 * @brief Constructor.
	 * @param refrences Names of each shared-component that is a dependency of the configuring component.
    * @example auto refs = "NgenFramework[Ngen,Ngen.Diagnostics] MyPackage[Cool,Cool.Aid]"
	 */
	Component(const BuildSettings& copy) :
		References(copy.References), DirBinary(copy.DirBinary), DirCreate(copy.DirCreate), 
		DirHeader(copy.DirHeader), DirSource(copy.DirSource) {
	}


	
};

#endif
