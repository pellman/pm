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
#ifndef __REGEXP_FUNCTION_CM_HPP
#define __REGEXP_FUNCTION_CM_HPP

#include <utility>
#include <type_abuse/dfun.hpp>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class CM
  : public Literal {
public:
  // DEFAULTS
  // CM() deleted
  // CONSTRUCTORS
  inline CM(const type_abuse::Creator & cr, const type_abuse::CRef<Literal> & rl, const type_abuse::Modifier & md);
  inline CM(const type_abuse::Creator & cr, const type_abuse::CRef<Literal> & rl, type_abuse::Modifier && md);
  inline CM(const type_abuse::Creator & cr, type_abuse::CRef<Literal> && rl, const type_abuse::Modifier & md);
  inline CM(const type_abuse::Creator & cr, type_abuse::CRef<Literal> && rl, type_abuse::Modifier && md);
  inline CM(type_abuse::Creator && cr, const type_abuse::CRef<Literal> & rl, const type_abuse::Modifier & md);
  inline CM(type_abuse::Creator && cr, const type_abuse::CRef<Literal> & rl, type_abuse::Modifier && md);
  inline CM(type_abuse::Creator && cr, type_abuse::CRef<Literal> && rl, const type_abuse::Modifier & md);
  inline CM(type_abuse::Creator && cr, type_abuse::CRef<Literal> && rl, type_abuse::Modifier && md);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::Creator cr_;
  const type_abuse::CRef<Literal> rl_;
  const type_abuse::Modifier md_;
};

inline Regexp cm(const type_abuse::Creator & cr, const Regexp & r, const type_abuse::Modifier & md);
inline Regexp cm(const type_abuse::Creator & cr, const Regexp & r, type_abuse::Modifier && md);
inline Regexp cm(const type_abuse::Creator & cr, Regexp && r, const type_abuse::Modifier & md);
inline Regexp cm(const type_abuse::Creator & cr, Regexp && r, type_abuse::Modifier && md);
inline Regexp cm(type_abuse::Creator && cr, const Regexp & r, const type_abuse::Modifier & md);
inline Regexp cm(type_abuse::Creator && cr, const Regexp & r, type_abuse::Modifier && md);
inline Regexp cm(type_abuse::Creator && cr, Regexp && r, const type_abuse::Modifier & md);
inline Regexp cm(type_abuse::Creator && cr, Regexp && r, type_abuse::Modifier && md);


// IMPLEMENTATION
CM::CM(const type_abuse::Creator & cr, const type_abuse::CRef<Literal> & rl, const type_abuse::Modifier & md)
  : cr_(cr),
    rl_(rl),
    md_(md) {}

CM::CM(const type_abuse::Creator & cr, const type_abuse::CRef<Literal> & rl, type_abuse::Modifier && md)
  : cr_(cr),
    rl_(rl),
    md_(std::move(md)) {}

CM::CM(const type_abuse::Creator & cr, type_abuse::CRef<Literal> && rl, const type_abuse::Modifier & md)
  : cr_(cr),
    rl_(std::move(rl)),
    md_(md) {}

CM::CM(const type_abuse::Creator & cr, type_abuse::CRef<Literal> && rl, type_abuse::Modifier && md)
  : cr_(cr),
    rl_(std::move(rl)),
    md_(std::move(md)) {}

CM::CM(type_abuse::Creator && cr, const type_abuse::CRef<Literal> & rl, const type_abuse::Modifier & md)
  : cr_(std::move(cr)),
    rl_(rl),
    md_(md) {}

CM::CM(type_abuse::Creator && cr, const type_abuse::CRef<Literal> & rl, type_abuse::Modifier && md)
  : cr_(std::move(cr)),
    rl_(rl),
    md_(std::move(md)) {}

CM::CM(type_abuse::Creator && cr, type_abuse::CRef<Literal> && rl, const type_abuse::Modifier & md)
  : cr_(std::move(cr)),
    rl_(std::move(rl)),
    md_(md) {}

CM::CM(type_abuse::Creator && cr, type_abuse::CRef<Literal> && rl, type_abuse::Modifier && md)
  : cr_(std::move(cr)),
    rl_(std::move(rl)),
    md_(std::move(md)) {}

Regexp cm(const type_abuse::Creator & cr, const Regexp & r, const type_abuse::Modifier & md) {return type_abuse::CRef<Literal>::create<CM>(cr, r.rl, md);}

Regexp cm(const type_abuse::Creator & cr, const Regexp & r, type_abuse::Modifier && md) {return type_abuse::CRef<Literal>::create<CM>(cr, r.rl, std::move(md));}

Regexp cm(const type_abuse::Creator & cr, Regexp && r, const type_abuse::Modifier & md) {return type_abuse::CRef<Literal>::create<CM>(cr, std::move(r.rl), md);}

Regexp cm(const type_abuse::Creator & cr, Regexp && r, type_abuse::Modifier && md) {return type_abuse::CRef<Literal>::create<CM>(cr, std::move(r.rl), std::move(md));}

Regexp cm(type_abuse::Creator && cr, const Regexp & r, const type_abuse::Modifier & md) {return type_abuse::CRef<Literal>::create<CM>(std::move(cr), r.rl, md);}

Regexp cm(type_abuse::Creator && cr, const Regexp & r, type_abuse::Modifier && md) {return type_abuse::CRef<Literal>::create<CM>(std::move(cr), r.rl, std::move(md));}

Regexp cm(type_abuse::Creator && cr, Regexp && r, const type_abuse::Modifier & md) {return type_abuse::CRef<Literal>::create<CM>(std::move(cr), std::move(r.rl), md);}

Regexp cm(type_abuse::Creator && cr, Regexp && r, type_abuse::Modifier && md) {return type_abuse::CRef<Literal>::create<CM>(std::move(cr), std::move(r.rl), std::move(md));}

} // namespace regexp
} // namespace pm

#endif
