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
#ifndef __REGEXP_REGEXP_HPP
#define __REGEXP_REGEXP_HPP

#include <type_abuse/cref.hpp>
#include "regexp/context.hpp"
#include "regexp/literal.hpp"

namespace pm {
namespace regexp {

class Regexp
  : public Literal {
public:
  // DEFAULTS
  inline Regexp();
  // CONSTRUCTORS
  inline Regexp(const type_abuse::CRef<Literal> & rl);
  inline Regexp(type_abuse::CRef<Literal> && rl);
  // PRESERVING METHODS
  inline bool match_full(stream::Stream & stream, Context & context) const override;
  // FIELDS
  type_abuse::CRef<Literal> rl;
};

extern const Regexp skip;


// IMPLEMENTATION
Regexp::Regexp()
  : rl(type_abuse::CRef<Literal>::create(lskip)) {}

Regexp::Regexp(const type_abuse::CRef<Literal> & rl)
  : rl(rl) {}

Regexp::Regexp(type_abuse::CRef<Literal> && rl)
  : rl(std::move(rl)) {}

bool Regexp::match_full(stream::Stream & stream, Context & context) const {return rl->match_full(stream, context);}

} // namespace regexp
} // namespace pm

#endif
