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
#ifndef PM_GRAMMAR_UTILS_INTERPRETER_HPP
#define PM_GRAMMAR_UTILS_INTERPRETER_HPP

//#include <string>
//#include <memory>

//#include "pm/grammar/utils/action.hpp"
#include "pm/grammar/utils/interpret_info.hpp"
#include "pm/grammar/utils/model.hpp"

namespace pm {
namespace grammar {
namespace utils {

class Interpreter {
public:
  virtual ~Interpreter();
  size_t add_name(const std::string & name, Model & model, InterpretInfo & ii) const;
  virtual Action interpret(Model & model, InterpretInfo & ii) const = 0;
};

typedef std::shared_ptr<Interpreter> InterpreterPtr;

} // namespace utils
} // namespace grammar
} // namespace pm

#endif