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
#include "dataset/set.hpp"

namespace pm {
namespace dataset {

Set::Set(size_t size) {
  v_.reserve(size);
  for(size_t i = 0; i < size; ++i) {
    v_.push_back(type_abuse::DRef());
  }
}

void Set::detach() {
  for(auto & data : v_) {
    data.detach();
  }
}

void Set::detach_receive(const Set & set) {
  for(size_t i = 0; i < v_.size(); ++i) {
    v_[i].detach_receive(set.v_[i]);
  }
}

void Set::detach_unset() {
  for(auto & data : v_) {
    data.detach_unset();
  }
}

void Set::receive(const Set & set) const {
  for(size_t i = 0; i < v_.size(); ++i) {
    v_[i].receive(set.v_[i]);
  }
}

void Set::unset() const {
  for(const auto & data : v_) {
    data.unset();
  }
}

Set Set::clone() const {
  Set res(0);
  res.v_.reserve(v_.size());
  for(const auto & data : v_) {
    res.v_.push_back(data.clone());
  }
  return res;
}

void Set::send(const Set & set) const {
  for(size_t i = 0; i < v_.size(); ++i) {
    v_[i].send(set.v_[i]);
  }
}

} // namespace dataset
} // namespace pm
