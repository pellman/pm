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
#ifndef PM_DEVEL_PARSER_GENERATOR_FUNCTIONAL_HPP
#define PM_DEVEL_PARSER_GENERATOR_FUNCTIONAL_HPP

#include <cstddef>

#include <functional>
#include <utility>

#include "pm/context.hpp"

namespace pm::devel::parser {

template<typename ... Args, size_t ... indexes>
void uref_helper(const std::function<void(Args ...)> & f, Context & con, std::index_sequence<indexes ...>) {
  f(con[indexes].template value<typename std::decay_t<Args>>() ...);
}
template<typename Ret, typename ... Args, size_t ... indexes>
void uret_helper(const std::function<Ret(Args ...)> & f, Context & con, size_t index, std::index_sequence<indexes ...>) {
  con[index].emplace<typename std::decay_t<Ret>>(f(con[indexes].template value<typename std::decay_t<Args>>() ...));
}
template<typename Any, typename ... Args, size_t ... indexes>
void ref_helper(Any (*f) (Args ...), Context & con, std::index_sequence<indexes ...>) {
  f(con[indexes].template value<typename std::decay_t<Args>>() ...);
}
template<typename Ret, typename ... Args, size_t ... indexes>
void ret_helper(Ret (*f) (Args ...), Context & con, size_t index, std::index_sequence<indexes ...>) {
  con[index].emplace<typename std::decay_t<Ret>>(f(con[indexes].template value<typename std::decay_t<Args>>() ...));
}

} // namespace pm::devel::parser

#endif
