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
#include "pm/grammar/definitions/constants.hpp"

//#include "pm/grammar/definition.hpp"
#include "pm/grammar/utils/actions/constants.hpp"
#include "pm/grammar/utils/interpreter.hpp"

namespace pm {
namespace grammar {

namespace {

// core
class InterpreterFalse
  : public utils::Interpreter {
public:
  utils::Action interpret(utils::Model & model, utils::InterpretInfo & ii) const override;
};

class InterpreterTrue
  : public utils::Interpreter {
public:
  utils::Action interpret(utils::Model & model, utils::InterpretInfo & ii) const override;
};

// core implementation
utils::Action InterpreterFalse::interpret(utils::Model &, utils::InterpretInfo &) const {
  return utils::afalse();
}
utils::Action InterpreterTrue::interpret(utils::Model &, utils::InterpretInfo &) const {
  return utils::atrue();
}

Definition pre_dfalse = {new InterpreterFalse()};
Definition pre_dtrue = {new InterpreterTrue()};

} // namespace

// interface
Definition dfalse() {
  return pre_dfalse;
}
Definition dtrue() {
  return pre_dtrue;
}

} // namespace grammar
} // namespace pm
