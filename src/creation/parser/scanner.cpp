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
#include "pm/creation/parser/scanner.hpp"

#include <utility>

#include "pm/creation/char_set/specific.hpp"
#include "pm/creation/parser/composition.hpp"
#include "pm/creation/parser/functional.hpp"

namespace pm::parser::scanner {

Parser end() {
  static Parser res =
    fparse(
  [](Stream & is, Context &) {
    return is.empty();
  }
    );
  return res;
}
Parser make(std::string s) {
  return
    fparse(
  [s = std::move(s)](Stream & is, Context &) {
    const auto get_res = is.try_get(s.size());
    return get_res.has_value() && get_res.value() == s;
  }
    );
}
Parser make(size_t size) {
  return
    fparse(
  [size](Stream & is, Context &) {
    return is.try_advance(size);
  }
    );
}
Parser id(CharSet head, CharSet tail) {
  return
    fparse(
  [head = std::move(head), tail = std::move(tail)](Stream & is, Context &) {
    auto get_res = is.try_get();
    if(!get_res.has_value() || !head.contains(get_res.value())) {
      return false;
    }
    while((get_res = is.try_peek()).has_value() && tail.contains(get_res.value())) {
      is.try_advance();
    }
    return true;
  }
    );
}
Parser id(CharSet cs) {
  CharSet cs_copy = cs;
  return id(std::move(cs), std::move(cs_copy));
}
Parser c_id() {
  static Parser res = id(char_set::c_id::head(), char_set::c_id::tail());
  return res;
}
Parser decimal() {
  static Parser res = id(char_set::decimal());
  return res;
}

} // namespace pm::parser::scanner

namespace pm::parser::scanner::suffix {

namespace {

bool scan_for_suffix(Stream & is, const std::string & s) {
  std::list<size_t> prefixes = {0};
  for(auto get_res = is.try_get(); get_res.has_value(); get_res = is.try_get()) {
    const char c = get_res.value();
    auto it = prefixes.begin();
    if(s[*it] == c) {
      ++*it;
      if(*it == s.size()) {
        return true;
      }
      ++it;
    }
    else {
      it = prefixes.erase(it);
    }
    while(it != prefixes.end()) {
      if(s[*it] == c) {
        ++*it;
        ++it;
      }
      else {
        it = prefixes.erase(it);
      }
    }
    prefixes.push_back(0);
  }
  return false;
}

} // namespace

Parser strong(std::string s) {
  return
    fparse(
  [s = std::move(s)](Stream & is, Context &) {
    return scan_for_suffix(is, s);
  }
    );
}
Parser weak(std::string s) {
  return
    fparse(
  [s = std::move(s)](Stream & is, Context &) {
    scan_for_suffix(is, s);
    return true;
  }
    );
}

} // namespace pm::parser::scanner::suffix

namespace pm::parser::scanner::comment {

Parser strong(std::string open, std::string close) {
  return make(std::move(open)) & suffix::strong(std::move(close));
}
Parser weak(std::string open, std::string close) {
  return make(std::move(open)) & suffix::weak(std::move(close));
}

} // namespace pm::parser::comment
