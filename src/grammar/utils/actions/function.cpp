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
#include "pm/grammar/utils/actions/function.hpp"

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
class ParserFunction
  : public Parser {
public:
  ParserFunction(set::utils::ApplierPtr ptr);
  bool match(stream::Stream & is, set::Set & ds) const override;

private:
  const set::utils::ApplierPtr ptr_;
};

// core implementation
ParserFunction::ParserFunction(set::utils::ApplierPtr ptr)
  : ptr_(std::move(ptr)) {}

bool ParserFunction::match(stream::Stream &, set::Set & ds) const {
  ptr_->apply(ds);
  return true;
}

} // namespace

// interface
Action fun(set::utils::Function f) {
  return new ParserFunction(std::move(f).ptr());
}

} // namespace utils
} // namespace grammar
} // namespace pm
