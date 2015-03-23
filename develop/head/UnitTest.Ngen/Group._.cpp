/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

COPYRIGHT (C) 2014 NGENWARE STUDIOS

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
using namespace Ngen::Diagnostics;

t_testgroup(?);
*/

#include "_External.hpp"

using namespace Ngen;
using namespace Ngen::Diagnostics;

t_testgroup(_);

t_begin_test(_, sizeof_primitive) [] (TestResult& result) {
	if(sizeof(uint8) != 1) {
		result.Error(const_text("sizeof(uint8) != 1"));
	} else if(sizeof(int8) != 1) {
		result.Error(const_text("sizeof(int8) != 1"));
	} else if(sizeof(int16) != 2) {
		result.Error(const_text("sizeof(int16) != 2"));
	} else if(sizeof(uint16) != 2) {
		result.Error(const_text("sizeof(uint16) != 2"));
	} else if(sizeof(int32) != 4) {
		result.Error(const_text("sizeof(int32) != 4"));
	} else if(sizeof(uint32) != 4) {
		result.Error(const_text("sizeof(uint32) != 4"));
	} else if(sizeof(int64) != 8) {
		result.Error(const_text("sizeof(int64) != 8"));
	} else if(sizeof(uint64) != 8) {
		result.Error(const_text("sizeof(uint64) != 8"));
	} else if(sizeof(float32) != 4) {
		result.Error(const_text("sizeof(float32) != 4"));
	} else if(sizeof(float64) != 8) {
		result.Error(const_text("sizeof(float64) != 8"));
	} else if(sizeof(float96) != 16) {
		result.Error(const_text("sizeof(float96) != 16"));
	} else if(sizeof(char8) != 1) {
		result.Error(const_text("sizeof(char8) != 1"));
	} else if(sizeof(char16) != 2) {
		result.Error(const_text("sizeof(char16) != 2"));
	} else if(sizeof(char32) != 4) {
		result.Error(const_text("sizeof(char32) != 4"));
	} else if(sizeof(unknown) != sizeof(word)) {
		result.Error(const_text("sizeof(unknown) != sizeof(word)"));
	}
}
t_end_test

t_begin_test(_, Memory) [] (TestResult& result) {
	Ngen::byte* ptr = Memory::New<Ngen::byte>(10);
	Ngen::byte* bigger = Memory::New<Ngen::byte>(15);
	Ngen::byte* smaller = Memory::New<Ngen::byte>(5);

	Memory::Delete(ptr);
	Memory::Delete(bigger);
	Memory::Delete(smaller);
}
t_end_test

t_begin_test(_, Aliases) [] (TestResult& result) {
	Ngen::byte* ptr = Memory::New<Ngen::byte>(10);
	Ngen::byte* bigger = Memory::New<Ngen::byte>(15);
	Ngen::byte* smaller = Memory::New<Ngen::byte>(5);

	Memory::Delete(ptr);
	Memory::Delete(bigger);
	Memory::Delete(smaller);
}
t_end_test

t_begin_test(_, typenameof_primitive) [] (TestResult& result) {
	if(const_text(typenameof(int8)) != const_text("Ngen$int8")) {
		result.Error(const_text("[int8] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(int16)) != const_text("Ngen$int16")) {
		result.Error(const_text("[int16] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(int32)) != const_text("Ngen$int32")) {
		result.Error(const_text("[int32] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(uint8)) != const_text("Ngen$uint8")) {
		result.Error(const_text("[uint8] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(uint16)) != const_text("Ngen$uint16")) {
		result.Error(const_text("[uint16] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(uint32)) != const_text("Ngen$uint32")) {
		result.Error(const_text("[uint32] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(int64)) != const_text("Ngen$int64")) {
		result.Error(const_text("[int64] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(uint64)) != const_text("Ngen$uint64")) {
		result.Error(const_text("[uint64] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(float32)) != const_text("Ngen$float32")) {
		result.Error(const_text("[float32] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(float64)) != const_text("Ngen$float64")) {
		result.Error(const_text("[float64] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(float96)) != const_text("Ngen$float96")) {
		result.Error(const_text("[float96] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(char16)) != const_text("Ngen$char16")) {
		result.Error(const_text("[char16] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(char32)) != const_text("Ngen$char32")) {
		result.Error(const_text("[char32] Something has gone terribly wrong!!"));
	} else if(const_text(typenameof(wchar)) != const_text("Ngen$wchar")) {
		result.Error(const_text("[wchar] Something has gone terribly wrong!!"));
	}
}
t_end_test
