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
#include "pm/grammar/definitions/assert.hpp"

//#include <string>
#include <utility>

//#include "pm/grammar/definition.hpp"
#include "pm/grammar/utils/actions/assert.hpp"
#include "pm/grammar/utils/interpreter.hpp"

namespace pm {
namespace grammar {

namespace {

// core
class InterpreterAssert
  : public utils::Interpreter {
public:
  InterpreterAssert(std::string data_name);
  utils::Action interpret(utils::Model & model, utils::InterpretInfo & ii) const override;
private:
  // FIELDS
  const std::string data_name_;
};

// core implementation
InterpreterAssert::InterpreterAssert(std::string data_name)
  : data_name_(std::move(data_name)) {}

utils::Action InterpreterAssert::interpret(utils::Model &, utils::InterpretInfo & ii) const {
  return utils::assert(ii.data_domain.add(data_name_));
}

} // namespace

// interface
Definition assert(std::string data_name) {
  return new InterpreterAssert(std::move(data_name));
}

} // namespace grammar
} // namespace pm
