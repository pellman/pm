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
#include "pm/regexp/expressions/terminal/string.hpp"

namespace pm {
namespace regexp {

namespace {

// core
class Str
  : public RegexpInterface {
public:
  // DEFAULTS
  // Str() deleted
  // CONSTRUCTORS
  Str(const std::string & good_string);
  Str(std::string && good_string);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  std::string good_string_;
};

// core implementation
Str::Str(const std::string & good_string)
  : good_string_(good_string) {}

Str::Str(std::string && good_string)
  : good_string_(std::move(good_string)) {}

bool Str::match_full(stream::Stream & s, const Context & context) const {
  std::string s_get;
  if(!s.get_strict(s_get, good_string_.size())) {
    return false;
  }
  if(s_get != good_string_) {
    s.unget(s_get);
    return false;
  }
  if(context.string_flag()) {
    if(context.data_flag()) {
      context.str() += s_get;
    }
    else {
      context.str() += std::move(std::move(s_get));
    }
  }
  if(context.data_flag()) {
    context.p_current_data.set<std::string>(std::move(s_get));
  }
  return true;
}

} // namespace

// interface
Regexp str(const std::string & good_string) {return new Str(good_string);}
Regexp str(std::string && good_string) {return new Str(std::move(good_string));}

} // namespace regexp
} // namespace pm
