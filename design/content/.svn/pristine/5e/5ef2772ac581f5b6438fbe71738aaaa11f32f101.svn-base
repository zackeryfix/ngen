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
#ifndef __NGEN_LIST_HPP
#define __NGEN_LIST_HPP

#include "Ngen.Memory.hpp"
#include "Ngen.Algorithm.hpp"
#include "Ngen.Trait.hpp"
#include "Ngen.Exception.hpp"
#include "Ngen.Array.hpp"

namespace Ngen {
   /** @brief A container object that implements a list of linked nodes. */
   template<typename T>
   class List { // : public virtual IContainer<uword, T> {
   public:
      /** @brief An instance that represents a single item in a list. */
      class Node {
      public:
         Node(Node* previous, T data) : mPrevious(previous), mNext(null), mData(data) {
            if(!isnull(previous)) {
               previous->mNext = this;
            }
         }

         /** @brief Gets the next node in the linked list. */
         Node* Next() const { return mNext; }

         /** @brief Gets the previous node in the linked list. */
         Node* Previous() const { return mPrevious; }

         /** @brief Gets a reference to the data-structure represented by this node. */
         T& Data() { return mData; }

         /** @brief Gets the last node linked to this node.
          * @param count [in] The number of nodes counted, including the starting (this) node.
          * @note The count will never be less than one.
          */
         Node* Last(uword& count) const {
            count = 1;
            Node* cur = (Node*)this;

            while(cur->mNext != null) {
               count++;
               cur = cur->mNext;
            }

            return cur;
         }

         /** @brief Gets the first node linked to this node.
          * @param count [in] The number of nodes counted, including the starting (this) node.
          * @note The count will never be less than one.
          */
         Node* First(uword& count) const {
            count = 1;
            Node* cur = this;

            while(cur->mPrevious != null) {
               count++;
               cur = cur->mPrevious;
            }

            return cur;
         }

			Node& operator++() {
				this = mNext;
				return *this;
			}

			Node& operator--() {
				this = mPrevious;
				return *this;
			}

      private:
         Node* mPrevious;
         Node* mNext;
         T mData;

         friend class List<T>;
      };

      /** @brief Constructor. Default. */
      List() : mHead(null), mTail(null), mLength(0), mIsReadonly(false) {}

      /** @brief Constructor. Copy. */
      List(const List<T>& copy) : mHead(null), mTail(null), mLength(0), mIsReadonly(false) {
         this->operator=(copy);
      }

      /** @brief Constructor. Move. */
      List(List<T>&& move) : mHead(move.mHead),mTail(move.mTail), mLength(move.mLength), mIsReadonly(move.mIsReadonly) {
         move.mHead = null;
         move.mTail = null;
         move.mLength = 0;
      }

      /** @brief Constructor. Creates a read-only list using the given reference to a node.
       * @param head A reference to a node that will be will represent thee head of the list.
       */
      List(const Node* head, bool readOnly = true) : mHead(null), mTail(null), mLength(1), mIsReadonly(readOnly) {
         Set(head, readOnly);
      }

      /** @brief Destructor. */
      ~List() {
         if(!mIsReadonly) {
            pClear(true);
         }
      }

      /** @brief Operator. Equal. const List<T>&. */
      bool operator==(const List<T>& rhs) {
         bool success = false;
         if(mLength > 0 && rhs.mLength > 0 && mLength == rhs.mLength) {
            Node* left = mHead;
            Node* right = rhs.mHead;

            do {
               if(left->mData != right->mData) {
                  success = false;
                  break;
               }
            } while(left != null && right != null);

            success = true;
         }

         return success;
      }

      /** @brief Operator. Not Equal. const List<T>&. */
      bool operator!=(const List<T>& rhs) {
         return !this->operator==(rhs);
      }

      /** @brief Operator. Assign. const List<T>&. */
      List<T>& operator=(const List<T>& rhs) {
			Set(rhs.mHead, rhs.mIsReadonly);
			return *this;
      }

      /** @brief Operator. Indexer. */
      T& operator[](uword index) {
         return At(index);
      }

