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
#ifndef __NGEN_CONSOLE_HPP
#define __NGEN_CONSOLE_HPP

#include "Ngen.Typedefs.hpp"
#include "Ngen.Text.hpp"

namespace Ngen {
   /** @brief A static instance used to handle IO for the console input/output streams.
    * @remarks The console is only available for 'Console' applications.
    */
   class ngen_api Console final {
   public:
      /** @brief Appends a null terminated string to the console output stream with a newline terminator.
       * @param str A pointer to the first character of the string being appended.
       */
		static void WriteLine(const text::TChar* str);

      /** @brief Appends a null terminated string to the console output stream.
       * @param str A pointer to the first character of the string being appended.
       */
		static void Write(const text::TChar* str);

      /** @brief Appends a label with the given max width to the console output stream.
       * @param width The maximum number characters allowed for the label.
       * @param str A pointer to the first character of the string being appended.
       */
		static void WriteLabel(uword width, const text::TChar* str);

		/** @brief Ensures all text written to the console is left aligned. */
		static void AlignLeft();

		/** @brief Ensures all text written to the console is right aligned. */
		static void AlignRight();

      /** @brief Appends a null terminated string to the console output stream.
       * @param str A pointer to the first character of the string being appended.
       */
      static void Write(const text& str) {
      	Write(str.Data());
		}

      /** @brief Appends a null terminated string to the console output stream with a newline terminator.
       * @param str A pointer to the first character of the string being appended.
       */
      static void WriteLine(const text& str) {
      	WriteLine(str.Data());
		}

      /** @brief Appends a label with the given max width to the console output stream.
       * @param width The maximum number characters allowed for the label.
       * @param str A pointer to the first character of the string being appended.
       */
      static void WriteLabel(uword width, const text& str) {
      	WriteLabel(width, str.Data());
		}
   };
}
#endif // __NGEN_CONSOLE_HPP
