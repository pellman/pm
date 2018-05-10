/*
    This file is part of the pm library package.
    Copyright (C) 2017, 2018 Vladislav Podymov
    
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
#include "pm/regexp/expressions/terminal/string.hpp"

namespace pm {
namespace regexp {

namespace {

// core
class StrLen
  : public RegexpInterface {
public:
  // DEFAULTS
  // AnyStr() deleted
  // CONSTRUCTORS
  StrLen(size_t size);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  size_t size_;
};

// core implementation
StrLen::StrLen(size_t size)
  : size_(size) {}

bool StrLen::match_full(stream::Stream & s, const Context & context) const {
  if(!context.string_flag() && !context.data_flag()) {
    return s.skip_strict(size_);
  }
  std::string s_get;
  if(!s.get_strict(s_get, size_)) {
    return false;
  }
  if(context.string_flag()) {
    if(context.data_flag()) {
      context.str() += s_get;
    }
    else {
      context.str() += std::move(s_get);
    }
  }
  if(context.data_flag()) {
    context.p_current_data.set<std::string>(std::move(s_get));
  }
  return true;
}

} // namespace

// interface
Regexp str(size_t len) {return new StrLen(len);}

} // namespace regexp
} // namespace pm
