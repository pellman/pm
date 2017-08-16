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
#ifndef __REGEXP_FUNCTION_MA_HPP
#define __REGEXP_FUNCTION_MA_HPP

#include <utility>
#include <type_abuse/dfun.hpp>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class MA
  : public Literal {
public:
  // DEFAULTS
  // MA() deleted
  // CONSTRUCTORS
  inline MA(const type_abuse::Modifier & md, const type_abuse::CRef<Literal> & rl, const type_abuse::Applier & ap);
  inline MA(const type_abuse::Modifier & md, const type_abuse::CRef<Literal> & rl, type_abuse::Applier && ap);
  inline MA(const type_abuse::Modifier & md, type_abuse::CRef<Literal> && rl, const type_abuse::Applier & ap);
  inline MA(const type_abuse::Modifier & md, type_abuse::CRef<Literal> && rl, type_abuse::Applier && ap);
  inline MA(type_abuse::Modifier && md, const type_abuse::CRef<Literal> & rl, const type_abuse::Applier & ap);
  inline MA(type_abuse::Modifier && md, const type_abuse::CRef<Literal> & rl, type_abuse::Applier && ap);
  inline MA(type_abuse::Modifier && md, type_abuse::CRef<Literal> && rl, const type_abuse::Applier & ap);
  inline MA(type_abuse::Modifier && md, type_abuse::CRef<Literal> && rl, type_abuse::Applier && ap);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::Modifier md_;
  const type_abuse::CRef<Literal> rl_;
  const type_abuse::Applier ap_;
};

inline Regexp ma(const type_abuse::Modifier & md, const Regexp & r, const type_abuse::Applier & ap);
inline Regexp ma(const type_abuse::Modifier & md, const Regexp & r, type_abuse::Applier && ap);
inline Regexp ma(const type_abuse::Modifier & md, Regexp && r, const type_abuse::Applier & ap);
inline Regexp ma(const type_abuse::Modifier & md, Regexp && r, type_abuse::Applier && ap);
inline Regexp ma(type_abuse::Modifier && md, const Regexp & r, const type_abuse::Applier & ap);
inline Regexp ma(type_abuse::Modifier && md, const Regexp & r, type_abuse::Applier && ap);
inline Regexp ma(type_abuse::Modifier && md, Regexp && r, const type_abuse::Applier & ap);
inline Regexp ma(type_abuse::Modifier && md, Regexp && r, type_abuse::Applier && ap);


// IMPLEMENTATION
MA::MA(const type_abuse::Modifier & md, const type_abuse::CRef<Literal> & rl, const type_abuse::Applier & ap)
  : md_(md),
    rl_(rl),
    ap_(ap) {}

MA::MA(const type_abuse::Modifier & md, const type_abuse::CRef<Literal> & rl, type_abuse::Applier && ap)
  : md_(md),
    rl_(rl),
    ap_(std::move(ap)) {}

MA::MA(const type_abuse::Modifier & md, type_abuse::CRef<Literal> && rl, const type_abuse::Applier & ap)
  : md_(md),
    rl_(std::move(rl)),
    ap_(ap) {}

MA::MA(const type_abuse::Modifier & md, type_abuse::CRef<Literal> && rl, type_abuse::Applier && ap)
  : md_(md),
    rl_(std::move(rl)),
    ap_(std::move(ap)) {}

MA::MA(type_abuse::Modifier && md, const type_abuse::CRef<Literal> & rl, const type_abuse::Applier & ap)
  : md_(std::move(md)),
    rl_(rl),
    ap_(ap) {}

MA::MA(type_abuse::Modifier && md, const type_abuse::CRef<Literal> & rl, type_abuse::Applier && ap)
  : md_(std::move(md)),
    rl_(rl),
    ap_(std::move(ap)) {}

MA::MA(type_abuse::Modifier && md, type_abuse::CRef<Literal> && rl, const type_abuse::Applier & ap)
  : md_(std::move(md)),
    rl_(std::move(rl)),
    ap_(ap) {}

MA::MA(type_abuse::Modifier && md, type_abuse::CRef<Literal> && rl, type_abuse::Applier && ap)
  : md_(std::move(md)),
    rl_(std::move(rl)),
    ap_(std::move(ap)) {}

Regexp ma(const type_abuse::Modifier & md, const Regexp & r, const type_abuse::Applier & ap) {return type_abuse::CRef<Literal>::create<MA>(md, r.rl, ap);}

Regexp ma(const type_abuse::Modifier & md, const Regexp & r, type_abuse::Applier && ap) {return type_abuse::CRef<Literal>::create<MA>(md, r.rl, std::move(ap));}

Regexp ma(const type_abuse::Modifier & md, Regexp && r, const type_abuse::Applier & ap) {return type_abuse::CRef<Literal>::create<MA>(md, std::move(r.rl), ap);}

Regexp ma(const type_abuse::Modifier & md, Regexp && r, type_abuse::Applier && ap) {return type_abuse::CRef<Literal>::create<MA>(md, std::move(r.rl), std::move(ap));}

Regexp ma(type_abuse::Modifier && md, const Regexp & r, const type_abuse::Applier & ap) {return type_abuse::CRef<Literal>::create<MA>(std::move(md), r.rl, ap);}

Regexp ma(type_abuse::Modifier && md, const Regexp & r, type_abuse::Applier && ap) {return type_abuse::CRef<Literal>::create<MA>(std::move(md), r.rl, std::move(ap));}

Regexp ma(type_abuse::Modifier && md, Regexp && r, const type_abuse::Applier & ap) {return type_abuse::CRef<Literal>::create<MA>(std::move(md), std::move(r.rl), ap);}

Regexp ma(type_abuse::Modifier && md, Regexp && r, type_abuse::Applier && ap) {return type_abuse::CRef<Literal>::create<MA>(std::move(md), std::move(r.rl), std::move(ap));}

} // namespace regexp
} // namespace pm

#endif
