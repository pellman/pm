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
#include "pm/grammar/definitions/optional.hpp"

#include <utility>

//#include "pm/grammar/definition.hpp"
#include "pm/grammar/utils/actions/optional.hpp"
#include "pm/grammar/utils/interpreter.hpp"

namespace pm {
namespace grammar {

namespace {

// core
class InterpreterOpt
  : public utils::Interpreter {
public:
  InterpreterOpt(utils::InterpreterPtr ptr);
  utils::Action interpret(utils::Model & model, utils::InterpretInfo & ii) const override;
private:
  const utils::InterpreterPtr ptr_;
};

// core implementation
InterpreterOpt::InterpreterOpt(utils::InterpreterPtr ptr)
  : ptr_(std::move(ptr)) {}

utils::Action InterpreterOpt::interpret(utils::Model & model, utils::InterpretInfo & ii) const {
  return utils::opt(ptr_->interpret(model, ii));
}

} // namespace

// interface
Definition opt(Definition d) {
  return new InterpreterOpt(std::move(d).ptr());
}

} // namespace grammar
} // namespace pm
