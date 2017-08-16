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
#ifndef __REGEXP_FUNCTION_NM_HPP
#define __REGEXP_FUNCTION_NM_HPP

#include <utility>
#include <type_abuse/dfun.hpp>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class NM
  : public Literal {
public:
  // DEFAULTS
  // NM() deleted
  // CONSTRUCTORS
  inline NM(const type_abuse::CRef<Literal> & rl, const type_abuse::Modifier & md);
  inline NM(const type_abuse::CRef<Literal> & rl, type_abuse::Modifier && md);
  inline NM(type_abuse::CRef<Literal> && rl, const type_abuse::Modifier & md);
  inline NM(type_abuse::CRef<Literal> && rl, type_abuse::Modifier && md);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::CRef<Literal> rl_;
  const type_abuse::Modifier md_;
};

inline Regexp nm(const Regexp & r, const type_abuse::Modifier & md);
inline Regexp nm(const Regexp & r, type_abuse::Modifier && md);
inline Regexp nm(Regexp && r, const type_abuse::Modifier & md);
inline Regexp nm(Regexp && r, type_abuse::Modifier && md);


// IMPLEMENTATION
NM::NM(const type_abuse::CRef<Literal> & rl, const type_abuse::Modifier & md)
  : rl_(rl),
    md_(md) {}

NM::NM(const type_abuse::CRef<Literal> & rl, type_abuse::Modifier && md)
  : rl_(rl),
    md_(std::move(md)) {}

NM::NM(type_abuse::CRef<Literal> && rl, const type_abuse::Modifier & md)
  : rl_(std::move(rl)),
    md_(md) {}

NM::NM(type_abuse::CRef<Literal> && rl, type_abuse::Modifier && md)
  : rl_(std::move(rl)),
    md_(std::move(md)) {}

Regexp nm(const Regexp & r, const type_abuse::Modifier & md) {return type_abuse::CRef<Literal>::create<NM>(r.rl, md);}

Regexp nm(const Regexp & r, type_abuse::Modifier && md) {return type_abuse::CRef<Literal>::create<NM>(r.rl, std::move(md));}

Regexp nm(Regexp && r, const type_abuse::Modifier & md) {return type_abuse::CRef<Literal>::create<NM>(std::move(r.rl), md);}

Regexp nm(Regexp && r, type_abuse::Modifier && md) {return type_abuse::CRef<Literal>::create<NM>(std::move(r.rl), std::move(md));}

} // namespace regexp
} // namespace pm

#endif
