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
#ifndef __REGEXP_COMPOSITION_OPT_HPP
#define __REGEXP_COMPOSITION_OPT_HPP

#include <utility>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class Opt
  : public Literal {
public:
  // DEFAULTS
  // Opt() deleted
  // CONSTRUCTORS
  inline Opt(const type_abuse::CRef<Literal> & optional_literal);
  inline Opt(type_abuse::CRef<Literal> && optional_literal);
  // PRESERVING METHODS
  inline bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::CRef<Literal> opt_lit_;
};

inline Regexp operator !(const Regexp & r);
inline Regexp operator !(Regexp && r);


// IMPLEMENTATION
Opt::Opt(const type_abuse::CRef<Literal> & optional_literal)
  : opt_lit_(optional_literal) {}

Opt::Opt(type_abuse::CRef<Literal> && optional_literal)
  : opt_lit_(std::move(optional_literal)) {}

bool Opt::match_full(stream::Stream & stream, Context & context) const {
  opt_lit_->match_full(stream, context);
  return true;
}

Regexp operator !(const Regexp & r) {return type_abuse::CRef<Literal>::create<Opt>(r.rl);}

Regexp operator !(Regexp && r) {return type_abuse::CRef<Literal>::create<Opt>(std::move(r.rl));}

} // namespace regexp
} // namespace pm

#endif
