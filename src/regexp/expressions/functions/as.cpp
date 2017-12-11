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
class AS
  : public RegexpInterface {
public:
  // DEFAULTS
  // AS() deleted
  // CONSTRUCTORS
  AS(const type_abuse::BinFun & f);
  AS(type_abuse::BinFun && f);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  type_abuse::BinFun f_;
};

// core implementation
AS::AS(const type_abuse::BinFun & f)
  : f_(f) {}

AS::AS(type_abuse::BinFun && f)
  : f_(std::move(f)) {}

bool AS::match_full(stream::Stream & s, const Context & context) const {
  if(context.cadata.active()) {
    f_(context.cadata.cdata.safe, context.cadata.cdata.current);
  }
  return true;
}

} // namespace

// interface
Regexp as(const type_abuse::BinFun & f) {return new AS(f);}
Regexp as(type_abuse::BinFun && f) {return new AS(std::move(f));}

} // namespace regexp
} // namespace pm
