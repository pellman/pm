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

template<typename Element>
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
    const Element & operator *() {return (*it)->first;}
    typename std::vector<typename std::map<Element, size_t>::const_iterator>::const_iterator it;
  };
  // ALTERING METHODS
  size_t add(const Element & el);
  size_t add(Element && el);
  void clear();
  void remove(const Element & el);
  // ACCESS METHODS
  // = direct access =
  const Element & element_at(size_t i) const;
  bool has(const Element & el) const;
  size_t index_of(const Element & el) const;
  size_t size() const;
  // = iteration =
  Iterator begin() const;
  Iterator end() const;

private:
  // FIELDS
  std::map<Element, size_t> forward_;
  typename std::vector<typename std::map<Element, size_t>::const_iterator> backward_;
};


// implementation
template<typename Element>
size_t Numeration<Element>::add(const Element & el) {
  auto it = forward_.find(el);
  if(it != forward_.end()) {
    return it->second;
  }
  size_t res = backward_.size();
  backward_.push_back(forward_.insert(it, {el, res}));
  return res;
}

template<typename Element>
size_t Numeration<Element>::add(Element && el) {
  auto it = forward_.find(el);
  if(it != forward_.end()) {
    return it->second;
  }
  size_t res = backward_.size();
  backward_.push_back(forward_.insert(it, {std::move(el), res}));
  return res;
}

template<typename Element>
void Numeration<Element>::clear() {
  forward_.clear();
  backward_.clear();
}

template<typename Element>
void Numeration<Element>::remove(const Element & el) {
  auto it = forward_.find(el);
  if(it == forward_.end()) return;
  for(auto vit = backward_.begin() + it->second + 1; vit != backward_.end(); ++vit) {
    --forward_[*vit];
  }
  erase_index(backward_, it->second);
  forward_.erase(it);
}

template<typename Element>
const Element & Numeration<Element>::element_at(size_t i) const {return backward_[i]->first;}

template<typename Element>
bool Numeration<Element>::has(const Element & el) const {return is_in(el, forward_);}

template<typename Element>
size_t Numeration<Element>::index_of(const Element & el) const {return forward_.at(el);}

template<typename Element>
size_t Numeration<Element>::size() const {return backward_.size();}

template<typename Element>
typename Numeration<Element>::Iterator Numeration<Element>::begin() const {return {backward_.begin()};}

template<typename Element>
typename Numeration<Element>::Iterator Numeration<Element>::end() const {return {backward_.end()};}

} // namespace utils
} // namespace pm

#endif
