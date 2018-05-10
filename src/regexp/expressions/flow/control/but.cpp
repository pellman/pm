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
#include "pm/regexp/expressions/flow/control.hpp"

#include <utility>
#include "pm/regexp/expressions/terminal/string.hpp"
#include "pm/regexp/expressions/terminal/symbol.hpp"
#include "pm/regexp/expressions/terminal/trivial.hpp"

namespace pm {
namespace regexp {

namespace {

// core
class But
  : public RegexpInterface {
public:
  // DEFAULTS
  // But() deleted
  // CONSTRUCTORS
  But(const Regexp & positive, const Regexp & negative);
  But(const Regexp & positive, Regexp && negative);
  But(Regexp && positive, const Regexp & negative);
  But(Regexp && positive, Regexp && negative);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  Regexp positive_;
  Regexp negative_;
};

// core implementation
But::But(const Regexp & positive, const Regexp & negative)
  : positive_(positive),
    negative_(negative) {}

But::But(const Regexp & positive, Regexp && negative)
  : positive_(positive),
    negative_(std::move(negative)) {}

But::But(Regexp && positive, const Regexp & negative)
  : positive_(std::move(positive)),
    negative_(negative) {}

But::But(Regexp && positive, Regexp && negative)
  : positive_(std::move(positive)),
    negative_(std::move(negative)) {}

bool But::match_full(stream::Stream & s, const Context & context) const {
  Context aux_context = context;
  aux_context.p_string.detach_unset();
  aux_context.p_string_flag.detach_set(true);
  if(context.data_flag()) {
    aux_context.p_current_data.detach();
    aux_context.p_saved_data.detach();
  }
  if(!positive_.match_full(s, aux_context)) {
    return false;
  }
  if(concat(negative_, end()).match(aux_context.str())) {
    s.unget(aux_context.str());
    return false;
  }
  if(context.string_flag()) {
    context.str() += std::move(aux_context.str());
  }
  if(context.data_flag()) {
    context.p_current_data.swap(aux_context.p_current_data);
    context.p_saved_data.swap(aux_context.p_saved_data);
  }
  return true;
}

} // namespace

// interface
Regexp but(const Regexp & positive, const Regexp & negative) {return new But(positive, negative);}
Regexp but(const Regexp & positive, Regexp && negative) {return new But(positive, std::move(negative));}
Regexp but(Regexp && positive, const Regexp & negative) {return new But(std::move(positive), negative);}
Regexp but(Regexp && positive, Regexp && negative) {return new But(std::move(positive), std::move(negative));}
Regexp operator -(const Regexp & r1, const Regexp & r2) {return but(r1, r2);}
Regexp operator -(const Regexp & r1, Regexp && r2) {return but(r1, std::move(r2));}
Regexp operator -(Regexp && r1, const Regexp & r2) {return but(std::move(r1), r2);}
Regexp operator -(Regexp && r1, Regexp && r2) {return but(std::move(r1), std::move(r2));}
Regexp operator -(const Regexp & r, char c) {return r - let(c);}
Regexp operator -(Regexp && r, char c) {return std::move(r) - let(c);}
Regexp operator -(char c, const Regexp & r) {return let(c) - r;}
Regexp operator -(char c, Regexp && r) {return let(c) - std::move(r);}
Regexp operator -(const Regexp & r, const std::set<char> & s) {return r - let(s);}
Regexp operator -(const Regexp & r, std::set<char> && s) {return r - let(std::move(s));}
Regexp operator -(Regexp && r, const std::set<char> & s) {return std::move(r) - let(s);}
Regexp operator -(Regexp && r, std::set<char> && s) {return std::move(r) - let(std::move(s));}
Regexp operator -(const std::set<char> & s, const Regexp & r) {return let(s) - r;}
Regexp operator -(const std::set<char> & s, Regexp && r) {return let(s) - std::move(r);}
Regexp operator -(std::set<char> && s, const Regexp & r) {return let(std::move(s)) - r;}
Regexp operator -(std::set<char> && s, Regexp && r) {return let(std::move(s)) - std::move(r);}
Regexp operator -(const Regexp & r, const std::string & s) {return r - str(s);}
Regexp operator -(const Regexp & r, std::string && s) {return r - str(std::move(s));}
Regexp operator -(Regexp && r, const std::string & s) {return std::move(r) - str(s);}
Regexp operator -(Regexp && r, std::string && s) {return std::move(r) - str(std::move(s));}
Regexp operator -(const std::string & s, const Regexp & r) {return str(s) - r;}
Regexp operator -(const std::string & s, Regexp && r) {return str(s) - std::move(r);}
Regexp operator -(std::string && s, const Regexp & r) {return str(std::move(s)) - r;}
Regexp operator -(std::string && s, Regexp && r) {return str(std::move(s)) - std::move(r);}

} // namespace regexp
} // namespace pm
