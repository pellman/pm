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
#ifndef __REGEXP_BASIC_LET_HPP
#define __REGEXP_BASIC_LET_HPP

#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class Let
  : public Literal {
public:
  // DEFAULTS
  // Let() deleted
  // CONSTRUCTORS
  inline Let(char good_char);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const char good_char_;
};

inline Regexp let(char good_char);


// IMPLEMENTATION
Let::Let(char good_char)
  : good_char_(good_char) {}

Regexp let(char good_char) {return type_abuse::CRef<Literal>::create<Let>(good_char);}

} // namespace regexp
} // namespace pm

#endif
