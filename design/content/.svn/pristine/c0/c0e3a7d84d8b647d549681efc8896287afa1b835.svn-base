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

bool ToConsole(List<TestGroupResult> results);

bool hasArgument(const char** args, uword length, const text& arg) {
	if(length >= 1) {
		for(uword i = 0; i < length; ++i) {
			if(const_text(args[i]) == arg) {
				return true;
			}
		}
	}

	return false;
}

int main(int32 length, const char** args) {
	Console::WriteLine("Ngen Framework (0.1a)");
	Console::WriteLine("Diagnostics & Testing");
	Console::WriteLine("TEST RESULT(S):");

	List<TestGroupResult> results = TestGroup::ExecuteAll();
	if(!ToConsole(results) && hasArgument(args, length, const_text("-P"))) {
		Console::WriteLine("Please review the results, some test have failed.");
		Console::WriteLine("Press any key to continue.");
		std::cin.get();
	}

	std::cin.get();
   return 0;
}

/* Entity.ncc
space MyNamespace {
   public type Entity : GameObject {
      ctor() {
			this->X = 0;
			this->Y = 0;
		}

      dtor() {}

		public real X[auto, protected auto];
		public real Y[auto, protected auto];
   }
}
*/

bool ToConsole(List<TestGroupResult> results) {
	List<TestGroupResult>::Node* group = results.Begin();
	bool pause = false;

	while(!isnull(group)) {
		Console::AlignLeft();
		Console::WriteLine("");
		Console::Write("[TestGroup] >>> ");
		Console::WriteLabel(30, group->Data().Group()->Name());
		Console::WriteLine("");

		List<TestResult> alltests = group->Data().Results();
		List<TestResult>::Node* test = alltests.Begin();

		while(!isnull(test)) {
			Console::Write("|-[Test] >>> ");
			Console::WriteLabel(25, test->Data().Parent()->Name());

			if(test->Data().HasFailed()) {
				Console::Write("FAILED!\n  |-'");
				Console::Write(test->Data().Error());
				Console::WriteLine("'");

				pause = true;
			} else {
				Console::WriteLine("PASS! ");
			}

			test = test->Next();
		}

		group = group->Next();
	}

	return pause;
}

