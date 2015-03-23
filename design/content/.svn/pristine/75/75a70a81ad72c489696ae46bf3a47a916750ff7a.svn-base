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
#ifndef __NGEN_TEXT_HPP
#define __NGEN_TEXT_HPP

#include "Ngen.Encoding.hpp"
#include "Ngen.AsciiEncoding.hpp"
#include "Ngen.Array.hpp"

namespace Ngen {
	/** @brief A encoded string of bytes representing human readable text.
	 * By default, the framework implements the following text encodings:
	 * @li AsciiEncoding 	ascii
	 * @li UnicodeEncoding 	unicode
	 *
	 * The text encoding used by the framework is determined at compile-time, and
	 * to keep code consistent, it is recommended to use the 'text' type-definition.
	 *
	 * To declare text as constant (ie. read-only), use the const_text type-definition, or
	 * an overloaded constructor that utilizes a 'readOnly' flag:
	 *
	 * @code
	 * text abc = const_text("Abc");  // read-only
	 * text Abc = text(abc, false);   // writeable copy of 'abc'
	 *
	 * Abc += abc; // == "Abcabc"
	 * abc += Abc; // !InvalidOperationException - 'abc' is read-only!
	 * @endcode
	 */
   template<typename TEncoding>
   class ngen_api Text {
   public:
		/** @brief The character data-type used by the encoded text. */
      typedef typename TEncoding::TChar TChar;
      /** @brief A typedef representing the class without template decorations. */
      typedef Text<TEncoding> TSelf;

		/** @brief Constructor. Default. */
      Text() : mData(null), mLength(0), mCapacity(0), mIsReadonly(true) {}

		/** @brief Constructor. (uword). Creates an encoded text instance using the given capacity. */
      explicit Text(uword capacity) : mData(Memory::New<TChar>(capacity)), mLength(1), mCapacity(capacity), mIsReadonly(false) {
			TEncoding::EndOfString(mData);
      }

		/** @brief Constructor. (TChar*, bool). Create an encoded text instance using the given character array and read-only flag.
		 * @param str A null terminated string of characters .
		 * @param readOnly Determines if the text will copy the string, or reference it.
		 * @remarks This constructor should only be used compile-time char-string literals.
		 */
      Text(const TChar* str, bool readOnly = false) : mData(null), mLength(0), mCapacity(0), mIsReadonly(readOnly) {
         mLength = TEncoding::Count(str);
         mCapacity = mLength;

         if(!readOnly) {
            mData = Memory::New<TChar>(mCapacity);
            Memory::Copy(str, inref mData, mLength);
         } else {
            mData = (TChar*)str;
         }
      }

		/** @brief Constructor. (TChar*, uword, bool). Create an encoded text instance using the given character array, length and read-only flag.
		 * @param str A string of encoded characters .
		 * @param length The number of characters to copy.
		 * @param readOnly Determines if the text will copy the string, or reference it.
		 */
      Text(const TChar* str, uword length, bool readOnly = false)  : mData(null), mLength(length), mCapacity(length), mIsReadonly(readOnly) {
         if(!readOnly) {
            mData = Memory::New<TChar>(mCapacity);
            Memory::Copy(str, inref mData, mLength);
         } else {
            mData = (TChar*)str;
         }
      }

		/** @brief Constructor. Copy (const TSelf&, bool). Create an encoded text instance using the given copy and read-only flag.
		 * @param copy The text instance being copied.
		 * @param readOnly Determines if the text will copy the text, or reference it.
		 */
      Text(const Text<TEncoding>& copy, bool readOnly) : mData(copy.mData), mLength(copy.mLength), mCapacity(copy.mCapacity), mIsReadonly(readOnly) {
         if(!mIsReadonly) {
            mData = Memory::New<TChar>(mCapacity);
            Memory::Copy(copy.mData, inref mData, mLength);
         }
      }

		/** @brief Constructor. Copy. (const Text<T>&). Create an encoded text instance using the given copy.
		 * @param copy The text instance being copied.
		 * @note Read-only text will not be copied, but reference.
		 */
      template<typename T> Text(const Text<T>& copy) : mData(Memory::New<TChar>(copy.mCapacity)), mLength(copy.mLength), mCapacity(copy.mCapacity), mIsReadonly(false)  {
			TEncoding::template Decode<T>(inref mData, copy.mData, mLength);
		}

