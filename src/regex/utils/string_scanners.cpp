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
#include "pm/regex/utils/string_scanners.hpp"

//#include <cstddef>
//#include <functional>
#include <list>
//#include <string>
#include <utility>
//#include "pm/stream/stream.hpp"

namespace pm {
namespace regex {
namespace utils {

namespace {

// core
bool match_future_char(stream::Stream & is, char c) {
  char tmpc;
  while(is.get(tmpc)) {
    if(tmpc == c) {
      return true;
    }
  }
  return false;
}

bool match_future_optional_char(stream::Stream & is, char c) {
  char tmpc;
  while(is.get(tmpc)) {
    if(tmpc == c) {
      return true;
    }
  }
  return true;
}

bool match_future_str(stream::Stream & is, const std::string & s) {
  std::list<size_t> prefixes = {0};
  char c;
  while(is.get(c)) {
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

bool match_future_optional_str(stream::Stream & is, const std::string & s) {
  std::list<size_t> prefixes = {0};
  char c;
  while(is.get(c)) {
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
  return true;
}

bool match_empty_str(stream::Stream &) {
  return true;
}

} // namespace


// interface
std::function<bool(stream::Stream &)> str(std::string s) {
  return [s = std::move(s)](stream::Stream & is) -> bool {
    std::string tmps;
    return is.get(tmps, s.size()) && tmps == s;
  };
}

std::function<bool(stream::Stream &)> len(size_t size) {
  return [size](stream::Stream & is) -> bool {
    return is.advance(size);
  };
}

std::function<bool(stream::Stream &)> future(std::string s) {
  if(s.empty()) {
    return match_empty_str;
  }
  if(s.size() == 1) {
    return [c = s[0]](stream::Stream & is) -> bool {
      return match_future_char(is, c);
    };
  }
  return [s = std::move(s)](stream::Stream & is) -> bool {
    return match_future_str(is, s);
  };
}

std::function<bool(stream::Stream &)> optional_future(std::string s) {
  if(s.empty()) {
    return match_empty_str;
  }
  if(s.size() == 1) {
    return [c = s[0]](stream::Stream & is) -> bool {
      return match_future_optional_char(is, c);
    };
  }
  return [s = std::move(s)](stream::Stream & is) -> bool {
    return match_future_optional_str(is, s);
  };
}

} // namespace utils
} // namespace regex
} // namespace pm
