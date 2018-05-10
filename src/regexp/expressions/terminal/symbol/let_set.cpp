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
#include "pm/regexp/expressions/terminal/symbol.hpp"

#include "pm/utils/container_functions.hpp"

namespace pm {
namespace regexp {

namespace {

// core
class LetSet
  : public RegexpInterface {
public:
  // DEFAULTS
  // LetSet() deleted
  // CONSTRUCTORS
  LetSet(const std::set<char> & good_chars);
  LetSet(std::set<char> && good_chars);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  std::set<char> good_chars_;
};

// core implementation
LetSet::LetSet(const std::set<char> & good_chars)
  : good_chars_(good_chars) {}

LetSet::LetSet(std::set<char> && good_chars)
  : good_chars_(std::move(good_chars)) {}

bool LetSet::match_full(stream::Stream & s, const Context & context) const {
  char c;
  if(!s.get(c)) {
    return false;
  }
  if(utils::isnt_in(c, good_chars_)) {
    s.unget(c);
    return false;
  }
  if(context.string_flag()) {
    context.str() += c;
  }
  if(context.data_flag()) {
    context.p_current_data.set<char>(c);
  }
  return true;
}

} // namespace

// interface
Regexp let(const std::set<char> & good_chars) {return new LetSet(good_chars);}
Regexp let(std::set<char> && good_chars) {return new LetSet(std::move(good_chars));}

} // namespace regexp
} // namespace pm
