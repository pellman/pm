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
#ifndef PM_REGEX_EXPRESSIONS_FUNCTIONAL_SPECIFIC_HPP
#define PM_REGEX_EXPRESSIONS_FUNCTIONAL_SPECIFIC_HPP

//#include <utility>
#include "pm/data/utils/functions.hpp"
#include "pm/utility/general_functions.hpp"

#include "pm/regex/expressions/functional/general.hpp"
//#include "pm/regex/expressions/functional/universal.hpp"
//#include "pm/regex/regex.hpp"

namespace pm {
namespace regex {

// untyped data manipulation
inline Regex equalize(Target t = cur) {
  return pm::regex::fun(data::utils::equalize, t, complement(t));
}
inline Regex swap() {
  return pm::regex::fun(data::utils::swap, cur, acc);
}
inline Regex unset(Target t = cur) {
  return pm::regex::fun(data::utils::unset, t);
}

// binary arithmetics
template<typename Left, typename Right = Left>
Regex add(Target t_left = cur) {
  return ref(utility::add<Left, Right>, t_left, complement(t_left));
}
template<typename Left, typename Right = Left>
Regex div(Target t_left = cur) {
  return ref(utility::div<Left, Right>, t_left, complement(t_left));
}
template<typename Left, typename Right = Left>
Regex mod(Target t_left = cur) {
  return ref(utility::mod<Left, Right>, t_left, complement(t_left));
}
template<typename Left, typename Right = Left>
Regex mul(Target t_left = cur) {
  return ref(utility::mul<Left, Right>, t_left, complement(t_left));
}
template<typename Left, typename Right = Left>
Regex sub(Target t_left = cur) {
  return ref(utility::sub<Left, Right>, t_left, complement(t_left));
}

// unary arithmetics
template<typename Left, typename Right>
Regex addc(Right val, Target t = cur) {
  return uref(utility::addc<Left>(std::move(val)), t);
}
template<typename Left, typename Right>
Regex divc(Right val, Target t = cur) {
  return uref(utility::divc<Left>(std::move(val)), t);
}
template<typename Left, typename Right>
Regex modc(Right val, Target t = cur) {
  return uref(utility::modc<Left>(std::move(val)), t);
}
template<typename Left, typename Right>
Regex mulc(Right val, Target t = cur) {
  return uref(utility::mulc<Left>(std::move(val)), t);
}
template<typename Left, typename Right>
Regex subc(Right val, Target t = cur) {
  return uref(utility::subc<Left>(std::move(val)), t);
}

// type changing
template<typename Int>
Regex char_to_decimal(Target t = cur) {
  return ren(utility::char_to_decimal<Int>, t);
}
template<typename Int>
Regex string_to_decimal(Target t = cur) {
  return ren(utility::string_to_decimal<Int>, t);
}
inline Regex char_to_string(Target t = cur) {
  return ren(utility::char_to_string, t);
}
template<typename T>
Regex create(T val, Target t = cur) {
  return uret(utility::create<T>(std::move(val)), t);
}
template<typename To, typename From>
Regex convert(Target t = cur) {
  return pm::regex::fun(data::utils::convert<To, From>, t);
}

} // namespace regex
} // namespace pm

#endif
