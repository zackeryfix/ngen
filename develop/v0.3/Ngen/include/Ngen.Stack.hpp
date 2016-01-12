/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

COPYRIGHT (C) 2014 NGENWARE

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
#ifndef __NGEN_STACK_HPP
#define __NGEN_STACK_HPP

#include "Ngen.Array.hpp"

namespace Ngen {
   template<typename T>
   class ngen_api Stack {
   public:
      typedef Stack<T> TSelf;

      Stack() : mData() {}
      Stack(uword capacity) : mData(capacity) {}
      Stack(T* copy, uword length, bool readOnly = true) : mData(copy, length, readOnly) {}
		Stack(const TSelf& copy) : mData(copy) {}
		Stack(const TSelf& copy, bool readOnly) : mData(copy, readOnly) {}
		Stack(TSelf&& move) : mData(move) {}

      uword Length() const {
         return mData.Length();
      }

      uword Capacity() const {
         return mData.Capacity();
      }

      void Push(const T& item) {
         mData.Add(item);
      }

      T& Pop() {
         T* result = mData[mData.Length()-1];
         mData.RemoveAt(mData.Length()-1);
         return *result;
      }

      bool IsReadonly() const {
         return mData.IsReadony();
      }

   protected:
      Array<T> mData;
   };


   /** @brief
    *
   class ngen_api Callstack {
   public:
      typedef Array<unknown> TUnknownArray;

      Callstack() : mMethodCalls() {}

      void Push(MethodInfo* method) {
         mMethodCalls.Push(method);
      }

      unknown Next(unknown self, const TUnknownArray& params) {
         Delegate* call = mMethodCalls.Pop();
         return call(self, params,Begin());
      }

      template<typename TOwner, typename TReturn typename... TParms>
      Object Next(Object self, const Array<Object>& params) {
         Delegate* call = mMethodCalls.Pop();

      }
   protected:
      Stack<Delegate*> mMethodCalls;
   };
   */
}
#endif