      /** @brief Gets a value that determines if the list was constructed as read-only. */
      bool IsReadonly() const {
         return mIsReadonly;
      }

      /** @brief Gets the total number of items in the list. */
      uword Length() const {
         return mLength;
      }

      /** @brief Gets a node in the list found at the given index. */
      Node* Begin(uword index = 0) const {
         return pGet(index);
      }

      /** @brief Gets the last node in the list. */
      Node* End() {
         return mTail;
      }

      /** @brief Gets a data item from the node found at the given index. */
      T& At(uword index) {
         return pGet(index, true)->mData;
      }

      /** @brief Adds a new item to the end of the list. */
      void Add(T item) {
         pThrowIfReadonly();

         if(isnull(mHead)) {
            mHead = new Node(null, item);
            mTail = mHead;
         } else {
            mTail->mNext = new Node(mTail, item);
            mTail = mTail->mNext;
         }

         mLength++;
      }

      /** @brief Inserts a new item into the list at the given index. */
      void Insert(T item, uword index = 0) {
         pThrowIfReadonly();

         Node* at = pGet(index, true);
         Node* node = new Node(at, item);

         node->mNext = at->mNext;
         at->mPrevious->mNext = node;
         node->mPrevious = at->mPrevious;
         at->mPrevious = node;
      }

      /** @brief Removes an item from the list at the given index.
       * @param index The index of the node being removed.
       */
      void RemoveAt(uword index) {
         pRemove(pGet(index));
      }

      /** @brief Removes an item from the list that matches a given value.
       * @param value The value being compared to determine which node being removed.
       */
      void Remove(const T& value) {
         pThrowIfReadonly();
         if(mLength == 0) {
            throw InvalidOperationException("Cannot modify the contents of a NULL container!");
         }

         pRemove(pGetByValue(value));
      }

      /** @brief Removes all items from the list that match a given value.
       * @param value The value being compared to determine which nodes will be removed.
       */
      void RemoveAny(const T& value) {
         Node* at = pGetByValue(value);

         while(!isnull(at)) {
            pRemove(at);
            at = pGetByValue(value);
         }
      }

      /** @brief Gets a read-only copy of the list.
       * @note This is useful when passing the list to functions by value. Similar to using move semantics.
       */
      List<T> AsReadonly() const {
         List<T> result = List<T>();

         result.mHead = mHead;
         result.mTail = mTail;
         result.mLength = mLength;
         result.mIsReadonly = true;

         return result;
      }

      /** @brief Clears all the items from the list. */
      void Clear() {
         pClear(false);
      }

      /** @brief Reverses the order of the nodes in the list. */
      void Reverse() {
         pThrowIfReadonly();

         if(mLength > 1) {
            Node* cur = mHead;
            Node* tmp = null;

            while(!isnull(cur->mNext)) {
               tmp = cur->mNext;
               cur->mNext = cur->mPrevious;
               cur->mPrevious = tmp;
               cur = tmp;
            }

            tmp = mHead;
            mHead = mTail;
            mTail = tmp;
         }
      }

      /** @brief Re-initializes the list using the given node.
       * @note This can be used on a read-only list.
       */
      void Set(const Node* head, bool readOnly) {
         if(mHead != head) {
            pClear(true);

            uword len = 0;
            Node* last = head->Last(inref len);

            if(readOnly) {
               mHead = (Node*)head;
               mLength = len;
               if(isnull(mHead->mNext)) {
                  mTail = mHead;
               } else {
                  mTail = last;
               }
            } else {
               mHead = new Node(null, head->mData);

               if(len == 1) {
                  mLength = 1;
                  mTail = mHead;
               } else {
                  Node* next = head->mNext; // copy iterator
                  Node* cur = mHead;              // this iterator
                  Node* prev = null;

                  while(!isnull(next)) {
                     cur->mNext = new Node(cur, next->mData);
                     cur->mPrevious = prev;

                     prev = cur;
                     cur = cur->mNext;
                     next = next->mNext;
                     mLength++;
                  }

                  mTail = prev;
               }
            }
         }

         mIsReadonly = readOnly;
      }

