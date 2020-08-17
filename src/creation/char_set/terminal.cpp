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
#include "pm/creation/char_set/terminal.hpp"

#include <utility>

#include "pm/devel/char_set/base.hpp"

namespace pm::char_set {
namespace {

class Singleton
  : public devel::char_set::Base {
public:
  Singleton(char c)
    : c_(c) {}
  bool contains(char c) const override {
    return c == c_;
  }
private:
  const char c_;
};

class Set
  : public devel::char_set::Base {
public:
  Set(std::set<char> cs)
    : cs_(std::move(cs)) {}
  bool contains(char c) const override {
    return cs_.find(c) != cs_.end();
  }
private:
  const std::set<char> cs_;
};

class Range
  : public devel::char_set::Base {
public:
  Range(char bottom, char top)
    : bottom_(bottom),
      top_(top) {}
  bool contains(char c) const override {
    return bottom_ <= c && c <= top_;
  }
private:
  const char bottom_, top_;
};

class Total
  : public devel::char_set::Base {
public:
  bool contains(char) const override {
    return true;
  }
};

class Empty
  : public devel::char_set::Base {
public:
  bool contains(char) const override {
    return false;
  }
};


} // namespace


CharSet make(char c) {
  return new Singleton{c};
}

CharSet make(std::set<char> cs) {
  return new Set{std::move(cs)};
}

CharSet range(char bottom, char top) {
  return new Range{bottom, top};
}

CharSet total() {
  static CharSet res = new Total();
  return res;
}

CharSet empty() {
  static CharSet res = new Empty();
  return res;
}

} // namespace pm::char_set
