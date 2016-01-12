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
#ifndef __NGEN_STRING_HPP
#define __NGEN_STRING_HPP

#include "Ngen.Array.hpp"

//TODO: This class only works with null-terminated strings, need to add prefixed
// length support for native C/C++ char arrays

namespace Ngen {
   /** @brief A fixed-width string of characters. */
   template<typename T> class ngen_api String {
   public:
      // -------------------------------------
      // PUBLIC TYPEDEF
      // -------------------------------------
      typedef String<T> TSelf;
      typedef T TChar;

      // -------------------------------------
      // PUBLIC CTOR
      // -------------------------------------
      String() : mIsReadonly(true), mData(null), mLength(0), mCapacity(0) { pValidate(); }

      explicit String(uword capacity) : mIsReadonly(false), mData(capacity == 0 ? Memory::New<TChar>(1) : Memory::New<TChar>(capacity)), mLength(1), mCapacity(capacity == 0 ? 1 : capacity) {
         pTerminate();
      }

      String(const TChar* string, bool readOnly) : mIsReadonly(readOnly), mData((TChar*)string), mLength(0), mCapacity(0) {
         mLength = mCapacity = TSelf::GetLength(string);
         if(!readOnly) {
            mData = Memory::New<TChar>(mLength);
            Memory::Copy<TChar>(string, mData, mLength);
            pTerminate();
         }
      }

      String(const TChar* string) : mIsReadonly(false), mData(null), mLength(0), mCapacity(0) {
         mLength = mCapacity = TSelf::GetLength(string);
         mData = Memory::New<TChar>(mLength);
         Memory::Copy<TChar>(string, mData, mLength);
         pTerminate();
      }

      String(const TSelf& copy) : mIsReadonly(copy.mIsReadonly), mData(copy.mData), mLength(copy.mLength), mCapacity(copy.mCapacity) {
         if(!mIsReadonly) {
				mData =	Memory::New<TChar>(copy.mCapacity);
				Memory::Copy(copy.mData, mData, mLength);
				pTerminate();
      	}
      }

      String(const TSelf& copy, bool readOnly) : mIsReadonly(readOnly), mData(copy.mData), mLength(copy.mLength), mCapacity(copy.mCapacity) {
         if(!mIsReadonly) {
				mData =	Memory::New<TChar>(copy.mCapacity);
				Memory::Copy(copy.mData, mData, mLength);
				pTerminate();
      	}
      }

      /** @brief Constructor. Move. (TSelf&&). */
		String(TSelf&& move) : mIsReadonly(move.mIsReadonly), mData(move.mData), mLength(move.mLength), mCapacity(move.mCapacity) {
         if(!move.mIsReadonly) {
				move.mData = null;
				move.mLength = 0;
				move.mCapacity = 0;
			}
      }

		/** @brief De-constructor. */
      ~String() {
         pClear(true);
      }


      // -------------------------------------
      // PUBLIC MEMBER OPERATORS
      // -------------------------------------
      /** @brief operator=(const TSelf&). */
		TSelf& operator=(const TSelf& rhs) {
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
		TSelf& operator=(TSelf&& rhs) {
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
      bool operator==(const TSelf& rhs) const {
         if(this == &rhs) {
            return true;
         }

         if(mLength == rhs.mLength) {
            if(mLength == 0) {
               return true;
            }

            TChar* l = this->Begin();
            TChar* r = rhs.Begin();
            do {
               if(*l++ != *r++) {
                  return false;
               }
            } while(l != End());

            return true;
         }

         return false;
      }

		/** @brief operator!=(const TSelf&). */
      bool operator!=(const TSelf& rhs) const {
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


      // -------------------------------------
      // PUBLIC MEMBER FUNCTIONS
      // -------------------------------------

      /** @brief Get the total length of the string that represent actual characters that belong to the string. */
      uword Length() const {
         return mLength;
      }

      /** @brief Gets the capacity used to determine the total number of fixed width characters allocated for the string. */
      uword Capacity() const {
         return mCapacity;
      }

		/** @brief Determines if the string is null or empty. */
      bool IsNullOrEmpty() const {
         return isnull(mData) || (mLength == 1 && *mData == '\0');
      }

      /** @brief Gets a pointer referencing the a character in the string found at the given index.
		 * @param at The index of the character within the text to reference.
		 */
      TChar* Begin(uword at = 0) const {
         if(at >= mLength) {
				THROW(InvalidParameterException("The given parameter 'at' must be LESS-than the length of the string."));
			}

			return (TChar*)(mData + at);
      }

		/** @brief Gets a pointer referencing the last character in the string. */
      TChar* End() const {
			return (TChar*)(mData + (mLength - 1));
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
				THROW(InvalidOperationException(E"Cannot seek from an empty or null string!"));
			} else if(start >= mLength) {
				THROW(OutOfRangeException(E"The given parameter 'start' cannot be larger than the length of the string!"));
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
		TChar* SeekTo(const TSelf& str) const {
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
			uword from = 0;
			return ReadTo(c, inref from);
		}

		/** @brief Reads text from the string until the given character is discovered.
		 * @param from The character index within the text to begin reading from, and a place to
		 * store the stopping location when the function terminates.
		 * @param c The character, if found, to stop at.
		 * @return The text that was read.
		 */
		TSelf ReadTo(TChar c, uword& from) const {
			if(IsNullOrEmpty()) {
				THROW(NullReferenceException(E"Unable to read from a string that is null or empty!"));
			} else if(from >= mLength) {
				THROW(InvalidParameterException(E"The parameter 'from' cannot be greater than the length of the string!"));
			}

			TSelf result = TSelf(mLength);
			TChar* begin = mData + from;

			do {
				if(*begin == c) {
					break;
				}

				result += *begin;
				from++;
			} while(++begin != End());

			return TSelf((TSelf&&)result);
		}

		/** @brief Reads text from the string until the given text is discovered.
		 * @param from The character index within the text to begin reading from, and a place to
		 * store the stopping location when the function terminates.
		 * @param c The character, if found, to stop at.
		 * @return The text that was read.
		 */
		TSelf ReadTo(TSelf str, uword& from) const {
			if(str.IsNullOrEmpty() || IsNullOrEmpty()) {
				THROW(NullReferenceException(E"Unable to read from a string that is null or empty!"));
			} else if(from >= mLength) {
				THROW(InvalidParameterException(E"The parameter 'from' cannot be greater-than the length of the string being read!"));
			} else if(str.mLength > mLength) {
				THROW(InvalidParameterException(E"The parameter 'str' cannot have a length that is greater-than the length of the string being read!"));
			}

			TSelf result = TSelf(mLength);
			TChar* lhsp = (mData + from);
			TChar* rhsp = str.mData;
			bool hit = false;

			do {
				if(*lhsp == *rhsp) {
					TChar* tmp = lhsp;
					hit = true;

					do {
						if(*lhsp != *rhsp) {
							rhsp = str.mData;
							lhsp = tmp;
							hit = false;
						}
					} while(++rhsp != str.End() && ++lhsp != End());
				}

				if(hit) {
					break;
				}

				result += *lhsp;
			} while(++lhsp != End());

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

		/** @brief Gets the text that falls between the first set of matching characters. */
		bool Between(TChar lhs, TChar rhs, inref TSelf& ref) const {
			ref = TSelf();

			uword from = 0;
			TSelf tmp = this->ReadTo(lhs, inref from);
			if(this->operator!=(tmp)) {
				ref = this->ReadTo(rhs, inref from);
				if(!ref.IsNullOrEmpty() && this->operator!=(ref)) {
					return true;
				}
			}

			return false;
		}

		/** @brief Gets a substring within the string of characters. */
		TSelf SubString(uword start=0, uword stop=0) {
         stop = stop == 0 ? mLength : stop;
         TSelf result = TSelf((stop - start) + 1);

         TChar* ptr = Begin(start);
         TChar* end = Begin(stop);

         do {
            result[start++] = *ptr;
         } while(ptr++ != end);

         return TSelf((TSelf&&)result);
		}

		uint64 ToHashcode() const {
			if(IsNullOrEmpty()) {
				return 0;
			}

			uint64 hash = 0;
			uint64 i = 0;
			TChar* begin = mData;
			do{
				uint64 tmp = (hash + (i++ + 1)) * (*begin);
				tmp -= hash;
				hash = tmp;
			} while(++begin != End());

			return hash;
		}
      // -------------------------------------
      // STATIC FUNCTIONS
      // -------------------------------------
      /** @brief Gets the size (in bytes) of the primitive data type used to represent the fixed with characters. */
      static uword GetByteWidth() {
         return sizeof(T);
      }

      static uword GetLength(const TChar* at) {
         if(isnull(at)) {
            return 0;
		   }

			uword result = 0;
         do {
            result++;
         } while(*(at++));

			return result;
      }

      static TSelf Format(const TSelf& format, const Array<TSelf>& params) {
         // TODO:  This was written once, and left unoptimized; optimize it (change to native C string formatting logic)
         TSelf result;
         TChar* begin = format.Begin();
         TChar* end = format.End();
         TSelf buffer[format.Length()/2];
         uword i = 0;
         uword buffer_i = 0;
         bool param_first = false;
         //buffer[0].pReallocate(format.Length()/2);

         do {
            if(*begin == E'{') {
               if(i == 0) {
                  param_first=true;
               }
               buffer_i++;
               //buffer[buffer_i].pReallocate(format.Length()/2);
               while(*begin != E'}') {
                  if(begin == end) {
                     THROW(OutOfRangeException("The given string has an invalid formatting or mismatching '{}' pair for use with string::Format!"));
                  }

                  begin++;
                  i++;
               }
            }

            buffer[buffer_i] += *begin;
            begin++;
         } while(begin != end);

         uword format_i = 0;
         uword params_i = 0;
         if(param_first) {
            while(format_i < buffer_i && params_i < params.Length()) {
               result += params[params_i++];
               result += buffer[format_i++];
            }
         } else {
            while(format_i < buffer_i && params_i < params.Length()) {
               result += buffer[format_i++];
               result += params[params_i++];
            }
         }

         if(params_i < params.Length()) {
            result += params[params_i];
         }

         if(format_i < buffer_i) {
            result += buffer[format_i];
         }

         return TSelf((TSelf&&)result);
      }


      static const TSelf& Empty();
   protected:
      // -------------------------------------
      // PROTECTED MEMBER FUNCTIONS
      // -------------------------------------
      /** @brief CLears the memory allocated for the string. */
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

      /** @brief Will throw an InvalidOperationException if the string is null or empty. */
      void pThrowIfReadOnly() {
         if(mIsReadonly) {
            THROW(InvalidOperationException(E"Attempting to overwrite a READONLY string of fixed width characters."));
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
               mData = Memory::New<TChar>(mCapacity);

               if(!isnull(ptr)) {
                  Memory::Copy(ptr, mData, mLength);
                  Memory::Delete(ptr);
                  pTerminate();
               }

               pValidate();
            }
         }
      }

		/** @brief Appends a null-termination character to the end of the text. */
		void pTerminate() {
			*(mData + (mLength-1)) = '\0';
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

      // -------------------------------------
      // PROTECTED MEMBER FIELDS
      // -------------------------------------
      bool mIsReadonly;
      TChar* mData;
      uword mLength;
      uword mCapacity;
   };

   typedef String<char8> string8;
   typedef String<char16> string16;
   typedef String<char32> string32;

/** @brief The encoded text type used by the framework. Determined at compile-time. */
#  if _tkn_UseUnicodeEncoding == _tknval_False
      typedef string8 string;
#  else
      typedef string16 string;
#  endif

	/** @brief A macro used to create a constant text instance at compile-time. */
#  if _tkn_UseUnicodeEncoding == _tknval_False
#     define const_string(str) string(str, true)
#  else
#     define const_string(str) string(u##str, true)
#  endif

	typedef string::TChar tchar;
}

#endif // __NGEN_STRING_HPP
