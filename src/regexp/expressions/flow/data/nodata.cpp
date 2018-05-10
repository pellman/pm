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
#include "pm/regexp/expressions/flow/data.hpp"

#include <utility>

namespace pm {
namespace regexp {

namespace {

// core
class NoData
  : public RegexpInterface {
public:
  // DEFAULTS
  // NoData() deleted
  // CONSTRUCTORS
  NoData(const Regexp & r);
  NoData(Regexp && r);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  Regexp r_;
};

// core implementation
NoData::NoData(const Regexp & r)
  : r_(r) {}

NoData::NoData(Regexp && r)
  : r_(std::move(r)) {}

bool NoData::match_full(stream::Stream & s, const Context & context) const {
  if(!context.data_flag()) {
    return r_.match_full(s, context);
  }
  context.data_flag() = false;
  bool res = r_.match_full(s, context);
  context.data_flag() = true;
  return res;
}

} // namespace

// interface
Regexp nodata(const Regexp & r) {return new NoData(r);}
Regexp nodata(Regexp && r) {return new NoData(std::move(r));}
Regexp operator ~(const Regexp & r) {return nodata(r);}
Regexp operator ~(Regexp && r) {return nodata(std::move(r));}

} // namespace regexp
} // namespace pm
