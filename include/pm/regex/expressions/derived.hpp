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
#ifndef PM_REGEX_EXPRESSIONS_DERIVED_HPP
#define PM_REGEX_EXPRESSIONS_DERIVED_HPP

#include <functional>
//#include <set>
#include <string>
//#include <utility>
//#include <vector>

#include "pm/regex/expressions/flow/alt.hpp"
#include "pm/regex/expressions/flow/concat.hpp"
#include "pm/regex/expressions/functional/specific.hpp"
#include "pm/regex/expressions/terminal/symbol.hpp"
//#include "pm/regex/regex.hpp"


namespace pm {
namespace regex {

// = terminal -> symbol =
template<typename ... Chars>
Regex let(Chars && ... chars) {
  return let(std::set<char> {std::forward<Chars>(chars) ...});
}

// = terminal -> string =
Regex enclose(std::string s_start, std::string s_finish);
Regex enclose_opt(std::string s_start, std::string s_finish);
Regex c_id();
Regex decimal_string();
Regex id(std::function<bool(char)> letter);
Regex id(std::function<bool(char)> head_letter, std::function<bool(char)> tail_letter);

// = terminal -> integer =
template<typename Int>
Regex decimal_digit() {
  return concat(std::vector<Regex> {decimal_letter(), char_to_decimal<Int>()});
}
template<typename Int>
Regex decimal() {
  return concat(std::vector<Regex> {decimal_string(), string_to_decimal<Int>()});
}

// = flow -> alternative =
template<typename ... Regexs>
Regex alt(Regexs && ... regexs) {
  return alt(std::vector<Regex> {std::forward<Regexs>(regexs) ...});
}
Regex operator |(Regex r1, Regex r2);
// = flow -> concatenation =
template<typename ... Regexs>
Regex concat(Regexs && ... regexs) {
  return concat(std::vector<Regex> {std::forward<Regexs>(regexs) ...});
}
Regex operator &(Regex r1, Regex r2);
// = flow -> but =
Regex operator -(Regex r1, Regex r2);
// = flow -> optional
Regex operator !(Regex r);
// = flow -> star =
Regex operator *(Regex r);
// = flow -> nodata =
Regex operator -(Regex r);
// = flow -> accumulate =
Regex operator ~(Regex r);

} // namespace regex
} // namespace pm


#endif
