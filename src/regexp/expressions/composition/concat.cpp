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
class Concat
  : public RegexpInterface {
public:
  // DEFAULTS
  // Concat() deleted
  // CONSTRUCTORS
  Concat(const std::list<Regexp> & rl);
  Concat(std::list<Regexp> && rl);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  std::list<Regexp> rl_;
};

// core implementation
Concat::Concat(const std::list<Regexp> & rl)
  : rl_(rl) {}

Concat::Concat(std::list<Regexp> && rl)
  : rl_(std::move(rl)) {}

bool Concat::match_full(stream::Stream & s, const Context & context) const {
  if(rl_.empty()) {
    return true;
  }
  if(rl_.size() == 1) {
    return rl_.front().match_full(s, context);
  }
  
  Context aux_context = {{true}, context.cadata};
  if(context.cadata.active()) {
    aux_context.cadata.cdata.detach();
  }
  auto ilast = rl_.end();
  --ilast;
  for(auto it = rl_.begin(); it != ilast; ++it) {
    if(!it->match_full(s, aux_context)) {
      s.unget(std::move(aux_context.str()));
      return false;
    }
  }
  if(context.castr.inactive()) {
    aux_context.castr.deactivate();
  }
  if(!ilast->match_full(s, aux_context)) {
    s.unget(std::move(aux_context.str()));
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
Regexp concat(const std::list<Regexp> & rl) {return new Concat(rl);}
Regexp concat(std::list<Regexp> && rl) {return new Concat(std::move(rl));}

} // namespace regexp
} // namespace pm
