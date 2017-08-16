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
#ifndef __REGEXP_BASIC_ANYLETBUT_HPP
#define __REGEXP_BASIC_ANYLETBUT_HPP

#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class AnyLetBut
  : public Literal {
public:
  // DEFAULTS
  // AnyLetBut() deleted
  // CONSTRUCTORS
  inline AnyLetBut(char bad_char);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const char bad_char_;
};

inline Regexp anyletbut(char bad_char);


// IMPLEMENTATION
AnyLetBut::AnyLetBut(char bad_char)
  : bad_char_(bad_char) {}

Regexp anyletbut(char bad_char) {return type_abuse::CRef<Literal>::create<AnyLetBut>(bad_char);}

} // namespace regexp
} // namespace pm

#endif
