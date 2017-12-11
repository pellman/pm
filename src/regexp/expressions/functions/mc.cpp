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
#include "pm/regexp/expressions/functions.hpp"

#include <utility>

namespace pm {
namespace regexp {

namespace {

// core
class MC
  : public RegexpInterface {
public:
  // DEFAULTS
  // MC() deleted
  // CONSTRUCTORS
  MC(const type_abuse::UnFun & f);
  MC(type_abuse::UnFun && f);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  type_abuse::UnFun f_;
};

// core implementation
MC::MC(const type_abuse::UnFun & f)
  : f_(f) {}

MC::MC(type_abuse::UnFun && f)
  : f_(std::move(f)) {}

bool MC::match_full(stream::Stream & s, const Context & context) const {
  if(context.cadata.active()) {
    f_(context.cadata.cdata.current);
  }
  return true;
}

} // namespace

// interface
Regexp mc(const type_abuse::UnFun & f) {return new MC(f);}
Regexp mc(type_abuse::UnFun && f) {return new MC(std::move(f));}

} // namespace regexp
} // namespace pm
