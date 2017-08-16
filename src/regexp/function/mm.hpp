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
#ifndef __REGEXP_FUNCTION_MM_HPP
#define __REGEXP_FUNCTION_MM_HPP

#include <utility>
#include <type_abuse/dfun.hpp>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class MM
  : public Literal {
public:
  // DEFAULTS
  // MM() deleted
  // CONSTRUCTORS
  inline MM(const type_abuse::Modifier & md1, const type_abuse::CRef<Literal> & rl, const type_abuse::Modifier & md2);
  inline MM(const type_abuse::Modifier & md1, const type_abuse::CRef<Literal> & rl, type_abuse::Modifier && md2);
  inline MM(const type_abuse::Modifier & md1, type_abuse::CRef<Literal> && rl, const type_abuse::Modifier & md2);
  inline MM(const type_abuse::Modifier & md1, type_abuse::CRef<Literal> && rl, type_abuse::Modifier && md2);
  inline MM(type_abuse::Modifier && md1, const type_abuse::CRef<Literal> & rl, const type_abuse::Modifier & md2);
  inline MM(type_abuse::Modifier && md1, const type_abuse::CRef<Literal> & rl, type_abuse::Modifier && md2) : md1_(std::move(md1)), rl_(rl), md2_(std::move(md2)) {}
  inline MM(type_abuse::Modifier && md1, type_abuse::CRef<Literal> && rl, const type_abuse::Modifier & md2);
  inline MM(type_abuse::Modifier && md1, type_abuse::CRef<Literal> && rl, type_abuse::Modifier && md2);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::Modifier md1_;
  const type_abuse::CRef<Literal> rl_;
  const type_abuse::Modifier md2_;
};

inline Regexp mm(const type_abuse::Modifier & md1, const Regexp & r, const type_abuse::Modifier & md2);
inline Regexp mm(const type_abuse::Modifier & md1, const Regexp & r, type_abuse::Modifier && md2);
inline Regexp mm(const type_abuse::Modifier & md1, Regexp && r, const type_abuse::Modifier & md2);
inline Regexp mm(const type_abuse::Modifier & md1, Regexp && r, type_abuse::Modifier && md2);
inline Regexp mm(type_abuse::Modifier && md1, const Regexp & r, const type_abuse::Modifier & md2);
inline Regexp mm(type_abuse::Modifier && md1, const Regexp & r, type_abuse::Modifier && md2);
inline Regexp mm(type_abuse::Modifier && md1, Regexp && r, const type_abuse::Modifier & md2);
inline Regexp mm(type_abuse::Modifier && md1, Regexp && r, type_abuse::Modifier && md2);


// IMPLEMENTATION
MM::MM(const type_abuse::Modifier & md1, const type_abuse::CRef<Literal> & rl, const type_abuse::Modifier & md2)
  : md1_(md1),
    rl_(rl),
    md2_(md2) {}

MM::MM(const type_abuse::Modifier & md1, const type_abuse::CRef<Literal> & rl, type_abuse::Modifier && md2)
  : md1_(md1),
    rl_(rl),
    md2_(std::move(md2)) {}

MM::MM(const type_abuse::Modifier & md1, type_abuse::CRef<Literal> && rl, const type_abuse::Modifier & md2)
  : md1_(md1),
    rl_(std::move(rl)),
    md2_(md2) {}

MM::MM(const type_abuse::Modifier & md1, type_abuse::CRef<Literal> && rl, type_abuse::Modifier && md2)
  : md1_(md1),
    rl_(std::move(rl)),
    md2_(std::move(md2)) {}

MM::MM(type_abuse::Modifier && md1, const type_abuse::CRef<Literal> & rl, const type_abuse::Modifier & md2)
  : md1_(std::move(md1)),
    rl_(rl),
    md2_(md2) {}

MM::MM(type_abuse::Modifier && md1, type_abuse::CRef<Literal> && rl, const type_abuse::Modifier & md2)
  : md1_(std::move(md1)),
    rl_(std::move(rl)),
    md2_(md2) {}

MM::MM(type_abuse::Modifier && md1, type_abuse::CRef<Literal> && rl, type_abuse::Modifier && md2)
  : md1_(std::move(md1)),
    rl_(std::move(rl)),
    md2_(std::move(md2)) {}

Regexp mm(const type_abuse::Modifier & md1, const Regexp & r, const type_abuse::Modifier & md2) {return type_abuse::CRef<Literal>::create<MM>(md1, r.rl, md2);}

Regexp mm(const type_abuse::Modifier & md1, const Regexp & r, type_abuse::Modifier && md2) {return type_abuse::CRef<Literal>::create<MM>(md1, r.rl, std::move(md2));}

Regexp mm(const type_abuse::Modifier & md1, Regexp && r, const type_abuse::Modifier & md2) {return type_abuse::CRef<Literal>::create<MM>(md1, std::move(r.rl), md2);}

Regexp mm(const type_abuse::Modifier & md1, Regexp && r, type_abuse::Modifier && md2) {return type_abuse::CRef<Literal>::create<MM>(md1, std::move(r.rl), std::move(md2));}

Regexp mm(type_abuse::Modifier && md1, const Regexp & r, const type_abuse::Modifier & md2) {return type_abuse::CRef<Literal>::create<MM>(std::move(md1), r.rl, md2);}

Regexp mm(type_abuse::Modifier && md1, const Regexp & r, type_abuse::Modifier && md2) {return type_abuse::CRef<Literal>::create<MM>(std::move(md1), r.rl, std::move(md2));}

Regexp mm(type_abuse::Modifier && md1, Regexp && r, const type_abuse::Modifier & md2) {return type_abuse::CRef<Literal>::create<MM>(std::move(md1), std::move(r.rl), md2);}

Regexp mm(type_abuse::Modifier && md1, Regexp && r, type_abuse::Modifier && md2) {return type_abuse::CRef<Literal>::create<MM>(std::move(md1), std::move(r.rl), std::move(md2));}

} // namespace regexp
} // namespace pm

#endif
