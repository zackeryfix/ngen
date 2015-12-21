/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

COPYRIGHT (C) 2016 RAZORWARE, LLC

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
/* snippet
#include "_External.hpp"

using namespace Ngen;
using namespace Ngen::Diagnostic;

t_testgroup(?);
*/

#include "_External.hpp"

using namespace Ngen;
using namespace Ngen::Diagnostic;

t_testgroup(_);

t_begin_test(_, sizeof_PrimitiveCheck) [] (TestResult& result) {
	if(sizeof(uint8) != 1) {
		result.Error(const_string("sizeof(uint8) != 1"));
	} else if(sizeof(int8) != 1) {
		result.Error(const_string("sizeof(int8) != 1"));
	} else if(sizeof(int16) != 2) {
		result.Error(const_string("sizeof(int16) != 2"));
	} else if(sizeof(uint16) != 2) {
		result.Error(const_string("sizeof(uint16) != 2"));
	} else if(sizeof(int32) != 4) {
		result.Error(const_string("sizeof(int32) != 4"));
	} else if(sizeof(uint32) != 4) {
		result.Error(const_string("sizeof(uint32) != 4"));
	} else if(sizeof(int64) != 8) {
		result.Error(const_string("sizeof(int64) != 8"));
	} else if(sizeof(uint64) != 8) {
		result.Error(const_string("sizeof(uint64) != 8"));
	} else if(sizeof(float32) != 4) {
		result.Error(const_string("sizeof(float32) != 4"));
	} else if(sizeof(float64) != 8) {
		result.Error(const_string("sizeof(float64) != 8"));
	} else if(sizeof(char8) != 1) {
		result.Error(const_string("sizeof(char8) != 1"));
	} else if(sizeof(char16) != 2) {
		result.Error(const_string("sizeof(char16) != 2"));
	} else if(sizeof(char32) != 4) {
		result.Error(const_string("sizeof(char32) != 4"));
	} else if(sizeof(unknown) != sizeof(word)) {
		result.Error(const_string("sizeof(unknown) != sizeof(word)"));
	}
}
t_end_test

t_begin_test(_, MemoryNew3Delete3) [] (TestResult& result) {
	Ngen::int8* ptr = Memory::New<Ngen::int8>(10);
	Ngen::int8* bigger = Memory::New<Ngen::int8>(15);
	Ngen::int8* smaller = Memory::New<Ngen::int8>(5);

	Memory::Delete(ptr);
	Memory::Delete(bigger);
	Memory::Delete(smaller);
}
t_end_test
