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
#include "pm/regexp/expressions/terminals.hpp"

namespace pm {
namespace regexp {

namespace {

// core
class AnyLetBut
  : public RegexpInterface {
public:
  // DEFAULTS
  // AnyLetBut() deleted
  // CONSTRUCTORS
  AnyLetBut(char bad_char);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  char bad_char_;
};

// core implementation
AnyLetBut::AnyLetBut(char bad_char)
  : bad_char_(bad_char) {}

bool AnyLetBut::match_full(stream::Stream & s, const Context & context) const {
  char c;
  if(!s.get(c)) {
    return false;
  }
  if(c == bad_char_) {
    s.unget(c);
    return false;
  }
  if(context.castr.active()) {
    context.str() += c;
  }
  if(context.cadata.active()) {
    context.data().set<char>(c);
  }
  return true;
}

} // namespace

// interface
Regexp letbut(char bad_char) {return new AnyLetBut(bad_char);}

} // namespace regexp
} // namespace pm
