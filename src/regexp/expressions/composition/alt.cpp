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
class Alt
  : public RegexpInterface {
public:
  // DEFAULTS
  // AltS() deleted
  // CONSTRUCTORS
  Alt(const std::list<Regexp> & rl);
  Alt(std::list<Regexp> && rl);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  std::list<Regexp> rl_;
};

// core implementation
Alt::Alt(const std::list<Regexp> & rl)
  : rl_(rl) {}

Alt::Alt(std::list<Regexp> && rl)
  : rl_(std::move(rl)) {}

bool Alt::match_full(stream::Stream & s, const Context & context) const {
  for(const auto & r : rl_) {
    if(r.match_full(s, context)) {
      return true;
    }
  }
  return false;
}

} // namespace

// interface
Regexp alt(const std::list<Regexp> & rl) {return new Alt(rl);}
Regexp alt(std::list<Regexp> && rl) {return new Alt(std::move(rl));}

} // namespace regexp
} // namespace pm
