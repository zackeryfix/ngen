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
*/
#include "_External.hpp"

using namespace Ngen;
using namespace Ngen::Diagnostics;


t_testgroup(class_Array);

t_begin_test(class_Array, Add2) [] (TestResult& result) {
	Array<uword> nums = Array<uword>(5);

	nums.Add(5);
	nums.Add(10);

	if(nums[0] != 5 || nums[1] != 10) {
		result.Error("The array has reported incorrect values.");
	}

	if(nums.Length() != 2) {
		result.Error("The array has reported an incorrect length.");
	}
}
t_end_test

t_begin_test(class_Array, Add2Remove1) [] (TestResult& result) {
	Array<uword> nums = Array<uword>(5);
	nums.Add(5);
	nums.Add(10);
	nums.Remove(5);

	if(nums[0] != 10) {
		result.Error("The array has reported incorrect values.");
	}
}
t_end_test
