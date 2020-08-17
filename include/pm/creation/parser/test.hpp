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
#ifndef PM_CREATION_PARSER_TEST_HPP
#define PM_CREATION_PARSER_TEST_HPP

#include <utility>

#include "pm/context.hpp"
#include "pm/creation/parser/functional.hpp"
#include "pm/parser.hpp"

namespace pm::parser::test {

Parser empty();
Parser nempty();

template<typename T0, typename T1 = T0>
Parser eq() {
  static Parser res =
    fparse(
  [](Stream &, Context & con) {
    return con[0].value<T0>() == con[1].value<T1>();
  }
    );
  return res;
}

template<typename T0, typename T1 = T0>
Parser neq() {
  static Parser res =
    fparse(
  [](Stream &, Context & con) {
    return con[0].value<T0>() != con[1].value<T1>();
  }
    );
  return res;
}

template<typename T0, typename T1 = T0>
Parser less() {
  static Parser res =
    fparse(
  [](Stream &, Context & con) {
    return con[0].value<T0>() < con[1].value<T1>();
  }
    );
  return res;
}

template<typename T0, typename T1 = T0>
Parser lesseq() {
  static Parser res =
    fparse(
  [](Stream &, Context & con) {
    return con[0].value<T0>() <= con[1].value<T1>();
  }
    );
  return res;
}

template<typename T0, typename T1 = T0>
Parser greater() {
  static Parser res =
    fparse(
  [](Stream &, Context & con) {
    return con[0].value<T0>() > con[1].value<T1>();
  }
    );
  return res;
}

template<typename T0, typename T1 = T0>
Parser greatereq() {
  static Parser res =
    fparse(
  [](Stream &, Context & con) {
    return con[0].value<T0>() >= con[1].value<T1>();
  }
    );
  return res;
}

template<typename T0, typename T>
Parser eq(T val) {
  return
    fparse(
  [val = std::move(val)](Stream &, Context & con) {
    return con[0].value<T0>() == val;
  }
    );
}

template<typename T0, typename T>
Parser neq(T val) {
  return
    fparse(
  [val = std::move(val)](Stream &, Context & con) {
    return con[0].value<T0>() != val;
  }
    );
}

template<typename T0, typename T>
Parser less(T val) {
  return
    fparse(
  [val = std::move(val)](Stream &, Context & con) {
    return con[0].value<T0>() < val;
  }
    );
}

template<typename T0, typename T>
Parser lesseq(T val) {
  return
    fparse(
  [val = std::move(val)](Stream &, Context & con) {
    return con[0].value<T0>() <= val;
  }
    );
}

template<typename T0, typename T>
Parser greater(T val) {
  return
    fparse(
  [val = std::move(val)](Stream &, Context & con) {
    return con[0].value<T0>() > val;
  }
    );
}

template<typename T0, typename T>
Parser greatereq(T val) {
  return
    fparse(
  [val = std::move(val)](Stream &, Context & con) {
    return con[0].value<T0>() >= val;
  }
    );
}

} // namespace pm::parser::test

#endif
