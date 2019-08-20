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
#include "pm/grammar/utils/actions/fail_function.hpp"

#include <utility>
#include "pm/set/utils/applier.hpp"
//#include "pm/set/utils/function.hpp"

//#include "pm/grammar/utils/action.hpp"
#include "pm/grammar/utils/parser.hpp"

namespace pm {
namespace grammar {
namespace utils {

namespace {

// core
class ParserFailFunction
  : public Parser {
public:
  ParserFailFunction(ParserPtr ptr, set::utils::ApplierPtr fptr);
  bool match(stream::Stream & is, set::Set & context) const override;

private:
  const ParserPtr ptr_;
  const set::utils::ApplierPtr fptr_;
};

// core implementation
ParserFailFunction::ParserFailFunction(ParserPtr ptr, set::utils::ApplierPtr fptr)
  : ptr_(std::move(ptr)),
    fptr_(std::move(fptr)) {}

bool ParserFailFunction::match(stream::Stream & is, set::Set & ds) const {
  bool res = ptr_->match(is, ds);
  if(!res) {
    fptr_->apply(ds);
  }
  return res;
}

} // namespace

// interface
Action ffun(Action a, set::utils::Function f) {
  return new ParserFailFunction(std::move(a).ptr(), std::move(f).ptr());
}

} // namespace utils
} // namespace grammar
} // namespace pm
