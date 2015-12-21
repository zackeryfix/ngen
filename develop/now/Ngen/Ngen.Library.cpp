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
#include "Ngen.Library.hpp"
#include "Ngen.Map.hpp"

namespace Ngen {
	unknown __libload(const string& path) {
	#	if _tkn_Platform == _tknval_Platform_Windows
		HMODULE lib = LoadLibrary(path.Begin());  // XXX: May require ASCII encoded string
		if (lib == null) {
			THROW(InvalidOperationException("Failed to load library information before being cached."));
		}

		return (unknown)lib;
	#	else
		unknown lib = dlopen(path.Begin(), RTLD_LAZY);  // XXX: May require ASCII encoded string
		if (lib == null) {
			THROW(InvalidOperationException("Failed to load library information before being cached."));
		}

		return lib;
	#	endif
	}

	void __libfree(unknown handle) {
	#	if _tkn_Platform == _tknval_Platform_Windows
		FreeLibrary((HMODULE)handle);
	#	else
		dlclose(handle);
	#	endif
	}

	unknown __libget(unknown handle, const string& signature) {
	#	if _tkn_Platform == _tknval_Platform_Windows
		return (unknown)GetProcAddress((HMODULE)handle, (LPCSTR)signature.Begin()); // XXX: May require ASCII encoded string
	#	else
		return (unknown)dlsym(handle,signature.Begin()); // XXX: May require ASCII encoded string
	#	endif
	}

	auto mNativeCache = Map<mirror, Library>();

	bool Library::Load(const mirror& path, Library*& lib) {
		if(!mNativeCache.ContainsKey(path)) {
			try {
				unknown handle = __libload(path.ToLongName());
				mNativeCache.Add(path, Library(path, handle));
			} catch(...) {
				return false;
			}
		}

		lib = &mNativeCache[path];
		return true;
	}

	bool Library::Unload(const mirror& path) {
		if(mNativeCache.ContainsKey(path)) {
			__libfree(mNativeCache[path].mHandle);
			mNativeCache.Remove(path);
			return true;
		}

		return false;
	}

	bool Library::IsLoaded() const {
		return mNativeCache.ContainsKey(this->mPath);
	}

	unknown Library::mGet(const mirror& signature) const {
		return __libget(this->mHandle, signature.ToLongName());
	}
}
