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
#ifndef __REGEXP_BASIC_LETSET_HPP
#define __REGEXP_BASIC_LETSET_HPP

#include <set>
#include <utility>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class LetSet
  : public Literal {
public:
  // DEFAULTS
  // LetSet() deleted
  // CONSTRUCTORS
  inline LetSet(const std::set<char> & good_chars);
  inline LetSet(std::set<char> && good_chars);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const std::set<char> good_chars_;
};

inline Regexp letset(const std::set<char> & good_chars);
inline Regexp letset(std::set<char> && good_chars);


// IMPLEMENTATION
LetSet::LetSet(const std::set<char> & good_chars)
  : good_chars_(good_chars) {}

LetSet::LetSet(std::set<char> && good_chars)
  : good_chars_(std::move(good_chars)) {}

Regexp letset(const std::set<char> & good_chars) {return type_abuse::CRef<Literal>::create<LetSet>(good_chars);}

Regexp letset(std::set<char> && good_chars) {return type_abuse::CRef<Literal>::create<LetSet>(std::move(good_chars));}

} // namespace regexp
} // namespace pm

#endif
