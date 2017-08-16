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
#ifndef __REGEXP_FUNCTION_NX_HPP
#define __REGEXP_FUNCTION_NX_HPP

#include <utility>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class NX
  : public Literal {
public:
  // DEFAULTS
  // NX() deleted
  // CONSTRUCTORS
  inline NX(const type_abuse::CRef<Literal> & rl);
  inline NX(type_abuse::CRef<Literal> && rl);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // FIELDS
  const type_abuse::CRef<Literal> rl_;
};

inline Regexp nx(const Regexp & r);
inline Regexp nx(Regexp && r);


// IMPLEMENTATION
NX::NX(const type_abuse::CRef<Literal> & rl)
  : rl_(rl) {}

NX::NX(type_abuse::CRef<Literal> && rl)
  : rl_(std::move(rl)) {}

Regexp nx(const Regexp & r) {return type_abuse::CRef<Literal>::create<NX>(r.rl);}

Regexp nx(Regexp && r) {return type_abuse::CRef<Literal>::create<NX>(std::move(r.rl));}

} // namespace regexp
} // namespace pm

#endif
