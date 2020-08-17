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
#include "pm/context.hpp"

#include <algorithm>

namespace pm {

Context::Context(const Context & con) {
  vec_.reserve(con.vec_.size());
  for(const auto & ptr : con.vec_) {
    vec_.emplace_back(new Data(*ptr));
  }
}

Context::Context(Context && con)
  : vec_(std::move(con.vec_)) {
  con.vec_.clear();
}

Context & Context::operator =(const Context & con) {
  return *this = Context(con);
}

Context & Context::operator =(Context && con) {
  vec_ = std::move(con.vec_);
  con.vec_.clear();
  return *this;
}

Context::Context(size_t max_index_hint) {
  size_t size = max_index_hint + 1;
  vec_.reserve(size);
  for(size_t i = 0; i < size; ++i) {
    vec_.emplace_back(new Data());
  }
}

Data & Context::operator [](size_t data_index) {
  enlarge_(data_index + 1);
  return *vec_[data_index];
}

const Data & Context::operator [](size_t data_index) const {
  enlarge_(data_index + 1);
  return *vec_[data_index];
}

void Context::swap(Context & con) {
  vec_.swap(con.vec_);
}

void Context::swap(const std::vector<size_t> & data_indexes, Context & con) {
  if(data_indexes.empty()) {
    return;
  }
  enlarge_(*std::max_element(data_indexes.begin(), data_indexes.end()) + 1);
  con.enlarge_(data_indexes.size());
  for(size_t i = 0; i < data_indexes.size(); ++i) {
    std::swap(vec_[data_indexes[i]], con.vec_[i]);
  }
}

void Context::clear() {
  vec_.clear();
}

void Context::enlarge_(size_t data_index) const {
  if(data_index > vec_.size()) {
    vec_.reserve(data_index);
    for(size_t i = vec_.size(); i < data_index; ++i) {
      vec_.emplace_back(new Data());
    }
  }
}

void swap(Context & con1, Context & con) {
  con1.swap(con);
}

} // namespace pm
