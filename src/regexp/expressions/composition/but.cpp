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

#include "pm/regexp/expressions/terminals.hpp"

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
  Context aux_context = {{true}, context.cadata};
  if(context.cadata.active()) {
    aux_context.cadata.cdata.detach();
  }
  if(!positive_.match_full(s, aux_context)) {
    return false;
  }
  if(concat(negative_, end()).match(aux_context.str())) {
    s.unget(aux_context.str());
    return false;
  }
  if(context.castr.active()) {
    context.str() += std::move(aux_context.str());
  }
  if(context.cadata.active()) {
    context.cadata.cdata.swap(aux_context.cadata.cdata);
  }
  return true;
}

} // namespace

// interface
Regexp but(const Regexp & positive, const Regexp & negative) {return new But(positive, negative);}
Regexp but(const Regexp & positive, Regexp && negative) {return new But(positive, std::move(negative));}
Regexp but(Regexp && positive, const Regexp & negative) {return new But(std::move(positive), negative);}
Regexp but(Regexp && positive, Regexp && negative) {return new But(std::move(positive), std::move(negative));}

} // namespace regexp
} // namespace pm
