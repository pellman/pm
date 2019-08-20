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
#ifndef PM_GRAMMAR_DEFINITION_HPP
#define PM_GRAMMAR_DEFINITION_HPP

//#include <string>

//#include "pm/grammar/utils/interpret_info.hpp"
#include "pm/grammar/utils/interpreter.hpp"
//#include "pm/grammar/utils/model.hpp"

namespace pm {
namespace grammar {

class Definition {
public:
  // DEFAULTS
  Definition();
  // CONSTRUCTORS
  Definition(utils::Interpreter * ptr);
  // PRESERVING METHODS
  void update(const std::string & name, utils::Model & model, utils::InterpretInfo & ii) const;
  utils::InterpreterPtr ptr() const &;
  utils::InterpreterPtr ptr() &&;
private:
  // FIELDS
  utils::InterpreterPtr ptr_;
};

} // namespace grammar
} // namespace pm

#endif
