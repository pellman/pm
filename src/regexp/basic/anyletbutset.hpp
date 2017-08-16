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
#ifndef __REGEXP_BASIC_ANYLETBUTSET_HPP
#define __REGEXP_BASIC_ANYLETBUTSET_HPP

#include <set>
#include <utility>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class AnyLetButSet
  : public Literal {
public:
  // DEFAULTS
  // AnyLetButSet() deleted
  // CONSTRUCTORS
  inline AnyLetButSet(const std::set<char> & bad_chars);
  inline AnyLetButSet(std::set<char> && bad_chars);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const std::set<char> bad_chars_;
};

inline Regexp anyletbutset(const std::set<char> & bad_chars);
inline Regexp anyletbutset(std::set<char> && bad_chars);


// IMPLEMENTATION
AnyLetButSet::AnyLetButSet(const std::set<char> & bad_chars)
  : bad_chars_(bad_chars) {}

AnyLetButSet::AnyLetButSet(std::set<char> && bad_chars)
  : bad_chars_(std::move(bad_chars)) {}

Regexp anyletbutset(const std::set<char> & s) {return type_abuse::CRef<Literal>::create<AnyLetButSet>(s);}

Regexp anyletbutset(std::set<char> && s) {return type_abuse::CRef<Literal>::create<AnyLetButSet>(std::move(s));}

} // namespace regexp
} // namespace pm

#endif
