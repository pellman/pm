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
#ifndef __REGEXP_FUNCTION_CA_HPP
#define __REGEXP_FUNCTION_CA_HPP

#include <utility>
#include <type_abuse/dfun.hpp>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class CA
  : public Literal {
public:
  // DEFAULTS
  // CA() deleted
  // CONSTRUCTORS
  inline CA(const type_abuse::Creator & cr, const type_abuse::CRef<Literal> & rl, const type_abuse::Applier & ap);
  inline CA(const type_abuse::Creator & cr, const type_abuse::CRef<Literal> & rl, type_abuse::Applier && ap);
  inline CA(const type_abuse::Creator & cr, type_abuse::CRef<Literal> && rl, const type_abuse::Applier & ap);
  inline CA(const type_abuse::Creator & cr, type_abuse::CRef<Literal> && rl, type_abuse::Applier && ap);
  inline CA(type_abuse::Creator && cr, const type_abuse::CRef<Literal> & rl, const type_abuse::Applier & ap);
  inline CA(type_abuse::Creator && cr, const type_abuse::CRef<Literal> & rl, type_abuse::Applier && ap);
  inline CA(type_abuse::Creator && cr, type_abuse::CRef<Literal> && rl, const type_abuse::Applier & ap);
  inline CA(type_abuse::Creator && cr, type_abuse::CRef<Literal> && rl, type_abuse::Applier && ap);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::Creator cr_;
  const type_abuse::CRef<Literal> rl_;
  const type_abuse::Applier ap_;
};

inline Regexp ca(const type_abuse::Creator & cr, const Regexp & r, const type_abuse::Applier & ap);
inline Regexp ca(const type_abuse::Creator & cr, const Regexp & r, type_abuse::Applier && ap);
inline Regexp ca(const type_abuse::Creator & cr, Regexp && r, const type_abuse::Applier & ap);
inline Regexp ca(const type_abuse::Creator & cr, Regexp && r, type_abuse::Applier && ap);
inline Regexp ca(type_abuse::Creator && cr, const Regexp & r, const type_abuse::Applier & ap);
inline Regexp ca(type_abuse::Creator && cr, const Regexp & r, type_abuse::Applier && ap);
inline Regexp ca(type_abuse::Creator && cr, Regexp && r, const type_abuse::Applier & ap);
inline Regexp ca(type_abuse::Creator && cr, Regexp && r, type_abuse::Applier && ap);


// IMPLEMENTATION
CA::CA(const type_abuse::Creator & cr, const type_abuse::CRef<Literal> & rl, const type_abuse::Applier & ap)
  : cr_(cr),
    rl_(rl),
    ap_(ap) {}

CA::CA(const type_abuse::Creator & cr, const type_abuse::CRef<Literal> & rl, type_abuse::Applier && ap)
  : cr_(cr),
    rl_(rl),
    ap_(std::move(ap)) {}

CA::CA(const type_abuse::Creator & cr, type_abuse::CRef<Literal> && rl, const type_abuse::Applier & ap)
  : cr_(cr),
    rl_(std::move(rl)),
    ap_(ap) {}

CA::CA(const type_abuse::Creator & cr, type_abuse::CRef<Literal> && rl, type_abuse::Applier && ap)
  : cr_(cr),
    rl_(std::move(rl)),
    ap_(std::move(ap)) {}

CA::CA(type_abuse::Creator && cr, const type_abuse::CRef<Literal> & rl, const type_abuse::Applier & ap)
  : cr_(std::move(cr)),
    rl_(rl),
    ap_(ap) {}

CA::CA(type_abuse::Creator && cr, const type_abuse::CRef<Literal> & rl, type_abuse::Applier && ap)
  : cr_(std::move(cr)),
    rl_(rl),
    ap_(std::move(ap)) {}

CA::CA(type_abuse::Creator && cr, type_abuse::CRef<Literal> && rl, const type_abuse::Applier & ap)
  : cr_(std::move(cr)),
    rl_(std::move(rl)),
    ap_(ap) {}

CA::CA(type_abuse::Creator && cr, type_abuse::CRef<Literal> && rl, type_abuse::Applier && ap)
  : cr_(std::move(cr)),
    rl_(std::move(rl)),
    ap_(std::move(ap)) {}

Regexp ca(const type_abuse::Creator & cr, const Regexp & r, const type_abuse::Applier & ap) {return type_abuse::CRef<Literal>::create<CA>(cr, r.rl, ap);}

Regexp ca(const type_abuse::Creator & cr, const Regexp & r, type_abuse::Applier && ap) {return type_abuse::CRef<Literal>::create<CA>(cr, r.rl, std::move(ap));}

Regexp ca(const type_abuse::Creator & cr, Regexp && r, const type_abuse::Applier & ap) {return type_abuse::CRef<Literal>::create<CA>(cr, std::move(r.rl), ap);}

Regexp ca(const type_abuse::Creator & cr, Regexp && r, type_abuse::Applier && ap) {return type_abuse::CRef<Literal>::create<CA>(cr, std::move(r.rl), std::move(ap));}

Regexp ca(type_abuse::Creator && cr, const Regexp & r, const type_abuse::Applier & ap) {return type_abuse::CRef<Literal>::create<CA>(std::move(cr), r.rl, ap);}

Regexp ca(type_abuse::Creator && cr, const Regexp & r, type_abuse::Applier && ap) {return type_abuse::CRef<Literal>::create<CA>(std::move(cr), r.rl, std::move(ap));}

Regexp ca(type_abuse::Creator && cr, Regexp && r, const type_abuse::Applier & ap) {return type_abuse::CRef<Literal>::create<CA>(std::move(cr), std::move(r.rl), ap);}

Regexp ca(type_abuse::Creator && cr, Regexp && r, type_abuse::Applier && ap) {return type_abuse::CRef<Literal>::create<CA>(std::move(cr), std::move(r.rl), std::move(ap));}

} // namespace regexp
} // namespace pm

#endif
