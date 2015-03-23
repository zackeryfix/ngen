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
#ifndef __NGEN_ICONTAINER_HPP
#define __NGEN_ICONTAINER_HPP

namespace Ngen {
   /** @brief An interface that represents the API for a container of items. */
   template<typename TIndexer, typename T>
   class IContainer {
   public:
      // Type-definitions ------------------------------------------------------

      typedef IContainer<TIndexer, T> TSelf;

      // Construction/Deconstruction -------------------------------------------

      /** @brief De-constructor. */
      virtual ~IContainer() {}

      // Operators -------------------------------------------------------------

      /** @brief Operator []. Gets an item reference from the container using the given index. */
      virtual T& operator[](TIndexer index) = 0;

      // Functions -------------------------------------------------------------

      /** @brief Gets an item reference from the container found at the given index.
       * @param index The index or key that can be used to identify the item.
       */
      virtual T& At(TIndexer index) const = 0;

      /** @brief Gets the total number of items in the container. */
      virtual uword Length() const = 0;

      /** @brief Gets the pre-allocated capacity of the container.
       * @remarks If the container does not support a pre-allocated capacity, return this->Length().
       */
      virtual uword Capacity() const = 0;

      /** @brief Gets a value that indicates if the collection is read-only. */
      virtual bool IsReadOnly() const = 0;

      /** @brief Attempts to increase the capacity of the container by reserving space for the given number of items. */
      virtual void Reserve(uword size) = 0;

      /** @brief Adds an item to the end of the container.
       * @param item A constant reference to the item being added to the container.
       */
      virtual void Add(const T& item) = 0;

      /** @brief Removes an item from the collection that was found at the given index or key.
       * @param index The index or key where the item being removed can be located.
       */
      virtual void RemoveAt(TIndexer index) = 0;

      /** @brief Inserts an item into the container at the given index. */
      virtual void Insert(T item, uword index = 0) = 0;

      /** @brief Replaces an existing item in container at the given index. */
      virtual void Replace(TIndexer index, T item) = 0;

      /** @brief Clears all the items from the container. */
      virtual void Clear() = 0;
   };
}

#endif // __NGEN_ICONTAINER_HPP