		/** @brief Constructor. Copy. (const TSelf&). Specialization. */
      Text(const Text<TEncoding>& copy) : mData(copy.mData), mLength(copy.mLength), mCapacity(copy.mCapacity), mIsReadonly(copy.mIsReadonly)  {
      	if(!mIsReadonly) {
				mData =	Memory::New<TChar>(copy.mCapacity);
				Memory::Copy(copy.mData, inref mData, mLength);
      	}
		}

		/** @brief Constructor. Move. (TSelf&&). */
		Text(Text<TEncoding>&& move) : mData(move.mData), mLength(move.mLength), mCapacity(move.mCapacity), mIsReadonly(move.mIsReadonly) {
         if(!move.mIsReadonly) {
				move.mData = null;
				move.mLength = 0;
				move.mCapacity = 0;
			}
      }

		/** @brief De-constructor. */
      ~Text() {
         pClear(true);
      }

		/** @brief operator=(const TSelf&). */
		Text<TEncoding>& operator=(const Text<TEncoding>& rhs) {
			if(this == &rhs) {
				return *this;
			}

			pClear(true);

			if(!rhs.mIsReadonly) {
				mData = Memory::New<TChar>(mCapacity);
            Memory::Copy(rhs.mData, inref mData, rhs.mLength);
			} else {
				mData = rhs.mData;
			}

         mIsReadonly = rhs.mIsReadonly;
         mLength = rhs.mLength;

         return *this;
		}

		/** @brief operator=(const TSelf&&). */
		Text<TEncoding>& operator=(Text<TEncoding>&& rhs) {
			if(this == &rhs) {
				return *this;
			}

			pClear(true);

			mData = rhs.mData;
         mIsReadonly = rhs.mIsReadonly;
         mLength = rhs.mLength;

			rhs.mData = null;
			rhs.mLength = 0;
			rhs.mIsReadonly = true;

         return *this;
		}

		/** @brief operator==(const TSelf&). */
      template<typename T> bool operator==(const Text<T>& rhs) const {
         if(this == &rhs) {
            return true;
         }

         if(mLength == rhs.mLength) {
            return TEncoding::template Compare<T>(mData, rhs.mData, mLength);
         }

         return false;
      }

		/** @brief operator!=(const TSelf&). */
      template<typename T> bool operator!=(const Text<T>& rhs) const {
			return !this->operator==(rhs);
      }

		/** @brief operator+(const TSelf&). */
		TSelf operator+(const TSelf& rhs) const {
			TSelf result = TSelf(*this, false);
			result.Append(rhs);
			return TSelf((TSelf&&)result);
		}

		/** @brief operator+=(const TSelf&). */
		TSelf& operator+=(const TSelf& rhs) {
			this->Append(rhs);
			return *this;
		}

		/** @brief operator+(const TSelf&). */
		TSelf operator+(TChar rhs) const {
			TSelf result = TSelf(*this, false);
			result.Append(rhs);
			return TSelf((TSelf&&)result);
		}

		/** @brief operator+=(const TSelf&). */
		TSelf& operator+=(TChar rhs) {
			this->Append(rhs);
			return *this;
		}

		/** @brief operator[](uword). */
      TChar& operator[](uword index) {
      	if(IsNullOrEmpty()) {
				THROW(InvalidOperationException("Unable to access empty or null text!"));
      	} else if(index >= mLength) {
				THROW(OutOfRangeException("The parameter 'index' must less than the length of the text!"));
      	}

         return *(mData + index);
      }

      /** @brief Gets the address of the first character in the text. */
      TChar* Data() const {
      	return mData;
		}

      /** @brief Gets the number of characters in the text. */
      uword Length() const {
			return mLength;
		}

		/** @brief Gets a unique numerical hash-code of the text.
		 * @remarks This algorithm has should have no collisions for small text strings, but should not be relied on
		 * for security measures.
		 */
		uword ToHashcode() const {
			// TODO: Determine the collision resolution of Text::ToHashcode()
			if(IsNullOrEmpty()) {
				return 0;
			}

			uword hash = 0;
			uword i = 0;
			TChar* begin = mData;
			do{
				uword tmp = (hash + (i++ + 1)) * (*begin);
				tmp -= hash;
				hash = tmp;
			} while(++begin != End());

			return hash;
		}

