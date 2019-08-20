/*
    This file is part of the pm library package.
    Copyright (C) 2017-2019 Vladislav Podymov

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
#include "pm/regex/regex.hpp"

//#include <iosfwd>
#include <utility>
//#include "pm/stream/stream.hpp"

//#include "pm/regex/context.hpp"
//#include "pm/regex/data_context.hpp"
#include "pm/regex/expressions/terminal/trivial.hpp"
//#include "pm/regex/utils/parser.hpp"

namespace pm {
namespace regex {

Regex::Regex()
  : Regex(re_false()) {}

Regex::Regex(utils::Parser * ptr)
  : ptr_(ptr) {}

bool Regex::match(std::istream & is) const {
  stream::Stream s(is);
  return match(s);
}

bool Regex::match(std::istream & is, Context & context) const {
  stream::Stream s(is);
  return match(s, context);
}

bool Regex::match(stream::Stream & is) const {
  DataContext context;
  return ptr_->match(is, context);
}

bool Regex::match(stream::Stream & is, Context & context) const {
  bool res;
  if(context.string_flag()) {
    stream::Stream saved_is = is;
    res = ptr_->match(is, context.dc);
    if(res) {
      saved_is.peek(context.str(), is.pos());
    }
  }
  else {
    res = ptr_->match(is, context.dc);
  }
  return res;
}

bool Regex::match(stream::Stream & is, DataContext & context) const {
  return ptr_->match(is, context);
}

utils::ParserPtr Regex::ptr() const & {
  return ptr_;
}

utils::ParserPtr Regex::ptr() && {
  return std::move(ptr_);
}

} // namespace regex
} // namespace pm
