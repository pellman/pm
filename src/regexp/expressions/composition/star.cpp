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

namespace pm {
namespace regexp {

namespace {

// core
class Star
  : public RegexpInterface {
public:
  // DEFAULTS
  // Star() deleted
  // CONSTRUCTORS
  Star(const Regexp & r);
  Star(Regexp && r);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  Regexp r_;
};

// core implementation
Star::Star(const Regexp & r)
  : r_(r) {}

Star::Star(Regexp && r)
  : r_(std::move(r)) {}

bool Star::match_full(stream::Stream & s, const Context & context) const {
  while(r_.match_full(s, context));
  return true;
}

} // namespace

// interface
Regexp star(const Regexp & r) {return new Star(r);}
Regexp star(Regexp && r) {return new Star(std::move(r));}

} // namespace regexp
} // namespace pm
