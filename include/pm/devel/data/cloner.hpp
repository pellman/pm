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
#ifndef PM_DEVEL_DATA_CLONER_HPP
#define PM_DEVEL_DATA_CLONER_HPP

#include <stdexcept>
#include <type_traits>
#include <utility>

namespace pm::devel::data {

class ClonerBase {
public:
  virtual ~ClonerBase();
  virtual ClonerBase * clone() const = 0;
};

template<typename T, bool = std::is_copy_constructible<T>::value>
class Cloner
  : public ClonerBase {
public:
  template<typename ... Args>
  Cloner(Args && ... args)
    : val(std::forward<Args>(args) ...) {}
  Cloner * clone() const override {
    return new Cloner(*this);
  }
  T val;
};

template<typename T>
class Cloner<T, false>
  : public ClonerBase {
public:
  template<typename ... Args>
  Cloner(Args && ... args)
    : val(std::forward<Args>(args) ...) {}
  Cloner * clone() const override {
    throw std::runtime_error("Trying to copy non-copyable object contained in Data");
  }
  T val;
};

} // namespace pm::devel::data

#endif
