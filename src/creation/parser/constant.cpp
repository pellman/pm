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
#include "pm/creation/parser/constant.hpp"

#include "pm/devel/parser/base.hpp"

namespace pm::parser {
namespace {

class F
  : public devel::parser::Base {
public:
  bool parse(Stream &, Context &) const override {
    return false;
  }
};

class T
  : public devel::parser::Base {
public:
  bool parse(Stream &, Context &) const override {
    return true;
  }
};

} // namespace

Parser f() {
  static Parser res = new F();
  return res;
}

Parser t() {
  static Parser res = new T();
  return res;
}

} // namespace pm::parser
