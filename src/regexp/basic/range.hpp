/*
    This file is part of the pm library package.
    Copyright (C) 2017 Vladislav Podymov
    
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
#ifndef __REGEXP_BASIC_RANGE_HPP
#define __REGEXP_BASIC_RANGE_HPP

#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class Range
  : public Literal {
public:
  // DEFAULTS
  // Range() deleted
  // CONSTRUCTORS
  inline Range(char bottom_char, char top_char);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const char bottom_char_, top_char_;
};

inline Regexp range(char bottom_char, char top_char);


// IMPLEMENTATION
Range::Range(char bottom_char, char top_char)
  : bottom_char_(bottom_char),
    top_char_(top_char) {}

Regexp range(char bottom_char, char top_char) {return type_abuse::CRef<Literal>::create<Range>(bottom_char, top_char);}

} // namespace regexp
} // namespace pm

#endif