		/** @brief Gets a pointer referencing the a character in the text found at the given index.
		 * @param at The index of the character within the text to reference.
		 */
		TChar* Begin(uword at = 0) const {
			if(at >= mLength) {
				THROW(InvalidParameterException("The given parameter 'at' must be greater than the length of the text."));
			}

			return mData + at;
		}

		/** @brief Gets a pointer referencing the last character in the text. */
		TChar* End() const {
			return mData + mLength - 1;
		}

		/** @brief Gets the pointer location to the first occurrence of the given character.
		 * @param c The character, if found, to stop seeking at.
		 * @return A reference to the first occurrence of the character within the text.
		 */
		TChar* SeekTo(TChar c) const {
			uword start = 0;
			return SeekTo(c, start);
		}

		/** @brief Gets the pointer location to the first occurrence of the given character.
		 * @param c The character, if found, to stop seeking at.
		 * @param start The character index within the text to begin seeking at.
		 * @return A reference to the first occurrence of the character within the text.
		 */
		TChar* SeekTo(TChar c, uword& start) const {
			if(IsNullOrEmpty()) {
				THROW(InvalidOperationException("Cannot seek from empty or null text!"));
			} else if(start >= mLength) {
				THROW(OutOfRangeException("The given parameter 'start' cannot be larger than the length of the text!"));
			}

			TChar* begin = mData + start;
			do {
				if(*begin == c) {
					return begin;
				}

				++start;
			} while(++begin != End());
			return null;
		}

		/** @brief Gets the pointer location to the first occurrence of the given string. */
		TChar* SeekTo(const Text<TEncoding>& str) const {
			TChar* ptr = mData;
			TChar* rhs = str.mData;
			bool hit = false;

			while(ptr++ && !hit) {
				if(*ptr == *rhs) {
					TChar* p = ptr;
					hit = false;

					while(*rhs++ && *p++) {
						if(*p != *rhs) {
							hit = false;
							break;
						}
						hit = true;
					}

					if(hit) {
						return p;
					} else {
						rhs = str.mData;
					}
				}
			}

			return null;
		}

		/** @brief Reads text from the string until the given character is discovered.
		 * @param c The character, if found, to stop at.
		 * @return The text that was read.
		 */
		TSelf ReadTo(TChar c) const {
			uword start = 0;
			return ReadTo(c, start);
		}

		/** @brief Reads text from the string until the given character is discovered.
		 * @param start The character index within the text to begin reading from, and a place to
		 * store the stopping location when the function terminates.
		 * @param c The character, if found, to stop at.
		 * @return The text that was read.
		 */
		TSelf ReadTo(TChar c, uword& start) const {
			if(IsNullOrEmpty()) {
				THROW(NullReferenceException("Unable to read from text that is null or empty!"));
			} else if(start >= mLength) {
				THROW(InvalidParameterException("The parameter 'start' cannot be greater than the length of the text!"));
			}

			TSelf result = TSelf(mLength);
			TChar* begin = mData + start;

			do {
				if(*begin == c) {
					break;
				}

				result += *begin;
			} while(++begin != End());

			return TSelf((TSelf&&)result);
		}

		/** @brief Counts the number of occurrences matching the given character.
		 * @param c The character being counted.
		 */
		uword Count(TChar c) const {
			if(IsNullOrEmpty()) {
				return 0;
			}

			uword result = 0;
			TChar* begin = mData;
			do {
				if(*begin == c) {
					++result;
				}
			} while(++begin != End());
			return result;
		}

		/** @brief Appends another string of text to the end of the text.
		 * @param rhs The text being appended.
		 * @remarks This will work when the text is null.
		 */
		void Append(const TSelf& rhs) {
			if(rhs.IsNullOrEmpty()) {
				return;
			}

			pReallocate(mLength + rhs.mLength - 1, false);
			TChar* begin = mData + mLength - 1;
			TChar* rhsp = rhs.mData;
			mLength += rhs.mLength - 1;

			do {
				*begin = *rhsp;
				++begin;
			} while(++rhsp != rhs.End());
			pTerminate();
		}

		/** @brief Appends a single character to the end of the text.
		 * @param c The character being appended.
		 * @remarks This will work when the text is null.
		 */
		void Append(TChar c) {
			pReallocate(mLength + 1, false);
			mData[mLength - 1] = c;
			mLength++;
			pTerminate();
		}

