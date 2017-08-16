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
#ifndef __REGEXP_FUNCTION_MX_HPP
#define __REGEXP_FUNCTION_MX_HPP

#include <utility>
#include <type_abuse/dfun.hpp>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class MX
  : public Literal {
public:
  // DEFAULTS
  // MX() deleted
  // CONSTRUCTORS
  inline MX(const type_abuse::Modifier & md, const type_abuse::CRef<Literal> & rl);
  inline MX(const type_abuse::Modifier & md, type_abuse::CRef<Literal> && rl);
  inline MX(type_abuse::Modifier && md, const type_abuse::CRef<Literal> & rl);
  inline MX(type_abuse::Modifier && md, type_abuse::CRef<Literal> && rl);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::Modifier md_;
  const type_abuse::CRef<Literal> rl_;
};

inline Regexp mx(const type_abuse::Modifier & md, const Regexp & r);
inline Regexp mx(type_abuse::Modifier && md, const Regexp & r);
inline Regexp mx(const type_abuse::Modifier & md, Regexp && r);
inline Regexp mx(type_abuse::Modifier && md, Regexp && r);


// IMPLEMENTATION
MX::MX(const type_abuse::Modifier & md, const type_abuse::CRef<Literal> & rl)
  : md_(md),
    rl_(rl) {}

MX::MX(const type_abuse::Modifier & md, type_abuse::CRef<Literal> && rl)
  : md_(md),
    rl_(std::move(rl)) {}

MX::MX(type_abuse::Modifier && md, const type_abuse::CRef<Literal> & rl)
  : md_(std::move(md)),
    rl_(rl) {}

MX::MX(type_abuse::Modifier && md, type_abuse::CRef<Literal> && rl)
  : md_(std::move(md)),
    rl_(std::move(rl)) {}

Regexp mx(const type_abuse::Modifier & md, const Regexp & r) {return type_abuse::CRef<Literal>::create<MX>(md, r.rl);}

Regexp mx(const type_abuse::Modifier & md, Regexp && r) {return type_abuse::CRef<Literal>::create<MX>(md, std::move(r.rl));}

Regexp mx(type_abuse::Modifier && md, const Regexp & r) {return type_abuse::CRef<Literal>::create<MX>(std::move(md), r.rl);}

Regexp mx(type_abuse::Modifier && md, Regexp && r) {return type_abuse::CRef<Literal>::create<MX>(std::move(md), std::move(r.rl));}

} // namespace regexp
} // namespace pm

#endif
