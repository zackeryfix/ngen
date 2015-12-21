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
#ifndef __NGEN_DIAGNOSTICS_TESTRESULT_HPP
#define __NGEN_DIAGNOSTICS_TESTRESULT_HPP

#include "Build.Diagnostics.Logic.hpp"
#include "Ngen.Exception.hpp"
#include "Ngen.StaticDelegate.hpp"

namespace Ngen {
	namespace Diagnostics {
		class Test;

		class TestResult {
		public:
			TestResult() : mParent(0), mFailed(false), mError() {}
			TestResult(Test* parent) : mParent(parent), mFailed(false), mError() {}
			TestResult(const TestResult& copy) : mParent(copy.mParent), mFailed(copy.mFailed), mError(copy.mError) {}


			const text& Error() const {
				return mError;
			}

			void Error(const text& error) {
				this->Fail();
				mError = text(error);
			}

			void Error(Exception* error) {
				if(isnull(error)) {
					return;
				}

				Error(const_text(error->what()));
			}

			bool HasFailed() const { return mFailed; }

			void Fail() {
				mFailed = true;
			}

			Test* Parent() const { return mParent; }

		protected:
			Test* mParent;
			bool mFailed;
			text mError;
		};
	}
}

#endif // __NGEN_DIAGNOSTICS_TESTRESULT_HPP
