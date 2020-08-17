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
#include "pm/creation/char_set/composition.hpp"

#include <utility>

#include "pm/devel/char_set/base.hpp"

namespace pm::char_set {
namespace {

class SetAnd
  : public devel::char_set::Base {
public:
  SetAnd(std::vector<CharSet> css)
    : css_(std::move(css)) {}
  bool contains(char c) const override {
    for(const auto & cs : css_) {
      if(!cs.contains(c)) {
        return false;
      }
    }
    return true;
  }
private:
  const std::vector<CharSet> css_;
};

class SetOr
  : public devel::char_set::Base {
public:
  SetOr(std::vector<CharSet> css)
    : css_(std::move(css)) {}
  bool contains(char c) const override {
    for(const auto & cs : css_) {
      if(cs.contains(c)) {
        return true;
      }
    }
    return false;
  }
private:
  const std::vector<CharSet> css_;
};

class SetNot
  : public devel::char_set::Base {
public:
  SetNot(CharSet cs)
    : cs_(std::move(cs)) {}
  bool contains(char c) const override {
    return !cs_.contains(c);
  }
private:
  const CharSet cs_;
};

class SetXor
  : public devel::char_set::Base {
public:
  SetXor(std::vector<CharSet> css)
    : css_(std::move(css)) {}
  bool contains(char c) const override {
    bool res = false;
    for(const auto & cs : css_) {
      res ^= cs.contains(c);
    }
    return res;
  }
private:
  const std::vector<CharSet> css_;
};

} // namespace

CharSet land(std::vector<CharSet> css) {
  return new SetAnd{std::move(css)};
}

CharSet lor(std::vector<CharSet> css) {
  return new SetOr{std::move(css)};
}

CharSet lnot(CharSet cs) {
  return new SetNot{std::move(cs)};
}

CharSet lxor(std::vector<CharSet> css) {
  return new SetXor{std::move(css)};
}

} // namespace pm::char_set

namespace pm {

CharSet operator &(CharSet left, CharSet right) {
  return char_set::land({std::move(left), std::move(right)});
}

CharSet operator |(CharSet left, CharSet right) {
  return char_set::lor({std::move(left), std::move(right)});
}

CharSet operator !(CharSet cs) {
  return char_set::lnot(std::move(cs));
}

CharSet operator ^(CharSet left, CharSet right) {
  return char_set::lxor({std::move(left), std::move(right)});
}

} // namespace pm
