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
#ifndef __REGEXP_COMPOSITION_ALT_HPP
#define __REGEXP_COMPOSITION_ALT_HPP

#include <utility>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class Alt
  : public Literal {
public:
  // DEFAULTS
  // Alt() deleted
  // CONSTRUCTORS
  inline Alt(const type_abuse::CRef<Literal> & rl1, const type_abuse::CRef<Literal> & rl2);
  inline Alt(const type_abuse::CRef<Literal> & rl1, type_abuse::CRef<Literal> && rl2);
  inline Alt(type_abuse::CRef<Literal> && rl1, const type_abuse::CRef<Literal> & rl2);
  inline Alt(type_abuse::CRef<Literal> && rl1, type_abuse::CRef<Literal> && rl2);
  // PRESERVING METHODS
  inline bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::CRef<Literal> rl1_, rl2_;
};

inline Regexp operator |(const Regexp & r1, const Regexp & r2);
inline Regexp operator |(const Regexp & r1, Regexp && r2);
inline Regexp operator |(Regexp && r1, const Regexp & r2);
inline Regexp operator |(Regexp && r1, Regexp && r2);


// IMPLEMENTATION
Alt::Alt(const type_abuse::CRef<Literal> & rl1, const type_abuse::CRef<Literal> & rl2)
  : rl1_(rl1),
    rl2_(rl2) {}

Alt::Alt(const type_abuse::CRef<Literal> & rl1, type_abuse::CRef<Literal> && rl2)
  : rl1_(rl1),
    rl2_(std::move(rl2)) {}

Alt::Alt(type_abuse::CRef<Literal> && rl1, const type_abuse::CRef<Literal> & rl2)
  : rl1_(std::move(rl1)),
    rl2_(rl2) {}

Alt::Alt(type_abuse::CRef<Literal> && rl1, type_abuse::CRef<Literal> && rl2)
  : rl1_(std::move(rl1)),
    rl2_(std::move(rl2)) {}

bool Alt::match_full(stream::Stream & stream, Context & context) const {return rl1_->match_full(stream, context) || rl2_->match_full(stream, context);}

Regexp operator |(const Regexp & r1, const Regexp & r2) {return type_abuse::CRef<Literal>::create<Alt>(r1.rl, r2.rl);}

Regexp operator |(const Regexp & r1, Regexp && r2) {return type_abuse::CRef<Literal>::create<Alt>(r1.rl, std::move(r2.rl));}

Regexp operator |(Regexp && r1, const Regexp & r2) {return type_abuse::CRef<Literal>::create<Alt>(std::move(r1.rl), r2.rl);}

Regexp operator |(Regexp && r1, Regexp && r2) {return type_abuse::CRef<Literal>::create<Alt>(std::move(r1.rl), std::move(r2.rl));}

} // namespace regexp
} // namespace pm

#endif
