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
#ifndef PM_SET_DEFINITIONS_UNIVERSAL_HPP
#define PM_SET_DEFINITIONS_UNIVERSAL_HPP

//#include <array>
//#include <cstddef>
//#include <functional>
#include <string>
//#include <utility>
//#include "pm/data/data.hpp"
//#include "pm/utility/pack_tricks.hpp"

#include "pm/set/definition.hpp"
#include "pm/set/utils/functions/universal.hpp"
//#include "pm/set/utils/interpreter.hpp"

namespace pm {
namespace set {
namespace utils {

template<typename ... String>
class InterpreterUniversal
  : public utils::Interpreter {
public:
  InterpreterUniversal(std::function<void(typename utility::replicate<data::Data &, String>::type ...)> f, String ... names) : f_(std::move(f)), names_{std::move(names) ...} {}
  utils::Function interpret(Domain & dom) const override {
    return interpret_template(std::index_sequence_for<String ...> {}, dom);
  }
private:
  template<size_t ... indexes>
  utils::Function interpret_template(std::index_sequence<indexes ...>, Domain & dom) const {
    return utils::fun(f_, dom.add(std::get<indexes>(names_)) ...);
  }
  const std::function<void(typename utility::replicate<data::Data &, String>::type ...)> f_;
  const std::array<std::string, sizeof...(String)> names_;
};

} // namespace utils

template<typename ... String>
Definition fun(std::function<void(typename utility::replicate<data::Data &, String>::type ...)> f, String ... names) {
  return new utils::InterpreterUniversal<String ...>(std::move(f), std::move(names) ...);
}

} // namespace set
} // namespace pm

#endif
