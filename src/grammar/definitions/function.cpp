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
#include "pm/grammar/definitions/function.hpp"

#include <utility>
//#include "pm/set/definition.hpp"

//#include "pm/grammar/definition.hpp"
#include "pm/grammar/utils/actions/function.hpp"
#include "pm/grammar/utils/interpreter.hpp"

namespace pm {
namespace grammar {

namespace {

// core
class InterpreterFunction
  : public utils::Interpreter {
public:
  InterpreterFunction(set::Definition df);
  utils::Action interpret(utils::Model & model, utils::InterpretInfo & ii) const override;
private:
  const set::Definition df_;
};

// core implementation
InterpreterFunction::InterpreterFunction(set::Definition df)
  : df_(std::move(df)) {}

utils::Action InterpreterFunction::interpret(utils::Model &, utils::InterpretInfo & ii) const {
  return utils::fun(df_.interpret(ii.data_domain));
}

} // namespace

// interface
Definition fun(set::Definition df) {
  return new InterpreterFunction(std::move(df));
}

} // namespace grammar
} // namespace pm