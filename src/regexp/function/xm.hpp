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
#ifndef __REGEXP_FUNCTION_XM_HPP
#define __REGEXP_FUNCTION_XM_HPP

#include <utility>
#include <type_abuse/dfun.hpp>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class XM
  : public Literal {
public:
  // DEFAULTS
  // XM() deleted
  // CONSTRUCTORS
  inline XM(const type_abuse::CRef<Literal> & rl, const type_abuse::Modifier & md);
  inline XM(const type_abuse::CRef<Literal> & rl, type_abuse::Modifier && md);
  inline XM(type_abuse::CRef<Literal> && rl, const type_abuse::Modifier & md);
  inline XM(type_abuse::CRef<Literal> && rl, type_abuse::Modifier && md);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::CRef<Literal> rl_;
  const type_abuse::Modifier md_;
};

inline Regexp xm(const Regexp & r, const type_abuse::Modifier & md);
inline Regexp xm(Regexp && r, const type_abuse::Modifier & md);
inline Regexp xm(const Regexp & r, type_abuse::Modifier && md);
inline Regexp xm(Regexp && r, type_abuse::Modifier && md);


// IMPLEMENTATION
XM::XM(const type_abuse::CRef<Literal> & rl, const type_abuse::Modifier & md)
  : rl_(rl),
    md_(md) {}

XM::XM(const type_abuse::CRef<Literal> & rl, type_abuse::Modifier && md)
  : rl_(rl),
    md_(std::move(md)) {}

XM::XM(type_abuse::CRef<Literal> && rl, const type_abuse::Modifier & md)
  : rl_(std::move(rl)),
    md_(md) {}

XM::XM(type_abuse::CRef<Literal> && rl, type_abuse::Modifier && md)
  : rl_(std::move(rl)),
    md_(std::move(md)) {}

Regexp xm(const Regexp & r, const type_abuse::Modifier & f) {return type_abuse::CRef<Literal>::create<XM>(r.rl, f);}

Regexp xm(const Regexp & r, type_abuse::Modifier && f) {return type_abuse::CRef<Literal>::create<XM>(r.rl, std::move(f));}

Regexp xm(Regexp && r, const type_abuse::Modifier & f) {return type_abuse::CRef<Literal>::create<XM>(std::move(r.rl), f);}

Regexp xm(Regexp && r, type_abuse::Modifier && f) {return type_abuse::CRef<Literal>::create<XM>(std::move(r.rl), std::move(f));}

} // namespace regexp
} // namespace pm

#endif
