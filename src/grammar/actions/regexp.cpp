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
#include "pm/grammar/actions.hpp"

#include <utility>
#include "pm/utils/optional.hpp"
#include "pm/grammar/grammar.hpp"

namespace pm {
namespace grammar {

namespace {

// core
class Re
  : public ActionInterface {
public:
  // DEFAULTS
  // Re() deleted
  // CONSTRUCTORS
  Re(const regexp::Regexp & r);
  Re(regexp::Regexp && r);
  Re(const regexp::Regexp & r, size_t data_index);
  Re(regexp::Regexp && r, size_t data_index);
  // PRESERVING METHODS
  bool gamatch(stream::Stream & s, const Grammar & g, const Context & gcontext) const override;
  
private:
  // FIELDS
  regexp::Regexp r_;
  utils::Optional<size_t> data_index_;
};

// core implementation
Re::Re(const regexp::Regexp & r)
  : r_(r) {}

Re::Re(regexp::Regexp && r)
  : r_(std::move(r)) {}

Re::Re(const regexp::Regexp & r, size_t data_index)
  : r_(r),
    data_index_(data_index) {}

Re::Re(regexp::Regexp && r, size_t data_index)
  : r_(std::move(r)),
    data_index_(data_index) {}

bool Re::gamatch(stream::Stream & s, const Grammar & g, const Context & gcontext) const {
  regexp::Context context;
  if(g.has_skip()) {
    context.string_flag() = true;
    while(g.skip().match(s, context));
    if(!gcontext.string_flag()) {
      context.string_flag() = false;
    }
  }
  else {
    if(gcontext.string_flag()) {
      context.p_string_flag = gcontext.p_string_flag;
      context.p_string = gcontext.p_string;
    }
  }
  if(gcontext.data_flag() && data_index_.nonempty()) {
    context.data_flag() = true;
    context.p_current_data = gcontext.ptr(data_index_.val());
  }
  bool res = r_.match(s, context);
  if(g.has_skip()) {
    if(res) {
      if(gcontext.string_flag()) {
        gcontext.str() += std::move(context.str());
      }
    }
    else {
      s.unget(std::move(context.str()));
    }
  }
  return res;
}

} // namespace

// interface
Action ac(const regexp::Regexp & r) {return new Re(r);}
Action ac(regexp::Regexp && r) {return new Re(std::move(r));}
Action ac(const regexp::Regexp & r, size_t data_index) {return new Re(r, data_index);}
Action ac(regexp::Regexp && r, size_t data_index) {return new Re(std::move(r), data_index);}

} // namespace grammar
} // namespace pm
