/*
    This file is part of the pm library package.
    Copyright (C) 2017 Vladislav Podymov
    
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
#include "regexp/basic/enclose.hpp"

namespace pm {
namespace regexp {

bool Enclose::match_full(stream::Stream & stream, Context & context) const {
  if(opening_string_.empty() && closing_string_.empty()) {
    return true;
  }
  int status = 0; // 0 -> undefined; 1 -> accept; -1 -> reject
  std::string s_popped;
  if(!opening_string_.empty() &&
      (!stream.get_strict(s_popped, opening_string_.size()) || s_popped != opening_string_)) {
    status = -1;
  }
  if(status == 0 && closing_string_.empty()) {
    status = 1;
  }
  if(status == 0) {
    status = (closing_string_.size() == 1)
             ? close_char_(stream, s_popped)
             : close_string_(stream, s_popped);
  }
  if(status == 1) {
    if(context.asc.is_active()) {
      context.string() += s_popped;
    }
    if(context.adc.is_active()) {
      context.adc.dc.set<std::string>(s_popped);
    }
    return true;
  }
  else { // status == -1
    stream.unget(s_popped);
    return false;
  }
}

int Enclose::close_char_(stream::Stream & stream, std::string & s_popped) const {
  const char c_desired = closing_string_.front();
  char c_popped;
  while(stream.get(c_popped)) {
    s_popped += c_popped;
    if(c_popped == c_desired) {
      return 1;
    }
  }
  return -1;
}

int Enclose::close_string_(stream::Stream & stream, std::string & s_popped) const {
  char c;
  std::list<size_t> matched_prefix_sizes;
  while(stream.get(c)) {
    s_popped += c;
    if(push_char_to_prefixes_(c, matched_prefix_sizes)) {
      return 1;
    }
  }
  return -1;
}

bool Enclose::push_char_to_prefixes_(char c, std::list<size_t> & matched_prefix_sizes) const {
  if(!matched_prefix_sizes.empty()) {
    auto it = matched_prefix_sizes.begin();
    if(c == closing_string_[*it]) {
      ++*it;
      if(*it == closing_string_.size()) {
        return true;
      }
      ++it;
    }
    else {
      matched_prefix_sizes.pop_front();
      it = matched_prefix_sizes.begin();
    }
    while(it != matched_prefix_sizes.end()) {
      if(c == closing_string_[*it]) {
        ++*it;
        ++it;
      }
      else {
        it = matched_prefix_sizes.erase(it);
      }
    }
  }
  if(c == closing_string_.front()) {
    matched_prefix_sizes.push_back(1);
  }
  return false;
}

} // namespace regexp
} // namespace pm
