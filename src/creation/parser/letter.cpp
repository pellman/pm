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
#include "pm/creation/parser/letter.hpp"

#include <utility>

#include "pm/char_set.hpp"
#include "pm/creation/char_set/specific.hpp"
#include "pm/creation/char_set/terminal.hpp"
#include "pm/devel/parser/base.hpp"

namespace pm::parser::letter {

namespace {

class ParserCharSet
  : public devel::parser::Base {
public:
  ParserCharSet(CharSet cs)
    : cs_(std::move(cs)) {}
  bool parse(Stream & is, Context & con) const override {
    Stream is_backup = is;
    auto cget = is.try_get();
    if(cget.has_value()) {
      if(cs_.contains(cget.value())) {
        con[0].emplace<char>(cget.value());
        return true;
      }
      is = std::move(is_backup);
    }
    return false;
  }
private:
  CharSet cs_;
};

} // namespace

Parser make(char c) {
  return new ParserCharSet(char_set::make(c));
}
Parser make(std::set<char> cs) {
  return new ParserCharSet(char_set::make(std::move(cs)));
}
Parser make(CharSet cs) {
  return new ParserCharSet(std::move(cs));
}
Parser range(char bottom, char top) {
  return new ParserCharSet(char_set::range(bottom, top));
}
Parser total() {
  static Parser res = new ParserCharSet(char_set::total());
  return res;
}
Parser decimal() {
  static Parser res = new ParserCharSet(char_set::decimal());
  return res;
}
Parser underscore() {
  static Parser res = new ParserCharSet(char_set::underscore());
  return res;
}

} // namespace pm::parser::letter

namespace pm::parser::letter::latin {

Parser lowercase() {
  static Parser res = new ParserCharSet(char_set::latin::lowercase());
  return res;
}
Parser uppercase() {
  static Parser res = new ParserCharSet(char_set::latin::uppercase());
  return res;
}
Parser any() {
  static Parser res = new ParserCharSet(char_set::latin::any());
  return res;
}

} // namespace pm::parser::letter::latin

namespace pm::parser::letter::c_id {

Parser head() {
  static Parser res = new ParserCharSet(char_set::c_id::head());
  return res;
}
Parser tail() {
  static Parser res = new ParserCharSet(char_set::c_id::tail());
  return res;
}

} // namespace pm::parser::letter::c_id
