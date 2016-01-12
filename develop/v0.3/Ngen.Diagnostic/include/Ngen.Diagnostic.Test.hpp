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
#ifndef __NGEN_DIAGNOSTIC_TEST_HPP
#define __NGEN_DIAGNOSTIC_TEST_HPP

#include "Ngen.Diagnostic.TestResult.hpp"
#include "Ngen.Diagnostic.TestGroup.hpp"

namespace Ngen {
	namespace Diagnostic {
		class TestGroup;

		/** @brief A single unit test within a group of tests.
		*/
		class ngen_diagnostic_api Test {
		public:
			/** @brief Constructor. Default. Invalid.
			*/
			Test() : mId(), mFunc() {}

			/** @brief Constructor. (const string&, StaticDelegate<TestResult&>)
			 * @param id The string used to identify the test.
			 * @param func The static delegate of the function representing the test.
			 */
			Test(const string& id, VoidStaticDelegate<TestResult&> func);

			/** @brief Constructor. (TestGroup*, const string&, StaticDelegate<TestResult&>)
			 * @param group The test-group that the test will belong to.
			 * @param id The string used to identify the test.
			 * @param func The static delegate of the function representing the test.
			 */
			Test(TestGroup* group, const string& id, VoidStaticDelegate<TestResult&> func);

			/** @brief Copy constructor. (const Test&)
			 */
			Test(const Test& copy) : mId(copy.mId), mFunc(copy.mFunc), mGroup(copy.mGroup) {}

			/** @brief operator=(const Test&) */
			Test& operator=(const Test& rhs) {
				if(this == &rhs) {
					return *this;
				}

				mId = rhs.mId;
				mFunc = rhs.mFunc;
				mGroup = rhs.mGroup;
			}

			/** @brief operator==(const Test&) */
			bool operator==(const Test& rhs) const {
				return mId == rhs.mId;
			}

			/** @brief operator!=(const Test&) */
			bool operator!=(const Test& rhs) const {
				return mId != rhs.mId;
			}

			/** @brief Executes the test function passing in a reference to a test-result object.
			 * @param result The result that can be internally set by the testing function.
			 */
			void Execute(TestResult& result) {
				try {
					mFunc.Call(result);
				} catch(Exception& e) {
					result.Error(&e);
				}
			}

			string& Name() {
				return mId;
			}

			TestGroup* Parent() const {
				return mGroup;
			}
		protected:
			string mId;
			VoidStaticDelegate<TestResult&> mFunc;
			TestGroup* mGroup;
		};
	}

	/** @brief A macro used to create a test.  Must have matching t_end_test macro.
	 * @example
	 * t_begin_test(MyGroup, MyTest) [] (TestResult& result) {
	 *		...
	 * }
	 * t_end_test
	 */
#	define t_begin_test(group, name) Test _test_##group##name = Test(TestGroup::Get(string(#group, true)), string(#name, true), VoidStaticDelegate<TestResult&>(

	/** @brief A macro used to create a test within the DEFAULT test-group. Must have matching t_end_test macro.
	 * @example
	 * t_default_test(MyTest) [] (TestResult& result) {
	 *		...
	 * }
	 * t_end_test
	 */
#	define t_default_test(name) Test _test_DEFAULT##name = Test(TestGroup::Get(string("DEFAULT", true)), string(#name, true), VoidStaticDelegate<TestResult&>(

	/** @brief A macro used to end a test. Must have matching t_begin_test or t_default_test macro.*/
#	define t_end_test ));
}
#endif // __NGEN_DIAGNOSTICS_TEST_HPP
