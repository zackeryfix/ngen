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
#ifndef __NGEN_DIAGNOSTIC_TESTGROUP_HPP
#define __NGEN_DIAGNOSTIC_TESTGROUP_HPP

#include "Ngen.Diagnostic.TestGroupResult.hpp"

namespace Ngen {
	namespace Diagnostic {
		class Test;

		class ngen_diagnostic_api TestGroup {
		public:
			TestGroup(const string& id) : mId(string(id)), mTests() {
				if(sGroups.Contains(this)) {
					throw InvalidOperationException("The TestGroup {0} already exists!");
				}

				sGroups.Add(this);
			}

			TestGroup(const TestGroup& copy) : mId(copy.mId), mTests(copy.mTests) {}

			static TestGroup* Default() {
				return &sDefault;
			}

			static TestGroup* Get(const string& id) {
				List<TestGroup*>::Node* i = sGroups.Begin(0);
				while(!isnull(i)) {
					if(i->Data()->mId == id) {
						return i->Data();
					}

					i = i->Next();
				}

				throw InvalidOperationException("The TestGroup {0} does not exist!");
			}

			bool operator==(const TestGroup& rhs) const {
				return mId == rhs.mId;
			}

			bool operator==(const string& rhs) const {
				return mId == rhs;
			}

			void Add(Test* test) {
				for(uword i = 0; i < mTests.Length(); ++i) {
					if(mTests[i] == test) {
						return;
					}
				}

				mTests.Add(test);
			}

			const string& Name() {
				return mId;
			}

			List<TestResult> Execute();
			static List<TestGroupResult> ExecuteAll();

		protected:
			TestGroup() : mId(), mTests() {}

			string mId;
			List<Test*> mTests;

			static ngen_diagnostic_api List<TestGroup*> sGroups;
			static ngen_diagnostic_api TestGroup sDefault;
		};
	}

#	define t_testgroup(name) TestGroup _testgroup_##name = TestGroup(string(#name, true))
}

#endif // __NGEN_DIAGNOSTICS_TESTGROUP_HPP
