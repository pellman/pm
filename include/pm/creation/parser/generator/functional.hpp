/*
    This file is part of the pm library package.
    Copyright (C) 2017-2020 Vladislav Podymov

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
#ifndef PM_CREATION_PARSER_GENERATOR_FUNCTIONAL_HPP
#define PM_CREATION_PARSER_GENERATOR_FUNCTIONAL_HPP

#include <cstddef>

#include <functional>
#include <utility>

#include "pm/creation/parser/functional.hpp"
#include "pm/devel/parser/generator/functional.hpp"
#include "pm/parser.hpp"

namespace pm::parser::generator {

template<typename ... Args>
Parser uref(std::function<void(Args ...)> f) {
  return
    fexecute(
  [f = std::move(f)](Stream &, Context & con) {
    devel::parser::uref_helper(f, con, std::index_sequence_for<Args ...> {});
  }
    );
}
template<typename Ret, typename ... Args>
Parser uret(std::function<Ret(Args ...)> f, size_t index = sizeof...(Args)) {
  return
    fexecute(
  [f = std::move(f), index](Stream &, Context & con) {
    devel::parser::uret_helper(f, con, index, std::index_sequence_for<Args ...> {});
  }
    );
}

template<typename Any, typename ... Args>
Parser ref(Any (*f) (Args ...)) {
  return
    fexecute(
  [f](Stream &, Context & con) {
    devel::parser::ref_helper(f, con, std::index_sequence_for<Args ...> {});
  }
    );
}
template<typename Ret, typename ... Args>
Parser ret(Ret (*f) (Args ...), size_t index = sizeof...(Args)) {
  return
    fexecute(
  [f, index](Stream &, Context & con) {
    devel::parser::ret_helper(f, con, index, std::index_sequence_for<Args ...> {});
  }
    );
}

} // namespace pm::parser::generator

#endif
