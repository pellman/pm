/*
    This file is part of the pm library package.
    Copyright (C) 2017-2019 Vladislav Podymov

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the1
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    To contact author, email to <vpod@cs.msu.ru>
 */
#include "pm/stream/stream.hpp"

//#include <cstddef>
//#include <iosfwd>
//#include <memory>
//#include <string>
#include <utility>

#include "pm/stream/utils/buffer.hpp"
#include "pm/stream/utils/buffer_reader.hpp"
#include "pm/stream/utils/istream_reader.hpp"
//#include "pm/stream/utils/position.hpp"
//#include "pm/stream/utils/reader.hpp"



namespace pm {
namespace stream {

Stream::Stream(std::istream & is)
  : buffer_(new utils::Buffer(128)), // 128 is some random number, not very big, not very small
    pos_(buffer_->begin()),
    reader_(new utils::IStreamReader(is)) {}

Stream::Stream(std::istream & is, size_t buffer_chunk_size)
  : buffer_(new utils::Buffer(buffer_chunk_size)),
    pos_(buffer_->begin()),
    reader_(new utils::IStreamReader(is)) {}

bool Stream::advance() {
  return reader_->advance(pos_, *buffer_);
}

bool Stream::advance(size_t size) {
  return reader_->advance(size, pos_, *buffer_);
}

size_t Stream::advance_at_most(size_t size) {
  return reader_->advance_at_most(size, pos_, *buffer_);
}

bool Stream::get(char & c) {
  return reader_->get(c, pos_, *buffer_);
}

bool Stream::get(std::string & s, size_t size) {
  return reader_->get(s, size, pos_, *buffer_);
}

void Stream::get(std::string & s, const Position & bound) {
  return reader_->get(s, bound, pos_, *buffer_);
}

void Stream::get_at_most(std::string & s, size_t size) {
  return reader_->get_at_most(s, size, pos_, *buffer_);
}

void Stream::reposition(Position pos) {
  pos_ = std::move(pos);
}

bool Stream::empty() const {
  return reader_->at_end(pos_, *buffer_);
}

bool Stream::peek(char & c) const {
  return reader_->peek(c, pos_, *buffer_);
}

bool Stream::peek(std::string & s, size_t size) const {
  return reader_->peek(s, size, pos_, *buffer_);
}

void Stream::peek(std::string & s, const Position & bound) const {
  return reader_->peek(s, bound, pos_, *buffer_);
}

void Stream::peek_at_most(std::string & s, size_t size) const {
  return reader_->peek_at_most(s, size, pos_, *buffer_);
}

Stream Stream::prefix(Position bound) const {
  return {buffer_,
          pos_,
          std::shared_ptr<utils::Reader>(new utils::BufferReader(std::move(bound)))
         };
}

Position Stream::pos() const {
  return pos_;
}

Stream::Stream(std::shared_ptr<utils::Buffer> buffer, Position pos, std::shared_ptr<utils::Reader> reader)
  : buffer_(std::move(buffer)),
    pos_(std::move(pos)),
    reader_(std::move(reader)) {}

} // namespace stream
} // namespace pm
