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

t_testgroup(class_List);

t_begin_test(class_List, Add1Remove1) [] (TestResult& result) {
	List<uword> list;

   list.Add(89);
   if(list.Length() != 1 || (list.Length() >= 1 && list[0]!= 89)) {
		result.Error(const_text("The item '89' was not added."));
		return;
   }

   list.Remove(89);
   if(list.Length() > 0) {
		result.Error(const_text("The item '89' did not get removed."));
		return;
   }
}t_end_test

t_begin_test(class_List, Add2Remove1) [] (TestResult& result) {
	List<uword> list;

   list.Add(89);
   if(list.Length() != 1 || (list.Length() >= 1 && list[0]!= 89)) {
		result.Error(const_text("The item '89' was not added."));
		return;
   }

   list.Add(90);
   if(list.Length() != 2 || (list.Length() >= 1 && list[1]!= 90)) {
		result.Error(const_text("The item '90' was not added."));
		return;
   }

   list.Remove(89);
   if(list.Length() != 1 || (list.Length() >= 1 && list[0]!= 90)) {
		result.Error(const_text("The item '89' did not get removed."));
		return;
   }
}t_end_test

t_begin_test(class_List, AddSame2Remove1) [] (TestResult& result) {
	List<uword> list;

   list.Add(89);
   if(list.Length() != 1 || (list.Length() >= 1 && list[0]!= 89)) {
		result.Error(const_text("The item '89[1]' was not added."));
		return;
   }

   list.Add(89);
   if(list.Length() != 2 || (list.Length() >= 1 && list[1]!= 89)) {
		result.Error(const_text("The item '89[2]' was not added."));
		return;
   }

   list.Remove(89);
   if(list.Length() == 0) {
		result.Error(const_text("Both items '89[1], 89[2]' were removed."));
		return;
   }
   if(list.Length() != 1 || (list.Length() >= 1 && list[0]!= 89)) {
		result.Error(const_text("The item '89[1]' did not get removed."));
   }
}t_end_test

t_begin_test(class_List, AddSame2RemoveAny) [] (TestResult& result) {
	List<uword> list;

   list.Add(89);
   if(list.Length() != 1 || (list.Length() >= 1 && list[0]!= 89)) {
		result.Error(const_text("The item '89[1]' was not added."));
		return;
   }

   list.Add(89);
   if(list.Length() != 2 || (list.Length() >= 2 && list[1]!= 89)) {
		result.Error(const_text("The item '89[2]' was not added."));
		return;
   }

   list.RemoveAny(89);
   if(list.Length() != 0) {
		result.Error(const_text("Both items '89[1], 89[2]' did not get removed."));
   }
}t_end_test

t_begin_test(class_List, Add1Remove2) [] (TestResult& result) {
	List<uword> list;

	list.Add(89);
   if(list.Length() != 1 || (list.Length() >= 1 && list[0]!= 89)) {
		result.Error(const_text("The item '89' was not added."));
		return;
   }

   list.Remove(89);
   if(list.Length() > 0) {
		result.Error(const_text("The item '89' did not get removed."));
		return;
   }

   try {
      list.Remove(89);
   } catch(const InvalidOperationException& e) {
      return;
   }

	result.Error("Call to 'list.Remove' did not throw an InvalidOperationException exception.");
}t_end_test
