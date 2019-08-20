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
#ifndef PM_UTILITY_GENERAL_FUNCTIONS_HPP
#define PM_UTILITY_GENERAL_FUNCTIONS_HPP

#include <functional>
#include <utility>

namespace pm {
namespace utility {

// binary arithmetics
template<typename Left, typename Right>
void add(Left & left, const Right & right) {
  left += right;
}
template<typename Left, typename Right>
void div(Left & left, const Right & right) {
  left /= right;
}
template<typename Left, typename Right>
void mod(Left & left, const Right & right) {
  left %= right;
}
template<typename Left, typename Right>
void mul(Left & left, const Right & right) {
  left *= right;
}
template<typename Left, typename Right>
void sub(Left & left, const Right & right) {
  left -= right;
}

// unary arithmetics
template<typename Left, typename Right>
std::function<void(Left &)> addc(Right val) {
  return std::bind(add<Left, Right>, std::placeholders::_1, std::move(val));
}
template<typename Left, typename Right>
std::function<void(Left &)> divc(Right val) {
  return std::bind(div<Left, Right>, std::placeholders::_1, std::move(val));
}
template<typename Left, typename Right>
std::function<void(Left &)> modc(Right val) {
  return std::bind(mod<Left, Right>, std::placeholders::_1, std::move(val));
}
template<typename Left, typename Right>
std::function<void(Left &)> mulc(Right val) {
  return std::bind(mul<Left, Right>, std::placeholders::_1, std::move(val));
}
template<typename Left, typename Right>
std::function<void(Left &)> subc(Right val) {
  return std::bind(sub<Left, Right>, std::placeholders::_1, std::move(val));
}

// other (coversion, creation)
template<typename Int>
Int char_to_decimal(char c) {
  return c - '0';
}
inline std::string char_to_string(char c) {
  return {c};
}
template<typename Int>
Int string_to_decimal(const std::string & s) {
  Int res = 0;
  for(char c : s) {
    res = res * 10 + (c - '0');
  }
  return res;
}

template<typename T, typename ... Args>
class Creator {
public:
  Creator(Args && ... args) : obj(std::forward<Args>(args) ...) {}
  T operator ()() {
    return obj;
  }
  T obj;
};

template<typename To, typename ... Args>
std::function<To()> create(Args && ... args) {
  return Creator<To, Args ...>(std::forward<Args>(args) ...);
}

} // namespace utility
} // namespace pm

#endif
