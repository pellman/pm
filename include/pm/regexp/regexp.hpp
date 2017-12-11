/*
    This file is part of the pm library package.
    Copyright (C) 2017, 2018 Vladislav Podymov
    
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
#ifndef __PM_REGEXP_REGEXP_HPP
#define __PM_REGEXP_REGEXP_HPP

#include <utility>
#include "pm/type_abuse/sptr.hpp"
#include "pm/regexp/regexp_interface.hpp"

namespace pm {
namespace regexp {

class Regexp
  : public RegexpInterface {
public:
  // DEFAULTS
  Regexp() = default;
  // CONSTRUCTORS
  inline Regexp(RegexpInterface * arg_ptr);
  inline Regexp(const type_abuse::SPtr<RegexpInterface> & arg_ptr);
  inline Regexp(type_abuse::SPtr<RegexpInterface> && arg_ptr);
  // PRESERVING METHODS
  inline bool match_full(stream::Stream & s, const Context & context) const override;
  // FIELDS
  type_abuse::SPtr<RegexpInterface> ptr;
};


// implementation
Regexp::Regexp(RegexpInterface * arg_ptr)
  : ptr(arg_ptr) {}

Regexp::Regexp(const type_abuse::SPtr<RegexpInterface> & arg_ptr)
  : ptr(arg_ptr) {}

Regexp::Regexp(type_abuse::SPtr<RegexpInterface> && arg_ptr)
  : ptr(std::move(arg_ptr)) {}

bool Regexp::match_full(stream::Stream & s, const Context & context) const {return ptr->match_full(s, context);}

} // namespace regexp
} // namespace pm

#endif
