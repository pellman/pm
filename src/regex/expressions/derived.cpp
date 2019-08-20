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
#include "pm/regex/expressions/derived.hpp"

//#include <functional>
//#include <set>
//#include <string>
//#include <utility>
//#include <vector>

#include "pm/regex/expressions/flow/accumulate.hpp"
//#include "pm/regex/expressions/flow/alt.hpp"
#include "pm/regex/expressions/flow/but.hpp"
//#include "pm/regex/expressions/flow/concat.hpp"
#include "pm/regex/expressions/flow/nodata.hpp"
#include "pm/regex/expressions/flow/opt.hpp"
#include "pm/regex/expressions/flow/star.hpp"
#include "pm/regex/expressions/flow/str.hpp"
//#include "pm/regex/expressions/functional/specific.hpp"
#include "pm/regex/expressions/terminal/string.hpp"
//#include "pm/regex/expressions/terminal/symbol.hpp"
#include "pm/regex/expressions/terminal/universal.hpp"
//#include "pm/regex/regex.hpp"
#include "pm/regex/utils/symbol_checkers.hpp"


namespace pm {
namespace regex {

// = flow operators =
Regex operator |(Regex r1, Regex r2) {
  return alt(std::vector<Regex> {std::move(r1), std::move(r2)});
}
Regex operator -(Regex r1, Regex r2) {
  return but(std::move(r1), std::move(r2));
}
Regex operator &(Regex r1, Regex r2) {
  return concat(std::vector<Regex> {std::move(r1), std::move(r2)});
}
Regex operator -(Regex r) {
  return nodata(std::move(r));
}
Regex operator ~(Regex r) {
  return accumulate(std::move(r));
}
Regex operator !(Regex r) {
  return opt(std::move(r));
}
Regex operator *(Regex r) {
  return star(std::move(r));
}

// = terminal -> string =
Regex enclose(std::string s_start, std::string s_finish) {
  return str(str(std::move(s_start)) & future_str(std::move(s_finish)));
}

Regex enclose_opt(std::string s_start, std::string s_finish) {
  return str(str(std::move(s_start)) & future_opt_str(std::move(s_finish)));
}

Regex c_id() {
  return id(utils::c_id_head_letter, utils::c_id_tail_letter);
}

Regex decimal_string() {
  return id(utils::decimal_letter);
}

Regex id(std::function<bool(char)> letter) {
  auto letter_copy = letter;
  return id(std::move(letter), std::move(letter_copy));
}

Regex id(std::function<bool(char)> head_letter, std::function<bool(char)> tail_letter) {
  return str(symbol(std::move(head_letter)) & *symbol(std::move(tail_letter)));
}


Regex operator |(Regex r, char c) {
  return std::move(r) | let(c);
}
Regex operator |(char c, Regex r) {
  return let(c) | std::move(r);
}
Regex operator &(Regex r, char c) {
  return std::move(r) & let(c);
}
Regex operator &(char c, Regex r) {
  return let(c) & std::move(r);
}
Regex operator -(Regex r, char c) {
  return std::move(r) - let(c);
}
Regex operator -(char c, Regex r) {
  return let(c) - std::move(r);
}
Regex operator |(Regex r, std::set<char> s) {
  return std::move(r) | let(std::move(s));
}
Regex operator |(std::set<char> s, Regex r) {
  return let(std::move(s)) | std::move(r);
}
Regex operator &(Regex r, std::set<char> s) {
  return std::move(r) & let(std::move(s));
}
Regex operator &(std::set<char> s, Regex r) {
  return let(std::move(s)) & std::move(r);
}
Regex operator -(Regex r, std::set<char> s) {
  return std::move(r) - let(std::move(s));
}
Regex operator -(std::set<char> s, Regex r) {
  return let(std::move(s)) - std::move(r);
}
Regex operator |(Regex r, std::string s) {
  return std::move(r) | str(std::move(s));
}
Regex operator |(std::string s, Regex r) {
  return str(std::move(s)) | std::move(r);
}
Regex operator &(Regex r, std::string s) {
  return std::move(r) & str(std::move(s));
}
Regex operator &(std::string s, Regex r) {
  return str(std::move(s)) & std::move(r);
}
Regex operator -(Regex r, std::string s) {
  return std::move(r) - str(std::move(s));
}
Regex operator -(std::string s, Regex r) {
  return str(std::move(s)) - std::move(r);
}

} // namespace regex
} // namespace pm
