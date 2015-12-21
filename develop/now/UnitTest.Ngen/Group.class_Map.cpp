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

#include "_External.hpp"

using namespace Ngen;
using namespace Ngen::Diagnostic;

t_testgroup(class_Map);

t_begin_test(class_Map, Add3) [] (TestResult& result) {
	mirror ref;
	Map<mirror, int32> map = Map<mirror, int32>();

	ref = const_mirror("unknown");
	map.Add(ref, 0);

	ref = const_mirror("void");
	map.Add(ref, 1);

	ref = const_mirror(":D");
	map.Add(ref, 2);

	if(!map.ContainsKey(const_mirror(":D"))) {
		result.Error(const_string(":("));
	}

	if(!map.ContainsKey(const_mirror("void"))) {
		result.Error(const_string("'void' did not exist in map!"));
	}

	if(!map.ContainsKey(const_mirror("unknown"))) {
		result.Error(const_string("''unknown' did not exist in map!"));
	}
}t_end_test


t_begin_test(class_Map, Add1ModifyValue) [] (TestResult& result) {
	mirror ref;
	Map<mirror, int32> map = Map<mirror, int32>();

	ref = const_mirror("unknown");
	map.Add(ref, 13);

	if(!map.ContainsKey(ref)) {
		result.Error(const_string("Pair was not added to map!"));
	}

	map[ref] = 100;
	int32 val = map[ref];
	if(val != 100) {
		result.Error("The value was not modified!");
	}
}t_end_test
