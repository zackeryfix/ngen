#ifndef __NGEN_BITFLAGS_HPP
#define __NGEN_BITFLAGS_HPP

#include "Ngen.Typedefs.hpp"

namespace Ngen {
	/** @brief A structure used to represent an enumeration data type as a set of bit flags.
	 */
	template<typename TEnum>
	class ngen_api BitFlags {
	public:
		/** @brief Default. ()
		 */
		BitFlags() : mCount(TEnum::_COUNT) {
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
			mFlags[target] = value;
			return this;
		}

		/** @brief Toggles the bit-flag of a given enumeration.
		 * @param target The enumeration representing the bit-flag being toggled.
		 */
		BitFlags* Toggle(TEnum target) {
			if(mFlags[target]) {
				mFlags[target] = false;
			} else {
				 mFlags[target] = true;
			}

			return this;
		}

		/** @brief Turns on the bit-flag of a given enumeration.
		 * @param target The enumeration representing the bit-flag being toggled.
		 */
		BitFlags* On(TEnum target) {
			mFlags[target] = true;
			return this;
		}

		/** @brief Turns off the bit-flag of a given enumeration.
		 * @param target The enumeration representing the bit-flag being toggled.
		 */
		BitFlags* Off(TEnum target) {
			mFlags[target] = false;
			return this;
		}

	protected:
		//byte* mFlags; TODO: bit manipulation
		bool[TEnum::_COUNT] mFlags;
		uword mCount;
	};
}

#endif // __NGEN_BITFLAGS_HPP
