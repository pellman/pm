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
#ifndef PM_CREATION_PARSER_GENERATOR_ARITHMETIC_HPP
#define PM_CREATION_PARSER_GENERATOR_ARITHMETIC_HPP

#include "pm/creation/parser/functional.hpp"
#include "pm/parser.hpp"

namespace pm::parser::generator {

template<typename T0, typename T1 = T0>
Parser add() {
  static Parser res =
    fexecute(
  [](Stream &, Context & con) {
    con[0].value<T0>() += con[1].value<T1>();
  }
    );
  return res;
}
template<typename T0, typename T1 = T0>
Parser sub() {
  static Parser res =
    fexecute(
  [](Stream &, Context & con) {
    con[0].value<T0>() -= con[1].value<T1>();
  }
    );
  return res;
}
template<typename T0, typename T1 = T0>
Parser mul() {
  static Parser res =
    fexecute(
  [](Stream &, Context & con) {
    con[0].value<T0>() *= con[1].value<T1>();
  }
    );
  return res;
}
template<typename T0, typename T1 = T0>
Parser div() {
  static Parser res =
    fexecute(
  [](Stream &, Context & con) {
    con[0].value<T0>() /= con[1].value<T1>();
  }
    );
  return res;
}
template<typename T0, typename T1 = T0>
Parser mod() {
  static Parser res =
    fexecute(
  [](Stream &, Context & con) {
    con[0].value<T0>() %= con[1].value<T1>();
  }
    );
  return res;
}

template<typename T0, typename T>
Parser add(T right) {
  return
    fexecute(
  [right = std::move(right)](Stream &, Context & con) {
    con[0].value<T0>() += right;
  }
    );
}
template<typename T0, typename T>
Parser sub(T right) {
  return
    fexecute(
  [right = std::move(right)](Stream &, Context & con) {
    con[0].value<T0>() -= right;
  }
    );
}
template<typename T0, typename T>
Parser mul(T right) {
  return
    fexecute(
  [right = std::move(right)](Stream &, Context & con) {
    con[0].value<T0>() *= right;
  }
    );
}
template<typename T0, typename T>
Parser div(T right) {
  return
    fexecute(
  [right = std::move(right)](Stream &, Context & con) {
    con[0].value<T0>() /= right;
  }
    );
}
template<typename T0, typename T>
Parser mod(T right) {
  return
    fexecute(
  [right = std::move(right)](Stream &, Context & con) {
    con[0].value<T0>() %= right;
  }
    );
}

} // namespace pm::parser::generator

#endif
