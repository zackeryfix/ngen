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
#ifndef __NGEN_KEYVALUEPAIR_HPP
#define __NGEN_KEYVALUEPAIR_HPP

#include "Ngen.Algorithm.hpp"

namespace Ngen {
   /** @brief Represents a key-value pair that is commonly used in look-up tables. */
   template<typename TKey, typename TValue>
   class KeyValuePair {
   public:
      // Construction/Deconstruction -------------------------------------------

      KeyValuePair(TKey key, TValue value) : Key(key), Value(value) {}
      KeyValuePair(const KeyValuePair& copy) : Key(copy.Key), Value(copy.Value) {}

      // Operators -------------------------------------------------------------

      /** @brief Operator. Equal (==). const KeyValuePair<TKey, TValue>& */
      bool operator==(const KeyValuePair<TKey, TValue>& rhs) const {
         if(this == &rhs || (Key == rhs.Key && Value == rhs.Value)) {
            return true;
         }

         return false;
      }

      /** @brief Operator. Not-Equal (!=). const KeyValuePair<TKey, TValue>& */
      bool operator!=(const KeyValuePair<TKey, TValue>& rhs) const {
         if(this != &rhs && (Key != rhs.Key || Value != rhs.Value)) {
            return true;
         }

         return false;
      }

      /** @brief Operator. Assign (=). const KeyValuePair<TKey, TValue>& */
      KeyValuePair<TKey, TValue>& operator=(const KeyValuePair<TKey, TValue>& rhs) {
         if(this == &rhs) {
            return *this;
         }

         Key = rhs.Key;
         Value = rhs.Value;

         return *this;
      }

      // Functions -------------------------------------------------------------

      // Fields ----------------------------------------------------------------

      /** @brief The key used to identify the value. */
      TKey Key;

      /** @brief  The value that is recognized by the key. */
      TValue Value;
   };
}

#endif // __NGEN_KEYVALUEPAIR_HPP
