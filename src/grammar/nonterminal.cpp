/*
    This file is part of the pm library package.
    Copyright (C) 2017-2019 Vladislav Podymov

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
#include "pm/grammar/nonterminal.hpp"

//#include <cstddef>
//#include <iosfwd>
#include <utility>
//#include "pm/set/set.hpp"
//#include "pm/stream/stream.hpp"

//#include "pm/grammar/context.hpp"
#include "pm/grammar/utils/actions/constants.hpp"
//#include "pm/grammar/utils/model.hpp"

namespace pm {
namespace grammar {

Nonterminal::Nonterminal()
  : model_ptr_(new utils::Model()),
    index_(model_ptr_->add(utils::afalse())) {}

bool Nonterminal::match(std::istream & is) const {
  stream::Stream s(is);
  return match(s);
}

bool Nonterminal::match(std::istream & is, Context & context) const {
  stream::Stream s(is);
  return match(s, context);
}

bool Nonterminal::match(stream::Stream & is) const {
  set::Set ds;
  return (*model_ptr_)[index_].match(is, ds);
}

bool Nonterminal::match(stream::Stream & is, Context & context) const {
  if(context.string_flag()) {
    stream::Stream s = is;
    bool res = match(is, context.ds);
    if(res) {
      s.peek(context.str(), is.pos());
    }
    return res;
  }
  else {
    return match(is, context.ds);
  }
}

bool Nonterminal::match(stream::Stream & is, set::Set & ds) const {
  return (*model_ptr_)[index_].match(is, ds);
}

Nonterminal::Nonterminal(utils::ModelPtr model_ptr, size_t index)
  : model_ptr_(std::move(model_ptr)),
    index_(index) {}

} // namespace grammar
} // namespace pm
