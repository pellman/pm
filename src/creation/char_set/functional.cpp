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
#include "pm/creation/char_set/functional.hpp"

#include <utility>

#include "pm/devel/char_set/base.hpp"

namespace pm::char_set {
namespace {

class FunctionalSet
  : public devel::char_set::Base {
public:
  FunctionalSet(std::function<bool(char)> f)
    : f_(std::move(f)) {}
  bool contains(char c) const override {
    return f_(c);
  }
private:
  const std::function<bool(char)> f_;
};

} // namespace

CharSet make(std::function<bool(char)> f) {
  return new FunctionalSet{std::move(f)};
}

} // namespace pm::char_set
