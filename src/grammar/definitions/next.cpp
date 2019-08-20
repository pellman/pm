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
#include "pm/grammar/definitions/next.hpp"

//#include <string>
#include <utility>

//#include "pm/grammar/definition.hpp"
#include "pm/grammar/utils/actions/next.hpp"
#include "pm/grammar/utils/interpreter.hpp"

namespace pm {
namespace grammar {

namespace {

// core
class InterpreterNext
  : public utils::Interpreter {
public:
  InterpreterNext(std::string d_name);
  utils::Action interpret(utils::Model & model, utils::InterpretInfo & ii) const override;
private:
  const std::string d_name_;
};

// core implementation
InterpreterNext::InterpreterNext(std::string d_name)
  : d_name_(std::move(d_name)) {}

utils::Action InterpreterNext::interpret(utils::Model & model, utils::InterpretInfo & ii) const {
  size_t index = add_name(d_name_, model, ii);
  return utils::next(index, &model);
}

} // namespace

// interface
Definition next(std::string d_name) {
  return new InterpreterNext(std::move(d_name));
}

} // namespace grammar
} // namespace pm
