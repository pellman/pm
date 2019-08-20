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
#include "pm/regex/expressions/flow/accumulate.hpp"

//#include <utility>
#include "pm/data/data.hpp"

//#include "pm/regex/regex.hpp"
#include "pm/regex/utils/parser.hpp"

namespace pm {
namespace regex {

namespace {

// core
class ParserAccumulate
  : public utils::Parser {
public:
  ParserAccumulate(utils::ParserPtr ptr);
  bool match(stream::Stream & is, DataContext & context) const override;

private:
  const utils::ParserPtr ptr_;
};

// core implementation
ParserAccumulate::ParserAccumulate(utils::ParserPtr ptr)
  : ptr_(std::move(ptr)) {}

bool ParserAccumulate::match(stream::Stream & is, DataContext & context) const {
  if(!context.flag) {
    return ptr_->match(is, context);
  }
  data::Data saved;
  saved.swap(context.dcur);
  saved.swap(context.dacc);
  bool res = ptr_->match(is, context);
  context.dcur.swap(context.dacc);
  context.dacc.swap(saved);
  return res;
}

} // namespace

// interface
Regex accumulate(Regex r) {
  return new ParserAccumulate(std::move(r).ptr());
}

} // namespace regex
} // namespace pm
