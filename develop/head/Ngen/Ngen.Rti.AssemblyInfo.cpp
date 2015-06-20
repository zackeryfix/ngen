/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

Copyright (c) 2013 Ngeneers Inc.

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
*

#include "Ngen.Rti.TypeInfo.hpp"

namespace Ngen {
	namespace Rti {
			class AssemblyReference {
	public:
		AssemblyReference(AssemblyInfo* info) : mAssembly(info), mReference(0) {
		}
		AssemblyReference(const AssemblyReference& copy) : mAssembly(copy.mAssembly), mReference(mReference) {
		}

		bool Dereference() {
			if(isnull(mReference) || mReference->Current() == 0) {
				return true;
			} else {
				mReference->Decrement();
			}
		}

		AssemblyInfo* mAssembly;
		Reference* mReference;
	};

	typedef Map<mirror, AssemblyInfo*> AssemblyMap;
	typedef Map<AssemblyInfo*, Reference*> AssemblyRefMap;

	AssemblyMap _loadedAssemblies =
	AssemblyRefMap _referencedAssmeblies = AssemblyRefMap();

	}
}
*/