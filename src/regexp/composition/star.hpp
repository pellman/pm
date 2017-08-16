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
#ifndef __REGEXP_COMPOSITION_STAR_HPP
#define __REGEXP_COMPOSITION_STAR_HPP

#include <utility>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class Star
  : public Literal {
public:
  // DEFAULTS
  // Star() deleted
  // CONSTRUCTORS
  inline Star(const type_abuse::CRef<Literal> & starred_literal);
  inline Star(type_abuse::CRef<Literal> && starred_literal);
  // PRESERVING METHODS
  inline bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::CRef<Literal> starred_lit_;
};

inline Regexp operator *(const Regexp & r);
inline Regexp operator *(Regexp && r);


// IMPLEMENTATION
Star::Star(const type_abuse::CRef<Literal> & starred_literal)
  : starred_lit_(starred_literal) {}

Star::Star(type_abuse::CRef<Literal> && starred_literal)
  : starred_lit_(std::move(starred_literal)) {}

bool Star::match_full(stream::Stream & stream, Context & context) const {
  while(starred_lit_->match_full(stream, context));
  return true;
}

Regexp operator *(const Regexp & r) {return type_abuse::CRef<Literal>::create<Star>(r.rl);}

Regexp operator *(Regexp && r) {return type_abuse::CRef<Literal>::create<Star>(std::move(r.rl));}

} // namespace regexp
} // namespace pm

#endif
