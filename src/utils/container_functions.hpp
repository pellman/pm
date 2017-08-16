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
#ifndef __UTILS_CONTAINER_FUNCTIONS_HPP
#define __UTILS_CONTAINER_FUNCTIONS_HPP

#include <cstddef>

namespace pm {
namespace utils {

template<typename Container>
void append(Container & where, const Container & who);

template<typename Container>
bool disjoint(const Container & X, const Container & Y);

template<typename Container>
void erase_index(Container & container, size_t ind);

template<typename Container>
bool intersects(const Container & X, const Container & Y);

template<typename Element, typename Container>
bool is_in(const Element & element, const Container & container);

template<typename Element, typename Container>
bool isnt_in(const Element & element, const Container & container);

template<typename Container>
void merge(Container & where, const Container & who);


// IMPLEMENTATION
template<typename Container>
void append(Container & where, const Container & who) {
  where.insert(where.end(), who.begin(), who.end());
}

template<typename Container>
bool disjoint(const Container & X, const Container & Y) {
  for(const auto & elX : X) {
    if(is_in(elX, Y)) {
      return false; // TODO effectiveness
    }
  }
  return true;
}

template<typename Container>
void erase_index(Container & container, size_t ind) {
  container.erase(container.begin() + ind);
}

template<typename Container>
bool intersects(const Container & X, const Container & Y) {
  for(const auto & elX : X) {
    if(is_in(elX, Y)) {
      return true; // TODO effectiveness
    }
  }
  return false;
}

template<typename Element, typename Container>
bool is_in(const Element & element, const Container & container) {
  return container.find(element) != container.end();
}

template<typename Element, typename Container>
bool isnt_in(const Element & element, const Container & container) {
  return container.find(element) == container.end();
}

template<typename Container>
void merge(Container & where, const Container & who) {
  where.insert(who.begin(), who.end());
}

} // namespace utils
} // namespace pm

#endif
