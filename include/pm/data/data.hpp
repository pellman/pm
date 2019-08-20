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
#ifndef PM_DATA_DATA_HPP
#define PM_DATA_DATA_HPP

#include <memory>
//#include <utility>

#include "pm/data/utils/dbase.hpp"

namespace pm {
namespace data {

class Data {
public:
  // DEFAULTS
  Data() = default;
  Data(const Data & d);
  Data(Data && d);
  Data & operator =(const Data & d);
  Data & operator =(Data && d);
  // ALTERING METHODS
  template<typename T, typename ... Args>
  void set(Args && ... args);
  void swap(Data & d);
  void unset();
  // PRESERVING METHODS
  Data clone() const;
  // ACCESS METHODS
  bool empty() const;
  bool nonempty() const;
  template<typename T>
  T & val() const;
  // STATIC_METHODS
  template<typename T, typename ... Args>
  static Data make(Args && ... args);

private:
  // CONSTRUCTORS
  Data(utils::DBase * ptr);
  // FIELDS
  std::unique_ptr<utils::DBase> ptr_;
};


// implementation

template<typename T, typename ... Args>
void Data::set(Args && ... args) {
  ptr_.reset(new utils::DDeriv<T>(std::forward<Args>(args) ...));
}

template<typename T>
T & Data::val() const {
  return static_cast<utils::DDeriv<T> *>(ptr_.get())->value;
}

template<typename T, typename ... Args>
Data Data::make(Args && ... args) {
  return Data(new utils::DDeriv<T>(std::forward<Args>(args) ...));
}

} // namespace data
} // namespace pm

#endif
