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
#ifndef PM_CREATION_PARSER_GENERATOR_CONVERSION_HPP
#define PM_CREATION_PARSER_GENERATOR_CONVERSION_HPP

#include <string>
#include <utility>

#include "pm/creation/parser/functional.hpp"
#include "pm/parser.hpp"

namespace pm::parser::generator {

Parser char_to_string();

template<typename Int>
Parser string_to_decimal() {
  static Parser res =
    fexecute(
  [](Stream &, Context & con) {
    std::string s = std::move(con[0].value<std::string>());
    Int res = 0;
    for(char c : s) {
      res = res * 10 + (c - '0');
    }
    con[0].emplace<Int>(std::move(res));
  }
    );
  return res;
}

template<typename Int>
Parser char_to_decimal() {
  static Parser res =
    fexecute(
  [](Stream &, Context & con) {
    con[0].emplace<Int>(con[0].value<char>() - '0');
  }
    );
  return res;
}

template<typename TSource, typename TTarget>
Parser convert() {
  static Parser res =
    fexecute(
  [](Stream &, Context & con) {
    con[0].emplace<TTarget>(std::move(con[0].value<TSource>()));
  }
    );
  return res;
}

} // namespace pm::parser::generator

#endif
