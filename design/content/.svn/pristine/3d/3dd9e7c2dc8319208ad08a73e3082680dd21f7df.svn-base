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
#ifndef __NGEN_REFERENCECOUNT_HPP
#define __NGEN_REFERENCECOUNT_HPP

namespace Ngen {
   /** @brief A class that maintains the reference count of an object instance. */
   class Reference {
   public:
      /** @brief Constructor. Default. */
      Reference() : mIsValid(true), mCount(0) {}

      /** @brief Increments the reference count by one. */
      Reference& Increment() {
         mCount++;
         return *this;
      }

      /** @brief Decrements the reference count by one. */
      Reference& Decrement() {
         mCount--;
         return *this;
      }

      /** @brief Gets the current reference count. */
      uword Current() const {
         return mCount;
      }

      void IsValid(bool validity) {
			mIsValid = validity;
      }

      bool IsValid() const {
			return mIsValid;
      }

	protected:
		bool mIsValid;
      uword mCount;

   };
}
#endif // __NGEN_REFERENCECOUNT_HPP