      /** @brief Gets an array of each item in the list that falls between the given range. */
      Array<T> ToArray(uword start = 0, uword length = 0) const {
         if(mLength == 0) {
            return Array<T>::Empty;
         } else if(start > mLength) {
            throw OutOfRangeException("The given argument 'start' cannot be larger than the length of the list.");
         } else if(length > mLength) {
            throw InvalidParameterException("The given argument 'length' cannot be greater-than the length of the list.");
         } else if(length == 0) {
            length = mLength;
         }

         if(start > length) {
            throw InvalidParameterException("The given argument 'start' cannot be greater-than the given 'length' argument.");
         }

         Array<T> result = Array<T>(length);
         Node* next = pGet(start);

         while(!isnull(next)) {
            result.Add(next->mData);
            next = next->mNext;
         }

         return result;
      }

      bool Contains(const T& item) {
			return !isnull(pGetByValue(item));
      }

      bool Contains(const T& item, T& ref) {
			ref = pGetByValue(item)->mData;
			return !isnull(ref);
      }

   protected:
      /** @brief A commonly used algorithm for retrieving a node by index. */
      inline Node* pGet(uword index, bool throwIfEmpty = false) const {
         if(mLength == 0) {
				if(throwIfEmpty) {
					throw InvalidOperationException("The list is empty and contains no items.");
				}

            return null;
         } else if(index >= mLength) {
            throw OutOfRangeException("The given parameter 'index' falls beyond the range of the list.");
         }

         Node* result = null;
         if(index == 0) {
            result = mHead;
         } else if(index == mLength - 1) {
            result = mTail;
         } else if((mLength / 2) > index) {
            uword i = mLength - 1;
            result = mTail;
            while(i != index) {
               result = result->Previous();
               --i;
            }
         } else {
            uword i = 0;
            result = mHead;
            while(i != index) {
               result = result->Next();
               ++i;
            }
         }

         return result;
      }
      /** @brief A commonly used algorithm for retrieving an item that matches the given value. */
      inline Node* pGetByValue(const T& value) const {
         Node* next = mHead;

         while(!isnull(next)) {
            if(next->mData == value) {
               return next;
            }

            next = next->mNext;
         }

         return null;
      }
      /** @brief A commonly used algorithm for retrieving an item that matches the given value. */
      inline Node* pGetByValue(const T& value, uword& index) const {
         Node* next = mHead;
         index = 0;

         while(next->mNext != null) {
            if(next->mData == value) {
               return next;
            }
            index++;
            next = next->mNext;
         }

         return null;
      }
      /** @brief An algorithm commonly used to remove a node from the list. */
      inline void pRemove(Node* node) {
         if(node == mHead) {
            if(mLength == 1) {
               pClear(true);
            } else {
               mHead = mHead->Next();
               mHead->mPrevious = null;
               mLength--;

               delete node;
            }
         } else if(!isnull(node)) {
            node->mPrevious->mNext = node->mNext;
            node->mNext->mPrevious = node->mPrevious;
            mLength--;

            delete node;
         }
      }

      /** @brief An algorithm commonly used to clear the contents of the list. */
      inline void pClear(bool ignoreReadOnlyError) {
         if(!ignoreReadOnlyError) {
            pThrowIfReadonly();
         }

         if(!mIsReadonly) {
            while(!isnull(mHead)) {
               Node* next = mHead->mNext;
               delete mHead;

               mHead = next;
               mLength--;
            }

            mHead = null;
            mTail = mHead;
            mLength = 0;
         }
      }

      /** @brief Throws an exception if the list is read-only. */
      inline void pThrowIfReadonly() {
         if(mIsReadonly) {
            throw new InvalidOperationException("Cannot manipulate a read-only list!");
         }
      }

      Node* mHead;
      Node* mTail;
      uword mLength;
      bool mIsReadonly;
   };
}
#endif // NGEN_LIST_CPP_INCLUDED
