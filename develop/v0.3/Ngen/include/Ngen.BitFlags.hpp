/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

COPYRIGHT (C) 2016 NGENWARE STUDIOS, LLC

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
#ifndef __NGEN_BITFLAGS_HPP
#define __NGEN_BITFLAGS_HPP

#include "Ngen.Typedefs.hpp"

namespace Ngen {
	/** @brief A structure used to represent an enumeration data type as a set of bit flags.
	 */
	template<typename TEnum>
	class ngen_api BitFlags {
	public:
	   typedef BitFlags<TEnum> TSelf;

		/** @brief Default. ()
		 */
		BitFlags() : mCount((uword)TEnum::_COUNT) {
			Clear();
		}

		/** @brief Turns off all bits in the flag.
		 */
		BitFlags* Clear() {
			for(uword i = 0; i < mCount; ++i) {
				mFlags[i] = false;
			}

			return this;
		}

		/** @brief Sets the bit-flag of a given enumeration.
		 * @param target The enumeration representing the bit-flag being set.
		 * @param value If true, the bit-flag will be turned on, and if false, the
		 * bit-flag will be turned off.
		 */
		BitFlags* Set(TEnum target, bool value) {
			mFlags[(uword)target] = value;
			return this;
		}

		/** @brief Toggles the bit-flag of a given enumeration.
		 * @param target The enumeration representing the bit-flag being toggled.
		 */
		BitFlags* Toggle(TEnum target) {
			if(mFlags[(uword)target]) {
				mFlags[(uword)target] = false;
			} else {
				 mFlags[(uword)target] = true;
			}

			return this;
		}

		/** @brief Turns on the bit-flag of a given enumeration.
		 * @param target The enumeration representing the bit-flag being toggled.
		 */
		BitFlags* On(TEnum target) {
			mFlags[(uword)target] = true;
			return this;
		}

		/** @brief Turns off the bit-flag of a given enumeration.
		 * @param target The enumeration representing the bit-flag being toggled.
		 */
		BitFlags* Off(TEnum target) {
			mFlags[(uword)target] = false;
			return this;
		}

      /** @brief Gets a value that determines if a specific bit-flag has been set.
       */
      bool operator[](TEnum e) const {
         return mFlags[(uword)e];
      }

      /** @brief Gets a value that determines if a specific bit-flag has been set.
       */
      bool operator[](uword e) const {
         return mFlags[e];
      }

      bool operator==(const TSelf& lhs) const {
         for(uword i = 0; i < mCount; ++i) {
            if(mFlags[i] != lhs[i]) {
               return false;
            }
         }

         return true;
      }

      bool operator!=(const TSelf& lhs) const {
         for(uword i = 0; i <  mCount; ++i) {
            if(mFlags[i] != lhs[i]) {
               return true;
            }
         }

         return false;
      }
	protected:
		//byte* mFlags; TODO: bit manipulation
		bool mFlags[(uword)TEnum::_COUNT];
		uword mCount;
	};
}

#endif // __NGEN_BITFLAGS_HPP
