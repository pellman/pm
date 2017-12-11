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

#include "pm/utils/container_functions.hpp"

namespace pm {
namespace regexp {

namespace {

// core
class LetButSet
  : public RegexpInterface {
public:
  // DEFAULTS
  // AnyLetButSet() deleted
  // CONSTRUCTORS
  LetButSet(const std::set<char> & bad_chars);
  LetButSet(std::set<char> && bad_chars);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  std::set<char> bad_chars_;
};

// core implementation
LetButSet::LetButSet(const std::set<char> & bad_chars)
  : bad_chars_(bad_chars) {}

LetButSet::LetButSet(std::set<char> && bad_chars)
  : bad_chars_(std::move(bad_chars)) {}

bool LetButSet::match_full(stream::Stream & s, const Context & context) const {
  char c;
  if(!s.get(c)) {
    return false;
  }
  if(utils::is_in(c, bad_chars_)) {
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
Regexp letbut(const std::set<char> & s) {return new LetButSet(s);}
Regexp letbut(std::set<char> && s) {return new LetButSet(std::move(s));}

} // namespace regexp
} // namespace pm
