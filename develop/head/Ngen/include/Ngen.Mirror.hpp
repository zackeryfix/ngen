/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

COPYRIGHT (C) 2014 NGENWARE STUDIOS

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
#ifndef __NGEN_MIRROR_HPP
#define __NGEN_MIRROR_HPP

#include "Ngen.Text.hpp"

namespace Ngen {
	/** @brief A structure used as a hash-code that represents a unique identity.
	 */
	class ngen_api Mirror {
	public:
		/** @brief Constructor. Default.
		 */
		Mirror() : mLongName(text::Empty()), mHashcode(0) {}

		/** @brief Constructor. (const text&).
		 * @param longName The unique identity being representing in the mirror.
		 */
		Mirror(const text& longName) : mLongName(const_text(longName)), mHashcode(longName.ToHashcode()) {}

		/** @brief Constructor. Copy. (const Mirror&).
		 * @param copy The unique identity being representing in the mirror.
		 */
		Mirror(const Mirror& copy) : mLongName(copy.mLongName), mHashcode(copy.mHashcode) {}

		/** @brief Constructor. Copy. (const Mirror&).
		 * @param copy The unique identity being representing in the mirror.
		 */
		Mirror(Mirror&& move) : mLongName((text&&)move.mLongName), mHashcode(move.mHashcode) {}


		/** @brief operator=(const Mirror&). */
		Mirror& operator=(const Mirror& rhs) {
			mHashcode = rhs.mHashcode;
			mLongName = rhs.mLongName;

			return *this;
		}

		/** @brief operator==(const Mirror&). */
		bool operator==(const Mirror& rhs) const {
			return rhs.mHashcode == mHashcode;
		}

		/** @brief operator!=(const Mirror&). */
		bool operator!=(const Mirror& rhs) const {
			return rhs.mHashcode != mHashcode;
		}

		/** @brief Gets the mirror represented as a hash-code. */
		uword ToHashcode() const {
			return mHashcode;
		}

		/** @brief Gets the unique name that generated the hash-code for the mirror. */
		text ToLongName() const {
			return mLongName;
		}
		
	protected:
		text mLongName;
		uword mHashcode;
	};


	typedef Mirror mirror;

#	define const_mirror(s) mirror(text(s, true))

	/** @brief A logic structure used by the trait class for determining if a
    * typename is movable.
    */
	template<typename T> mirror mirrorof() {
 		return mirror(const_text(typenameof(T)));
	};

}


#endif // __NGEN_MIRROR_HPP
