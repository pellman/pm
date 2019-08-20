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
#ifndef PM_SET_DEFINITIONS_SPECIFIC_HPP
#define PM_SET_DEFINITIONS_SPECIFIC_HPP

//#include <string>
//#include <utility>
#include "pm/data/utils/functions.hpp"
#include "pm/utility/general_functions.hpp"

//#include "pm/set/definition.hpp"
#include "pm/set/definitions/general.hpp"
//#include "pm/set/definitions/universal.hpp"

namespace pm {
namespace set {

// untyped functions
inline Definition equalize(std::string name_target, std::string name_source) {
  return fun(data::utils::equalize, std::move(name_target), std::move(name_source));
}
inline Definition swap(std::string name1, std::string name2) {
  return fun(data::utils::swap, std::move(name1), std::move(name2));
}
inline Definition unset(std::string name) {
  return fun(data::utils::unset, std::move(name));
}

// binary arithmetics
template<typename Left, typename Right = Left>
Definition add(std::string name_left, std::string name_right) {
  return ref(utility::add<Left, Right>, std::move(name_left), std::move(name_right));
}
template<typename Left, typename Right = Left>
Definition div(std::string name_left, std::string name_right) {
  return ref(utility::div<Left, Right>, std::move(name_left), std::move(name_right));
}
template<typename Left, typename Right = Left>
Definition mod(std::string name_left, std::string name_right) {
  return ref(utility::mod<Left, Right>, std::move(name_left), std::move(name_right));
}
template<typename Left, typename Right = Left>
Definition mul(std::string name_left, std::string name_right) {
  return ref(utility::mul<Left, Right>, std::move(name_left), std::move(name_right));
}
template<typename Left, typename Right = Left>
Definition sub(std::string name_left, std::string name_right) {
  return ref(utility::sub<Left, Right>, std::move(name_left), std::move(name_right));
}

// unary arithmetics
template<typename Left, typename Right>
Definition addc(std::string name, Right val) {
  return uref(utility::addc<Left>(std::move(val)), std::move(name));
}
template<typename Left, typename Right>
Definition divc(std::string name, Right val) {
  return uref(utility::divc<Left>(std::move(val)), std::move(name));
}
template<typename Left, typename Right>
Definition modc(std::string name, Right val) {
  return uref(utility::modc<Left>(std::move(val)), std::move(name));
}
template<typename Left, typename Right>
Definition mulc(std::string name, Right val) {
  return uref(utility::mulc<Left>(std::move(val)), std::move(name));
}
template<typename Left, typename Right>
Definition subc(std::string name, Right val) {
  return uref(utility::subc<Left>(std::move(val)), std::move(name));
}

// type changing functions
template<typename Int>
Definition char_to_decimal(std::string name) {
  return ren(utility::char_to_decimal<Int>, std::move(name));
}
inline Definition char_to_string(std::string name) {
  return ren(utility::char_to_string, std::move(name));
}
template<typename To, typename From>
Definition convert(std::string name) {
  return fun(data::utils::convert<To, From>, std::move(name));
}
template<typename T>
Definition create(std::string name, T val) {
  return uret(utility::create<T>(std::move(val)), std::move(name));
}
template<typename Int>
Definition string_to_decimal(std::string name) {
  return ren(utility::string_to_decimal<Int>, std::move(name));
}

} // namespace set
} // namespace pm

#endif
