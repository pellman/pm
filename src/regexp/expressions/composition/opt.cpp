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
class Opt
  : public RegexpInterface {
public:
  // DEFAULTS
  // Opt() deleted
  // CONSTRUCTORS
  Opt(const Regexp & r);
  Opt(Regexp && r);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  Regexp r_;
};

// core implementation
Opt::Opt(const Regexp & r)
  : r_(r) {}

Opt::Opt(Regexp && r)
  : r_(std::move(r)) {}

bool Opt::match_full(stream::Stream & s, const Context & context) const {
  r_.match_full(s, context);
  return true;
}

} // namespace

// interface
Regexp opt(const Regexp & r) {return new Opt(r);}
Regexp opt(Regexp && r) {return new Opt(std::move(r));}

} // namespace regexp
} // namespace pm
