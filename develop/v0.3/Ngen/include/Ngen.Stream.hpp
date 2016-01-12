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
#ifndef __NGEN_STREAM_HPP
#define __NGEN_STREAM_HPP

#include "Ngen.Exception.hpp"

namespace Ngen {

	class ngen_api Stream {
	public:
		virtual ~Stream() {};

		/** @brief Gets the length (in bytes) of the data stream.
		 */
		virtual void Close() pure;

		/** @brief Gets the length (in bytes) of the data stream.
		 */
		virtual uword Length() const pure;

		/** @brief Sets the length (in bytes) of the stream.
		 * @remarks The buffer will be truncated if the new length is smaller than the current length.
		 */
		virtual void Resize(uword length) const;

		/** @brief Gets the current cursor location (in offset bytes) of the data stream.
		 */
		virtual uword Offset() const pure;

		/** @brief Offsets a new cursor location (in bytes) forwards from its current location.
		 * @param offset The number of bytes to move the cursor forwards.
		 */
		virtual void Forward(uword offset) const pure;

		/** @brief Offsets a new cursor location (in bytes) backwards from its current location.
		 * @param offset The number of bytes to move the cursor backwards.
		 */
		virtual void Backward(uword offset) const pure;

		/** @brief Reads a single byte from the data stream.
		 * @param buffer The place where the bytes being read will be written to.
		 * @return Will return false if the end of the stream was reached before the read operation.
		 */
		virtual bool ReadByte(uint8*& buffer) const pure;

		/** @brief Reads a string of bytes from the data stream.
		 * @param buffer The place where the bytes being read will be written to.
		 * @param start The offset (in bytes) within the stream to begin reading.
		 * @param count The number bytes to read.
		 * @remarks The new cursor offset of the stream will replace the start parameter.
		 * @return Will return false if the end of the stream was reached before the read operation.
		 */
		virtual bool Read(uint8*& buffer, uword start, uword count) const pure;

		/** @brief Writes a single byte to the data stream.
		 * @param value The single byte being written to the stream.
		 * @return Will return false if the end of the stream was reached before the write.
		 */
		virtual bool WriteByte(uint8 value) const pure;

		/** @brief Writes a string of bytes to the data stream.
		 * @param buffer The place where the bytes being written will be read from.
		 * @param start The offset (in bytes) within the stream to begin writing.
		 * @param count The number bytes to write.
		 * @remarks The new cursor offset of the stream will replace the start parameter.
		 * @return Will return false if the end of the stream was reached before the write operation.
		 */
		virtual bool Write(uint8* buffer, uword start, uword count) const pure;

		/** @brief Determines if data can be read from the stream.
		 */
		virtual bool CanRead() const pure;

		/** @brief Determines if data can be written to the stream.
		 */
		virtual bool CanWrite() const pure;

		/** @brief Determines if IO operations on the stream can time-out.
		 */
		virtual bool CanTimeout() const pure;

		/** @brief Gets the number of milliseconds required for a read operation to time-out.
		 */
		virtual uword ReadTimeout() const pure;

		/** @brief Sets the number of milliseconds required for a read operation to time-out.
		 * @param ms The number of milliseconds to wait before a read operation will time-out.
		 */
		virtual void ReadTimeout(uword ms) const pure;

		/** @brief Gets the number of milliseconds required for a write operation to time-out.
		 */
		virtual uword WriteTimeout() const pure;

		/** @brief Sets the number of milliseconds required for a write operation to time-out.
		 * @param ms The number of milliseconds to wait before a write operation will time-out.
		 */
		virtual void WriteTimeout(uword ms) const pure;

		/** @brief Forces the write buffer to be written to the source of the stream.
		 */
		virtual void Flush() pure;
	protected:

	};
}

#endif // __NGEN_STREAM_HPP
