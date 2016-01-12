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

t_testgroup(class_Algorithm);

t_begin_test(class_Algorithm, BubbleSort) [] (TestResult& result) {
	uword list[] = { 1, 2, 3, 4, 5 };
   uword* ptr = (uword*)&list;

   Algorithm::BubbleSort<uword, EOrderBy::HIGHEST>(ptr, 5);
   uword j = 5;
   for(uword i = 0; i < 5; i++) {
      if(ptr[i] != j--) {
			result.Error(const_string("The collection is not HIGHEST order."));
      }
   }

   Algorithm::BubbleSort<uword, EOrderBy::LOWEST>(ptr, 5);
   j = 1;
   for(uword i = 0; i < 5; i++) {
      if(ptr[i] != j++) {
			result.Error(const_string("The collection is not in LOWEST order."));
      }
   }
}t_end_test

t_begin_test(class_Algorithm, ReverseSort) [] (TestResult& result) {
   uword list[] = { 1, 2, 3, 4, 5 };
   uword* ptr = (uword*)&list;

   Algorithm::ReverseSort<uword>(ptr, 5);
   uword j = 5;
   for(uword i = 0; i < 5; ++i) {
      if(list[i] != j--) {
			result.Error(const_string("The original collection is not in reverse order."));
      }
   }

   Algorithm::ReverseSort<uword>(ptr, 5);
   j = 1;
   for(uword i = 5; i < 5; ++i) {
		if(list[i-1] != j++) {
			result.Error(const_string("The reversed collection is not in the original order."));
      }
   }
}t_end_test
