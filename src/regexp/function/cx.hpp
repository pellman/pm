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
#ifndef __REGEXP_FUNCTION_CX_HPP
#define __REGEXP_FUNCTION_CX_HPP

#include <utility>
#include <type_abuse/dfun.hpp>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class CX
  : public Literal {
public:
  // DEFAULTS
  // CX() deleted
  // CONSTRUCTORS
  inline CX(const type_abuse::Creator & cr, const type_abuse::CRef<Literal> & rl);
  inline CX(const type_abuse::Creator & cr, type_abuse::CRef<Literal> && rl);
  inline CX(type_abuse::Creator && cr, const type_abuse::CRef<Literal> & rl);
  inline CX(type_abuse::Creator && cr, type_abuse::CRef<Literal> && rl);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::Creator cr_;
  const type_abuse::CRef<Literal> rl_;
};

inline Regexp cx(const type_abuse::Creator & cr, const Regexp & r);
inline Regexp cx(const type_abuse::Creator & cr, Regexp && r);
inline Regexp cx(type_abuse::Creator && cr, const Regexp & r);
inline Regexp cx(type_abuse::Creator && cr, Regexp && r);


// IMPLEMENTATION
CX::CX(const type_abuse::Creator & cr, const type_abuse::CRef<Literal> & rl)
  : cr_(cr),
    rl_(rl) {}

CX::CX(const type_abuse::Creator & cr, type_abuse::CRef<Literal> && rl)
  : cr_(cr),
    rl_(std::move(rl)) {}

CX::CX(type_abuse::Creator && cr, const type_abuse::CRef<Literal> & rl)
  : cr_(std::move(cr)),
    rl_(rl) {}

CX::CX(type_abuse::Creator && cr, type_abuse::CRef<Literal> && rl)
  : cr_(std::move(cr)),
    rl_(std::move(rl)) {}

Regexp cx(const type_abuse::Creator & cr, const Regexp & r) {return type_abuse::CRef<Literal>::create<CX>(cr, r.rl);}

Regexp cx(const type_abuse::Creator & cr, Regexp && r) {return type_abuse::CRef<Literal>::create<CX>(cr, std::move(r.rl));}

Regexp cx(type_abuse::Creator && cr, const Regexp & r) {return type_abuse::CRef<Literal>::create<CX>(std::move(cr), r.rl);}

Regexp cx(type_abuse::Creator && cr, Regexp && r) {return type_abuse::CRef<Literal>::create<CX>(std::move(cr), std::move(r.rl));}

} // namespace regexp
} // namespace pm

#endif
