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
#include "pm/regexp/expressions/composition.hpp"

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
  if(context.cadata.inactive()) {
    return r_.match_full(s, context);
  }
  context.cadata.deactivate();
  bool res = r_.match_full(s, context);
  context.cadata.activate();
  return res;
}

} // namespace

// interface
Regexp nodata(const Regexp & r) {return new NoData(r);}
Regexp nodata(Regexp && r) {return new NoData(std::move(r));}

} // namespace regexp
} // namespace pm
