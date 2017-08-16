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
#ifndef __UTILS_NUMERATION_HPP
#define __UTILS_NUMERATION_HPP

#include <cstddef>
#include <map>
#include <utility>
#include <vector>
#include "utils/container_functions.hpp"

namespace pm {
namespace utils {

template<typename Element>
class Numeration {
public:
  // ALTERING METHODS
  size_t add(const Element & el);
  size_t add(Element && el);
  void add(const Numeration<Element> & num);
  void add(Numeration<Element> && num);
  void clear();
  void remove(const Element & el);
  // ACCESS METHODS
  // = direct access =
  const Element & element_at(size_t i) const;
  bool has(const Element & el) const;
  size_t index_of(const Element & el) const;
  size_t size() const;
  // = iteration =
  typename std::vector<Element>::const_iterator begin() const;
  typename std::vector<Element>::const_iterator end() const;

private:
  // FIELDS
  std::map<Element, size_t> backward_;
  std::vector<Element> forward_;
};


// IMPLEMENTATION
template<typename Element>
size_t Numeration<Element>::add(const Element & el) {
  auto it = backward_.find(el);
  if(it != backward_.end()) {
    return it->second;
  }
  size_t res = forward_.size();
  backward_[el] = res;
  forward_.push_back(el);
  return res;
}

template<typename Element>
size_t Numeration<Element>::add(Element && el) {
  auto it = backward_.find(el);
  if(it != backward_.end()) {
    return it->second;
  }
  size_t res = forward_.size();
  backward_[el] = res;
  forward_.push_back(std::move(el));
  return res;
}

template<typename Element>
void Numeration<Element>::add(const Numeration<Element> & num) {
  for(const auto & el : num) {
    add(el);
  }
}

template<typename Element>
void Numeration<Element>::add(Numeration<Element> && num) {
  for(const auto & el : num) {
    add(std::move(el));
  }
}

template<typename Element>
void Numeration<Element>::clear() {
  forward_.clear();
  backward_.clear();
}

template<typename Element>
void Numeration<Element>::remove(const Element & el) {
  auto it = backward_.find(el);
  if(it == backward_.end()) return;
  for(auto vit = forward_.begin() + it->second + 1; vit != forward_.end(); ++vit) {
    --backward_[*vit];
  }
  erase_index(forward_, it->second);
  backward_.erase(it);
}

template<typename Element>
const Element & Numeration<Element>::element_at(size_t i) const {return forward_[i];}

template<typename Element>
bool Numeration<Element>::has(const Element & el) const {return is_in(el, backward_);}

template<typename Element>
size_t Numeration<Element>::index_of(const Element & el) const {return backward_.at(el);}

template<typename Element>
size_t Numeration<Element>::size() const {return forward_.size();}

template<typename Element>
typename std::vector<Element>::const_iterator Numeration<Element>::begin() const {return forward_.begin();}

template<typename Element>
typename std::vector<Element>::const_iterator Numeration<Element>::end() const {return forward_.end();}

} // namespace utils
} // namespace pm

#endif