		/** @brief Splits the text into tokens using the given character as a delimiter.
		 * @param delim The character occurrence representing the locations where to split the string.
		 * @param removeEmpty Determines if the empty tokens should be discarded.
		 */
		Array<TSelf> Split(TChar at, bool removeEmpty = true) const {
			auto result = Array<TSelf>(2);
			TSelf token = TSelf(1);

			TChar* begin = this->Begin();
			do {
				if(*begin == at) {
					if(!removeEmpty || !token.IsNullOrEmpty()) {
						result.Add(TSelf((TSelf&&)token));
						continue;
					}
				}

				token.Append(*begin);
			} while(++begin != this->End());

			if(!removeEmpty || !token.IsNullOrEmpty()) {
				result.Add(TSelf((TSelf&&)token));
			}

			return Array<TSelf>((Array<TSelf>&&)result);
		}

		/** @brief Determines if the text is null or empty. */
		bool IsNullOrEmpty() const {
			return isnull(mData) || (mLength == 1 && *mData == TEncoding::EndOfString());
		}

		/** @brief A constant value representing empty text. */
		static const Text<TEncoding>& Empty();

   protected:
   	/** @brief Clears the text by initializing the internal data to null. */
      void pClear(bool ignoreReadOnlyError) {
         if(!ignoreReadOnlyError) {
            pThrowIfReadOnly();
         }

			if(!mIsReadonly && !isnull(mData)) {
            Memory::Delete<TChar>(mData);
            mLength = 0;
            mCapacity = 0;
            mData = null;
         }
      }

		/** @brief Ensures that the text is properly initialized.
		 * @return True if the text needed revalidation.
		 * @remarks Invalid text occurs when an instance is de-constructed or moved.
		 */
		bool pValidate() {
			if(IsNullOrEmpty()) {
				mData = Memory::New<TChar>(2);
				mLength = 1;
				mCapacity = 2;
				pTerminate();
				mIsReadonly = false;
				return true;
			}

			return false;
		}

		/** @brief Throws an exception if the text is read-only. */
      void pThrowIfReadOnly() const {
         if(mIsReadonly) {
            throw InvalidOperationException("Cannot modify the characters of read-only text!");
         }
      }

		/** @brief Reallocates the text to a new capacity. */
      void pReallocate(uword newCapacity, bool ignoreReadonly = true) {
			if(!ignoreReadonly) {
				pThrowIfReadOnly();
			}

			if(!mIsReadonly) {
				if(pValidate()) {
					newCapacity++;
				}

				if(newCapacity == mCapacity) {
					return;
				} else if(newCapacity > mCapacity) {
					mCapacity = newCapacity;

					TChar* ptr = mData;
					mData = memory::New<TChar>(mCapacity);

					if(!isnull(ptr)) {
						memory::Copy(ptr, mData, mLength);
						memory::Delete(ptr);
					}
				}
			}
      }

		/** @brief Appends a null-termination character to the end of the text. */
		void pTerminate() {
			TEncoding::EndOfString(mData + (mLength-1));
		}

		/** @brief Shrinks the text to its length. */
      void pShrink(bool ignoreReadonly = true) {
			if(!ignoreReadonly) {
				pThrowIfReadOnly();
			}

			if(!mIsReadonly && mLength < mCapacity) {
				mCapacity = mLength;
				TChar* ptr = mData;
				mData = Memory::New<TChar>(mCapacity);
				memory::Copy(ptr, mData, mLength);

				if(!isnull(ptr)) {
					Memory::Delete(ptr);
				}
			}
      }

      TChar* mData;
      uword mLength;
      uword mCapacity;
      bool mIsReadonly;
   };

	/** @brief Text<AsciiEncoding> */
   typedef Text<AsciiEncoding> ascii;

	/** @brief The encoded text type used by the framework. Determined at compile-time. */
#  if _tkn_UseUnicodeEncoding == _tknval_False
      typedef ascii text;
#  else
      typedef ascii text;
#  endif

	/** @brief A macro used to create a constant text instance at compile-time. */
#  if _tkn_UseUnicodeEncoding == _tknval_False
#     define const_text(str) text(str, true)
#  else
#     define const_text(str) text(str, true)
#  endif
}
#endif // __NGEN_TEXT_HPP
