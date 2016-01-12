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
#ifndef __NGEN_MAP_HPP
#define __NGEN_MAP_HPP

#include "Ngen.KeyValuePair.hpp"
#include "Ngen.List.hpp"

/// Because I was lazy and needed the API functional:
/// TODO: Use an Array of Keys and an array of Values instead of a KeyValuePair.

namespace Ngen {
	/** @brief A generic list of key-value pairs. */
	template<typename TKey, typename TValue>
	class ngen_api Map {
	public:
		typedef KeyValuePair<TKey, TValue> TKvPair;
		typedef List<TKvPair> TDict;
		typedef typename TDict::Node Node;
		typedef Map<TKey, TValue> TSelf;

		Map() : mData() {}
		Map(const TSelf& copy) : mData(copy.mData) {}
		Map(TSelf&& move) : mData((TDict&&)move.mData) {}

		Node* Begin(uword at = 0) const {
			return mData.Begin(at);
		}

		Node* End() const {
			return mData.End();
		}

      const TValue& operator[](const TKey& key) const {
			typename TDict::Node* node = mData.Begin();

			while(!isnull(node)) {
				if(node->Data().Key == key) {
					return node->Data().Value;
				}

				node = node->Next();
			}

			return this->End()->Data().Value;
		}

      TValue& operator[](const TKey& key) {
			typename TDict::Node* node = mData.Begin();

			while(!isnull(node)) {
				if(node->Data().Key == key) {
					return node->Data().Value;
				}

				node = node->Next();
			}

			this->Add(key, TValue());
			return this->End()->Data().Value;
		}

		uword Capacity() const {
         return mData.Capacity();
		}

      uword Length() const {
			return mData.Length();
		}

		bool IsReadonly() const {
			return mData.IsReadonly();
		}

		void Add(const TKey& key, const TValue& value) {
			mData.Add(TKvPair(key, value));
		}

		void Remove(const TKey& key) {
			mData.RemoveAt(IndexOf(key));
		}

		void RemoveAt(uword index) {
			mData.RemoveAt(index);
		}

      Map<TKey, TValue*> ToPointerMap() const {
         auto result =  Map<TKey, TValue*>();
         for(uword i = 0; i < mData.Length(); ++i) {
            result.Add(mData[i].Key, (TValue*)&mData[i].Value); // const to non-const
         }

         return result;
      }

      Array<TValue> Values() const {
         auto result =  Array<TValue>(mData.Length());
         for(uword i = 0; i < mData.Length(); ++i) {
            result.Add(mData[i].Value);
         }

         return result;
      }

      Array<TKey> Keys() const {
         auto result =  Array<TValue>(mData.Length());
         for(uword i = 0; i < mData.Length(); ++i) {
            result.Add(mData[i].Key);
         }

         return result;
      }

		uword IndexOf(const TKey& key) {
			typename TDict::Node* node = mData.Begin();
			uword index = 0;
			bool hit = false;

			while(!isnull(node)) {
				if(node->Data().Key == key) {
					hit = true;
					break;
				}

				index++;
				node = node->Next();
			}

			if(!hit) {
				THROW(InvalidParameterException("The parameter 'key' was not a recognized as known pair."));
			}

			return index;
		}

		/** @brief Determines if the map contains a matching key. */
		bool ContainsKey(const TKey& key) const {
			typename TDict::Node* node = mData.Begin();

			while(!isnull(node)) {
				if(node->Data().Key == key) {
					return true;
				}
				node = node->Next();
			}

			return false;
		}

		bool TryGetValue(const TKey& key, inref TValue& value) {
			typename TDict::Node* node = mData.Begin();
			bool hit = false;

			while(!isnull(node)) {
				if(node->Data().Key == key) {
					hit = true;
					value = node->Data().Value;
				}

				node = node->Next();
			}

			return hit;
		}

		Array<TKvPair> ToArray() const {
			return mData.ToArray();
		}

		bool Contains(const TKvPair& item) {
			return mData.Contains(item);
		}

		bool Contains(const TKvPair& item, TKvPair& ref) {
			return mData.Contains(item, inref ref);
		}

		void Reverse() {
			mData.Reverse();
		}

		TSelf AsReadonly() const {
			TSelf result = TSelf();
			result.mData = mData.AsReadonly();
			return result;
		}
	protected:
		TDict mData;
};
}
#endif // __NGEN_MAP_HPP
