/*
    This file is part of the pm library package.
    Copyright (C) 2017-2020 Vladislav Podymov

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    To contact author, email to <vpod@cs.msu.ru>
 */
#ifndef PM_DEVEL_STREAM_BUFFER_HPP
#define PM_DEVEL_STREAM_BUFFER_HPP

#include <cstddef>

#include <list>
#include <string>

namespace pm::devel::stream {

class Buffer {
public:
  // = types =
  using Chunk = std::string;
  using ChunkSeq = std::list<Chunk>;
  class Iterator {
  public:
    // = methods =
    // defaults
    Iterator() = default;
    // advance
    Iterator & operator ++();
    Iterator operator ++(int);
    Iterator & operator +=(size_t size);
    Iterator operator +(size_t size) const;
    // compare
    bool operator ==(const Iterator & it) const;
    bool operator !=(const Iterator & it) const;
    // extract contents
    char operator *() const;
    char operator [](size_t size);
    std::string peek(size_t size) const;
    std::string peek(const Iterator & bound) const;
    // extract contents & advance
    char get();
    std::string get(size_t size);
    std::string get(const Iterator & bound);
    // other
    size_t operator -(const Iterator & it) const;
    size_t trim(size_t size, const Iterator & bound) const;
  private:
    // = methods =
    // constructors
    Iterator(ChunkSeq::const_iterator it, size_t offset, size_t chunk_size);
    // advance
    void advance_();
    void advance_(size_t size);
    void adjust_();
    // = fields =
    ChunkSeq::const_iterator chunk_it_;
    size_t offset_;
    size_t chunk_size_;
    // = friends =
    friend class Buffer;
  };
  // = methods =
  // defaults
  // Buffer() = delete;
  Buffer(const Buffer &) = delete;
  Buffer(Buffer &&) = delete;
  Buffer & operator =(const Buffer &) = delete;
  Buffer & operator =(Buffer &&) = delete;
  // constructors
  // TODO docs: chunk_size should fit in ptrdiff_t and be at least 1
  Buffer(size_t chunk_size);
  // insert data
  void add(char c);
  void add(std::string s);
  // generate iterators
  Iterator begin();
  Iterator end();
private:
  // = methods =
  void adjust_last_chunk_();
  // = fields =
  const size_t chunk_size_;
  ChunkSeq chunks_;
};

Buffer::Iterator operator +(size_t i, const Buffer::Iterator & it);

} // namespace pm::devel::stream

#endif
