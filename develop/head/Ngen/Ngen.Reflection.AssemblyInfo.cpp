/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

COPYRIGHT (C) 2014 NGENWARE

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "Ngen.Reflection.TypeInfo.hpp"

namespace Ngen {
	namespace Reflection {
      EAttributeBinding AssemblyInfo::AttributeBinding = EAttributeBinding::AssmeblyBound;

		typedef Map<mirror, AssemblyInfo*> MirrorAssemblyInfoMap;
		typedef Map<AssemblyInfo*, Reference*> AssemblyInfoReferenceMap;
		typedef Map<AssemblyInfo*, StaticDelegate<const mirror&> > AssemblyLOADMap;
		typedef Map<AssemblyInfo*, StaticDelegate<const mirror&> > AssemblyUNLOADMap;

		const char8* mRTI_LOADASSEMBLY = "_RTI_LOADASSEMBLY";
		const char8* mRTI_UNLOADASSEMBLY = "_RTI_UNLOADASSEMBLY";

		MirrorAssemblyInfoMap _loadedAssemblies = MirrorAssemblyInfoMap();
		AssemblyInfoReferenceMap _referencedAssmeblies = AssemblyInfoReferenceMap();

		Assembly* _call_reference_assembly(const mirror& library)

		Assmebly::Reference(const mirror& libraryPath, const mirror& assemblyName) {
			Library* library = null;

			if(!Library::Load(libraryPath, inref library)) {
				THROW(InvalidOperationException("Unable to reference assembly because the library could not be loaded."))
			}

			auto _rti_loadassembly = (StaticDelegate<const mirror&, Assembly*&>)library->
												Get(mRTI_LOADASSEMBLY);

			auto _rti_unloadassembly = (StaticDelegate<const mirror&, Assembly*&>)library->
												Get(mRTI_UNLOADASSEMBLY);


		}

	}
}
/**/
