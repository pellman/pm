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
#include "pm/grammar/definition.hpp"

//#include <string>
#include <utility>

#include "pm/grammar/definitions/constants.hpp"
//#include "pm/grammar/utils/interpret_info.hpp"
//#include "pm/grammar/utils/interpreter.hpp"
//#include "pm/grammar/utils/model.hpp"

namespace pm {
namespace grammar {

Definition::Definition()
  : Definition(dfalse()) {}

Definition::Definition(utils::Interpreter * ptr)
  : ptr_(ptr) {}

void Definition::update(const std::string & name, utils::Model & model, utils::InterpretInfo & ii) const {
  size_t index = ptr_->add_name(name, model, ii);
  model[index] = ptr_->interpret(model, ii);
}

utils::InterpreterPtr Definition::ptr() const & {
  return ptr_;
}

utils::InterpreterPtr Definition::ptr() && {
  return std::move(ptr_);
}


} // namespace grammar
} // namespace pm
