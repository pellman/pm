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
#ifndef __REGEXP_FUNCTION_NC_HPP
#define __REGEXP_FUNCTION_NC_HPP

#include <utility>
#include <type_abuse/dfun.hpp>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class NC
  : public Literal {
public:
  // DEFAULTS
  // NC() deleted
  // CONSTRUCTORS
  inline NC(const type_abuse::CRef<Literal> & rl, const type_abuse::Creator & cr);
  inline NC(const type_abuse::CRef<Literal> & rl, type_abuse::Creator && cr);
  inline NC(type_abuse::CRef<Literal> && rl, const type_abuse::Creator & cr);
  inline NC(type_abuse::CRef<Literal> && rl, type_abuse::Creator && cr);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::CRef<Literal> rl_;
  const type_abuse::Creator cr_;
};

inline Regexp nc(const Regexp & r, const type_abuse::Creator & cr);
inline Regexp nc(const Regexp & r, type_abuse::Creator && cr);
inline Regexp nc(Regexp && r, const type_abuse::Creator & cr);
inline Regexp nc(Regexp && r, type_abuse::Creator && cr);


// IMPLEMENTATION
NC::NC(const type_abuse::CRef<Literal> & rl, const type_abuse::Creator & cr)
  : rl_(rl),
    cr_(cr) {}

NC::NC(const type_abuse::CRef<Literal> & rl, type_abuse::Creator && cr)
  : rl_(rl),
    cr_(std::move(cr)) {}

NC::NC(type_abuse::CRef<Literal> && rl, const type_abuse::Creator & cr)
  : rl_(std::move(rl)),
    cr_(cr) {}

NC::NC(type_abuse::CRef<Literal> && rl, type_abuse::Creator && cr)
  : rl_(std::move(rl)),
    cr_(std::move(cr)) {}

Regexp nc(const Regexp & r, const type_abuse::Creator & f) {return type_abuse::CRef<Literal>::create<NC>(r.rl, f);}

Regexp nc(const Regexp & r, type_abuse::Creator && f) {return type_abuse::CRef<Literal>::create<NC>(r.rl, std::move(f));}

Regexp nc(Regexp && r, const type_abuse::Creator & f) {return type_abuse::CRef<Literal>::create<NC>(std::move(r.rl), f);}

Regexp nc(Regexp && r, type_abuse::Creator && f) {return type_abuse::CRef<Literal>::create<NC>(std::move(r.rl), std::move(f));}

} // namespace regexp
} // namespace pm

#endif
