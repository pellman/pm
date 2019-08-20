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
#include "pm/set/domain.hpp"

//#include <cstddef>
//#include <map>
//#include <string>
//#include <vector>
#include <utility>

namespace pm {
namespace set {

Domain::Iterator & Domain::Iterator::operator ++() {
  ++it_;
  return *this;
}

Domain::Iterator Domain::Iterator::operator ++(int) {
  return {it_++};
}

Domain::Iterator & Domain::Iterator::operator --() {
  --it_;
  return *this;
}

Domain::Iterator Domain::Iterator::operator --(int) {
  return {it_--};
}

bool Domain::Iterator::operator ==(const Domain::Iterator & it) const {
  return it_ == it.it_;
}

bool Domain::Iterator::operator !=(const Domain::Iterator & it) const {
  return it_ != it.it_;
}

bool Domain::Iterator::operator >(const Domain::Iterator & it) const {
  return it_ > it.it_;
}

bool Domain::Iterator::operator >=(const Domain::Iterator & it) const {
  return it_ >= it.it_;
}

bool Domain::Iterator::operator <(const Domain::Iterator & it) const {
  return it_ < it.it_;
}

bool Domain::Iterator::operator <=(const Domain::Iterator & it) const {
  return it_ <= it.it_;
}

const std::string & Domain::Iterator::operator *() const {
  return (*it_)->first;
}

Domain::Domain(const Domain & dom)
  : forward_(dom.forward_),
    backward_(forward_.size()) {
  renew_iterators_();
}

Domain & Domain::operator =(const Domain & dom) {
  forward_ = dom.forward_;
  backward_.resize(forward_.size());
  renew_iterators_();
  return *this;
}

Domain & Domain::operator =(Domain && dom) {
  forward_ = std::move(dom.forward_);
  backward_.resize(forward_.size());
  renew_iterators_();
  return *this;
}

const std::string & Domain::operator [](size_t index) const {
  return backward_[index]->first;
}

size_t Domain::operator [](const std::string & name) const {
  return forward_.at(name);
}

size_t Domain::add(const std::string & name) {
  auto insert_res = forward_.insert({name, backward_.size()});
  if(insert_res.second) {
    backward_.push_back(insert_res.first);
  }
  return insert_res.first->second;
}

size_t Domain::add(std::string && name) {
  auto insert_res = forward_.insert({std::move(name), backward_.size()});
  if(insert_res.second) {
    backward_.push_back(insert_res.first);
  }
  return insert_res.first->second;
}

void Domain::clear() {
  forward_.clear();
  backward_.clear();
}

void Domain::erase(size_t index) {
  if(index >= backward_.size()) {
    return;
  }
  forward_.erase(backward_[index]);
  auto it = backward_.begin() + static_cast<ptrdiff_t>(index);
  it = backward_.erase(it);
  while(it != backward_.end()) {
    --(*it)->second;
    ++it;
  }
  // TODO m.b. increase safety in conversion to signed
}

void Domain::erase(const std::string & name) {
  const auto it = forward_.find(name);
  if(it == forward_.end()) {
    return;
  }
  auto itb = backward_.begin() + static_cast<ptrdiff_t>(it->second);
  forward_.erase(it);
  itb = backward_.erase(itb);
  while(itb != backward_.end()) {
    --(*itb)->second;
    ++itb;
  }
  // TODO m.b. increase safety in conversion to signed
}

Domain::Iterator Domain::begin() const {
  return {backward_.begin()};
}

bool Domain::contains(const std::string & name) const {
  return forward_.find(name) != forward_.end();
}

bool Domain::empty() const {
  return backward_.empty();
}

Domain::Iterator Domain::end() const {
  return {backward_.end()};
}

size_t Domain::size() const {
  return backward_.size();
}

size_t Domain::index(const std::string & name) const {
  return forward_.at(name);
}

const std::string & Domain::name(size_t index) const {
  return backward_[index]->first;
}

void Domain::renew_iterators_() {
  for(std::map<std::string, size_t>::iterator it = forward_.begin(); it != forward_.end(); ++it) {
    backward_[it->second] = it;
  }
}

} // namespace set
} // namespace pm
