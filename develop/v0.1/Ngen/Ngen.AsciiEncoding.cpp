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
#include "Ngen.AsciiEncoding.hpp"
#include "Ngen.Algorithm.hpp"
#include "Ngen.Text.hpp"

namespace Ngen {
   template<> bool AsciiEncoding::Compare<AsciiEncoding>(const AsciiEncoding::TChar* lhs, const AsciiEncoding::TChar* rhs, uword length) {
      for(uword i = 0; i < length; ++i) {
         if(*(lhs + i) != *(rhs + i)) {
            return false;
         }
      }

      return true;
   }

   template<> void AsciiEncoding::Encode<AsciiEncoding>(const AsciiEncoding::TChar* from, AsciiEncoding::TChar*& at, uword length) {
      Memory::Copy<AsciiEncoding::TChar>(from, at, length);
   }

   template<> void AsciiEncoding::Decode<AsciiEncoding>(AsciiEncoding::TChar*& at, const AsciiEncoding::TChar* from, uword length) {
      Memory::Copy<AsciiEncoding::TChar>(from, at, length);
   }

   bool AsciiEncoding::Compare(const Encoding* rhsEncoding, const byte* lhs, const byte* rhs, uword length) {
      if(this == rhsEncoding) {
         return Algorithm::Compare(lhs, rhs, length);
      }

      return false;
   }

   void AsciiEncoding::Encode(const Encoding* encodeTo, const byte* from, byte*& to, uword length) {
      throw NotImplementedException();
   }

   void AsciiEncoding::Decode(const Encoding* decodeFrom, const byte* from, byte*& to, uword length) {
      throw NotImplementedException();
   }
}
