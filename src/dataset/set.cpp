/*
    This file is part of the pm library package.
    Copyright (C) 2017, 2018 Vladislav Podymov
    
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
#include "pm/dataset/set.hpp"

namespace pm {
namespace dataset {

void Set::detach() {
  ptr_.detach();
  detach_all_data_();
}

void Set::detach_receive(const Set & set) {
  ptr_.receive(set.ptr_);
  detach_all_data_();
}

void Set::receive(const Set & set) const {
  resize_(set.ptr_.val().size());
  const auto & thisv = ptr_.val();
  const auto & setv = set.ptr_.val();
  for(auto thisit = thisv.begin(), setit = setv.begin(); thisit != thisv.end(); ++thisit, ++setit) {
    thisit->receive(*setit);
  }
}

Set Set::clone() const {
  Set res = *this;
  res.detach();
  return res;
}

const type_abuse::DPtr & Set::ptr(size_t i) const {
  if(ptr_.val().size() <= i) resize_(i+1);
  return ptr_.val()[i];
}

void Set::detach_all_data_() const {
  for(auto & d : ptr_.val()) {
    d.detach();
  }
}

void Set::resize_(size_t size) const {
  auto & v = ptr_.val();
  if(v.size() > size) {
    v.resize(size);
  }
  else {
    for(size_t i = v.size(); i < size; ++i) {
      v.push_back(type_abuse::DPtr());
    }
  }
}

} // namespace dataset
} // namespace pm
