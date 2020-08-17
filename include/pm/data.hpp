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
#ifndef PM_DATA_HPP
#define PM_DATA_HPP

#include <memory>
#include <utility>

#include "pm/devel/data/cloner.hpp"

namespace pm {

class Data {
public:
  // = methods =
  // defaults
  Data() = default;
  Data(const Data & d);
  Data(Data && d) = default;
  Data & operator =(const Data & d);
  Data & operator =(Data && d) = default;
  // alter content
  template<typename T, typename ... Args>
  void emplace(Args && ... args);
  void swap(Data & d);
  void reset();
  // content access
  bool has_value() const;
  template<typename T>
  T & value();
  template<typename T>
  const T & value() const;
  // statics
  template<typename T, typename ... Args>
  static Data make(Args && ... args) {
    return Data(new devel::data::Cloner<T>(std::forward<Args>(args) ...));
  }
private:
  // = methods =
  // constructors
  Data(devel::data::ClonerBase * base);
  // = fields =
  std::unique_ptr<devel::data::ClonerBase> ptr_;
};

void swap(Data & d1, Data & d2);


// implementation
template<typename T, typename ... Args>
void Data::emplace(Args && ... args) {
  ptr_.reset(new devel::data::Cloner<T>(std::forward<Args>(args) ...));
}

template<typename T>
T & Data::value() {
  return static_cast<devel::data::Cloner<T> *>(ptr_.get())->val;
}

template<typename T>
const T & Data::value() const {
  return static_cast<devel::data::Cloner<T> *>(ptr_.get())->val;
}

} // namespace pm

#endif
