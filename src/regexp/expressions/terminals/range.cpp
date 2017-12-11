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
#include "pm/regexp/expressions/terminals.hpp"

namespace pm {
namespace regexp {

namespace {

// core
class Range
  : public RegexpInterface {
public:
  // DEFAULTS
  // Range() deleted
  // CONSTRUCTORS
  Range(char bottom_char, char top_char);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  char bottom_char_, top_char_;
};

// core implementation
Range::Range(char bottom_char, char top_char)
  : bottom_char_(bottom_char),
    top_char_(top_char) {}

bool Range::match_full(stream::Stream & s, const Context & context) const {
  char c;
  if(!s.get(c)) {
    return false;
  }
  if(c < bottom_char_ || c > top_char_) {
    s.unget(c);
    return false;
  }
  if(context.castr.active()) {
    context.str() += c;
  }
  if(context.cadata.active()) {
    context.data().set<char>(c);
  }
  return true;
}

} // namespace

// interface
Regexp range(char bottom_char, char top_char) {return new Range(bottom_char, top_char);}

} // namespace regexp
} // namespace pm
