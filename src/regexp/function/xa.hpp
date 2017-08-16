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
#ifndef __REGEXP_FUNCTION_XA_HPP
#define __REGEXP_FUNCTION_XA_HPP

#include <utility>
#include <type_abuse/dfun.hpp>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class XA
  : public Literal {
public:
  // DEFAULTS
  // XA() deleted
  // CONSTRUCTORS
  inline XA(const type_abuse::CRef<Literal> & rl, const type_abuse::Applier & ap);
  inline XA(const type_abuse::CRef<Literal> & rl, type_abuse::Applier && ap);
  inline XA(type_abuse::CRef<Literal> && rl, const type_abuse::Applier & ap);
  inline XA(type_abuse::CRef<Literal> && rl, type_abuse::Applier && ap);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::CRef<Literal> rl_;
  const type_abuse::Applier ap_;
};

inline Regexp xa(const Regexp & r, const type_abuse::Applier & ap);
inline Regexp xa(const Regexp & r, type_abuse::Applier && ap);
inline Regexp xa(Regexp && r, const type_abuse::Applier & ap);
inline Regexp xa(Regexp && r, type_abuse::Applier && ap);


// IMPLEMENTATION
XA::XA(const type_abuse::CRef<Literal> & rl, const type_abuse::Applier & ap)
  : rl_(rl),
    ap_(ap) {}

XA::XA(const type_abuse::CRef<Literal> & rl, type_abuse::Applier && ap)
  : rl_(rl),
    ap_(std::move(ap)) {}

XA::XA(type_abuse::CRef<Literal> && rl, const type_abuse::Applier & ap)
  : rl_(std::move(rl)),
    ap_(ap) {}

XA::XA(type_abuse::CRef<Literal> && rl, type_abuse::Applier && ap)
  : rl_(std::move(rl)),
    ap_(std::move(ap)) {}

Regexp xa(const Regexp & r, const type_abuse::Applier & f) {return type_abuse::CRef<Literal>::create<XA>(r.rl, f);}

Regexp xa(const Regexp & r, type_abuse::Applier && f) {return type_abuse::CRef<Literal>::create<XA>(r.rl, std::move(f));}

Regexp xa(Regexp && r, const type_abuse::Applier & f) {return type_abuse::CRef<Literal>::create<XA>(std::move(r.rl), f);}

Regexp xa(Regexp && r, type_abuse::Applier && f) {return type_abuse::CRef<Literal>::create<XA>(std::move(r.rl), std::move(f));}

} // namespace regexp
} // namespace pm

#endif
