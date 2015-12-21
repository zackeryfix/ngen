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
#ifndef __NGEN_ARRAY_HPP
#define __NGEN_ARRAY_HPP

#include "Ngen.Memory.hpp"
#include "Ngen.Container.hpp"

namespace Ngen {
   /** @brief A contiguous data structure for holding items contiguously in memory. */
   template<typename T> class Array { // : public virtual IContainer<uword, T> {
   public:
   	/** @brief A type-definition of the type without template decorations. */
   	typedef Array<T> TSelf;

      /** @brief Constructor. Default. */
      Array() : mData(null), mLength(0), mCapacity(0), mIsReadonly(false) {}

      /** @brief Constructor. Initialize.
       * @param capacity The number of structures to pre-allocate for the array.
       */
      Array(uword capacity) : mData(Memory::New<T>(capacity)), mLength(0), mCapacity(capacity), mIsReadonly(false) {}

      /** @brief Constructor. (T*, uword, bool)
       * @param copy The pointer where the data structures will be referenced to create the array.
       * @param length The number of structures being copied.
       * @param readOnly Determines if the array will copy the data structures or only reference them.
       */
      Array(T* copy, uword length, bool readOnly = true) : mData(null), mLength(0), mCapacity(0), mIsReadonly(readOnly) {
         Set(copy, length, readOnly);
      }

      /** @brief Constructor. Copy. (const TSelf&)
       * @param copy The array to copy elements from.
       */
      Array(const TSelf& copy) : mData(null), mLength(0), mCapacity(0), mIsReadonly(false)  {
         Set(copy.mData, copy.mLength, copy.mCapacity, copy.mIsReadonly);
      }

	   /** @brief Constructor. Copy. (const TSelf&, bool)
       * @param copy The array to copy elements from.
       * @param readOnly Determines if the array will copy the data structures or only reference them.
       */
      Array(const TSelf& copy, bool readOnly) : mData(null), mLength(0), mCapacity(0), mIsReadonly(readOnly)  {
         Set(copy.mData, copy.mLength, copy.mCapacity, readOnly);
      }

	   /** @brief Constructor. Move. (TSelf&&) */
      Array(TSelf&& move) : mData(move.mData), mLength(move.mLength), mCapacity(move.mCapacity), mIsReadonly(move.mIsReadonly) {
			if(!move.mIsReadonly) {
				move.mData = null;
				move.mLength = 0;
				move.mCapacity = 0;
			}
      }

		/** @brief De-constructor. */
		~Array() {
			pClear(true);
		}

      /** @brief operator[](uword).*/
      T& operator[](uword index) {
         if(IsNullOrEmpty()) {
            THROW(InvalidOperationException("Cannot index an array that is null or empty!"));
         } else if(index >= mLength) {
            THROW(OutOfRangeException("The parameter 'index' must be less than the length of the array!"));
         }

         return *(mData + index);
      }

      /** @brief operator+(const TSelf&)*/
      TSelf operator+(const TSelf& rhs) const {
			TSelf result = TSelf(*this, false);
			result.AddRange(rhs);
			return TSelf((TSelf&&)result);
      }

      /** @brief operator+=(const TSelf&)*/
      TSelf& operator+=(const TSelf& rhs) const {
			this->AddRange(rhs);
			return *this;
      }

		/** @brief operator+(const T&)*/
      TSelf operator+(const T& rhs) const {
			TSelf result = TSelf(*this, false);
			result.Add(rhs);
			return TSelf((TSelf&&)result);
      }

      /** @brief operator+=(const T&)*/
      TSelf& operator+=(const T& rhs) const {
			this->Add(rhs);
			return *this;
      }

      /** @brief Re-initializes the array using the given parameters.
       * @param data A pointer to the data structures being referenced.
		 * @param length The number of data structures to copy.
		 * @param readOnly Determines if the data structures will be copied or only referenced.
       */
      void Set(T* data, uword length, bool readOnly = false) {
         this->Set(data, length, 0, readOnly);
      }

      /** @brief Re-initializes the array using the given parameters.
       * @param data A pointer to the data structures being referenced.
		 * @param length The number of data structures to copy.
		 * @param capacity The total number of structures to reserve space for. Must be greater-than length or zero.
		 * @param readOnly Determines if the data structures will be copied or only referenced.
       */
      void Set(T* data, uword length, uword capacity, bool readOnly = false) {
         if(data == null) {
            throw InvalidParameterException("The parameter 'data' cannot be null!");
         } else if(length == 0) {
            throw InvalidParameterException("The parameter 'length' cannot be a zero!");
         } else if(capacity != 0 && length > capacity) {
            throw InvalidParameterException("The parameter 'length' must be less-than or equal-to the parameter 'capacity'!");
         }

         pClear(true);
         mIsReadonly = readOnly;
         mLength = length;
			mCapacity = capacity == 0 ? length : capacity;

         if(mIsReadonly) {
            mData = data;
         } else {
            pReallocate(mCapacity, true);

				T* begin = mData;
				do {
					*begin = *data++;
				} while(End() != begin++);
         }
      }

      /** @brief Clears all resources used by the array. */
      void Clear() {
         this->pClear(false);
      }

      /** @brief Gets the number of items in the array. */
      uword Length() const {
         return mLength;
      }

      /** @brief Gets the pre-allocated capacity of the array. */
      uword Capacity() const {
         return mCapacity;
      }

      /** @param Gets a value that determines if the array contains null data. */
      bool IsNullOrEmpty() const {
         return isnull(mData) ||  mLength == 0;
      }

      /** @brief Determines if the array is empty.
       * @param length [inref] A place to store the length of the array.
       */
      bool IsEmpty(uword& length) const {
         length = mLength;
         return IsNullOrEmpty();
      }

		/** @brief Get an iterator beginning at the given index. */
		T* Begin(uword at = 0) const {
			if(at >= mLength) {
				THROW(InvalidParameterException("The parameter 'at' must be less-than the length of the array!"));
			}

			return mData + at;
		}

		/** @brief Gets an iterator pointing at the last item in the array. */
		T* End() const {
			return mData + mLength-1;
		}

		/** @brief Adds item to the end of the array. */
      void Add(const T& item) {
			pReallocate(mLength + 1);
			memory::Place(mData + mLength, item);
			mLength++;
      }

		/** @brief Adds an array of items to the end of the array. */
		void AddRange(const TSelf& rhs) {
			if(rhs.IsNullOrEmpty()) {
				return;
			}

			pReallocate(mLength + rhs.mLength);

			T* begin = Begin(mLength);
			T* rhsp = rhs.mData;
			mLength += rhs.mLength;

			do {
				*begin = *rhsp++;
			} while(End() != begin++);
		}

		/** @brief Removes the first occurrence of an item from the array.
		 * @param item The data structure to use as a matching predicate for the item being removed.
		 */
		void Remove(const T& item) {
			if(IsNullOrEmpty()) {
				THROW(InvalidOperationException("Unable to remove items from a null or empty array!"));
			}

			T* begin = Begin();

			do {
				if(*begin == item) {
					break;
				}
			} while(End() != begin++);

			while(begin != End()) {
				*begin = *(begin+1);
				++begin;
			}

			mLength--;
		}

		/** @brief Counts the number of items in the array matching the given item.
		 * @param item The data structure to use as a matching predicate for the item being counted.
		 */
		uword Count(const T& item) const {
			uword result = 0;
			T* begin = mData;
			do {
				if(*begin == item) {
					++result;
				}
			} while(End() != begin++);
			return result;
		}
   protected:
      /** @brief Clears the items from the array, with an option to ignore read-only errors.
       * @param ignoreReadOnlyError Determines if the read-only flag should be checked before clearing the items.
       */
		void pClear(bool ignoreReadOnlyError) {
         if(!ignoreReadOnlyError) {
            pThrowIfReadonly();
         }

         if(!mIsReadonly) {
            if(!isnull(mData) && mLength != 0) {
               memory::Delete<T>(mData);
               mLength = 0;
               mCapacity = 0;
               mData = null;
            }
         }
      }

      /** @brief Throws an InvalidOperationException if the array is read-only. */
		void pThrowIfReadonly() const {
         if(mIsReadonly) {
            throw InvalidOperationException("Cannot manipulate a read-only array!");
         }
      }

      /** @brief Reallocates the array to a new capacity. */
		void pReallocate(uword newCapacity, bool ignoreReadonly = true) {
      	if(!ignoreReadonly) {
				pThrowIfReadonly();
      	}

			if(!mIsReadonly) {
				if(newCapacity == mCapacity) {
					return;
				} else if(newCapacity > mCapacity) {
					mCapacity = newCapacity;

					T* begin = mData;
					mData = Memory::New<T>(mCapacity);

					memory::Copy(begin, mData, mLength);
					if(!isnull(begin) && mLength > 0) {
						memory::Delete(begin);
					}
				}
			}
      }

      T* mData;
      uword mLength;
      uword mCapacity;
      bool mIsReadonly;
   };
}

#endif // __NGEN_ARRAY_HPP
