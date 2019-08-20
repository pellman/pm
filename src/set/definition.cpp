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
#include "pm/set/definition.hpp"

#include <utility>

//#include "pm/set/utils/interpreter.hpp"
#include "pm/set/definitions/trivial.hpp"

namespace pm {
namespace set {

Definition::Definition()
  : Definition(fun()) {}

Definition::Definition(utils::Interpreter * ptr)
  : ptr_(ptr) {}

utils::Function Definition::interpret(Domain & dom) const {
  return ptr_->interpret(dom);
}

utils::InterpreterPtr Definition::ptr() const & {
  return ptr_;
}

utils::InterpreterPtr Definition::ptr() && {
  return std::move(ptr_);
}

} // namespace set
} // namespace pm
