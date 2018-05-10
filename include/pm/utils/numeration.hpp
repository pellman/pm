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
#ifndef __PM_UTILS_NUMERATION_HPP
#define __PM_UTILS_NUMERATION_HPP

#include <cstddef>
#include <map>
#include <utility>
#include <vector>
#include "pm/utils/container_functions.hpp"

namespace pm {
namespace utils {

template<typename T>
class Numeration {
public:
  // TYPES
  class Iterator {
  public:
    Iterator & operator ++() {++it; return *this;}
    Iterator operator ++(int) {Iterator res; ++it; return res;}
    Iterator & operator --() {--it; return *this;}
    Iterator operator --(int) {Iterator res; --it; return res;}
    bool operator ==(const Iterator & i) const {return it == i.it;}
    bool operator !=(const Iterator & i) const {return it != i.it;}
    const T & operator *() {return (*it)->first;}
    typename std::vector<typename std::map<T, size_t>::const_iterator>::const_iterator it;
  };
  // OPERATORS
  const T & operator [](size_t i) const;
  // ALTERING METHODS
  void clear();
  void erase(const T & el);
  size_t insert(const T & el);
  size_t insert(T && el);
  // ACCESS METHODS
  // = direct access =
  const T & at(size_t i) const;
  size_t find(const T & el) const;
  bool has(const T & el) const;
  size_t size() const;
  // = iteration =
  Iterator begin() const;
  Iterator end() const;

private:
  // FIELDS
  std::map<T, size_t> forward_;
  typename std::vector<typename std::map<T, size_t>::const_iterator> backward_;
};


// implementation
template<typename T>
const T & Numeration<T>::operator [](size_t i) const {return backward_[i]->first;}

template<typename T>
void Numeration<T>::clear() {
  forward_.clear();
  backward_.clear();
}

template<typename T>
void Numeration<T>::erase(const T & el) {
  auto it = forward_.find(el);
  if(it == forward_.end()) return;
  for(auto vit = backward_.begin() + it->second + 1; vit != backward_.end(); ++vit) {
    --forward_[*vit];
  }
  erase_index(backward_, it->second);
  forward_.erase(it);
}

template<typename T>
size_t Numeration<T>::insert(const T & el) {
  auto it = forward_.find(el);
  if(it != forward_.end()) {
    return it->second;
  }
  size_t res = backward_.size();
  backward_.push_back(forward_.insert(it, {el, res}));
  return res;
}

template<typename T>
size_t Numeration<T>::insert(T && el) {
  auto it = forward_.find(el);
  if(it != forward_.end()) {
    return it->second;
  }
  size_t res = backward_.size();
  backward_.push_back(forward_.insert(it, {std::move(el), res}));
  return res;
}

template<typename T>
const T & Numeration<T>::at(size_t i) const {return backward_.at(i)->first;}

template<typename T>
size_t Numeration<T>::find(const T & el) const {return forward_.at(el);}

template<typename T>
bool Numeration<T>::has(const T & el) const {return is_in(el, forward_);}

template<typename T>
size_t Numeration<T>::size() const {return backward_.size();}

template<typename T>
typename Numeration<T>::Iterator Numeration<T>::begin() const {return {backward_.begin()};}

template<typename T>
typename Numeration<T>::Iterator Numeration<T>::end() const {return {backward_.end()};}

} // namespace utils
} // namespace pm

#endif
