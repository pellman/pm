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
#ifndef PM_DATA_UTILS_DBASE_HPP
#define PM_DATA_UTILS_DBASE_HPP

#include <utility>

namespace pm {
namespace data {
namespace utils {

class DBase {
public:
  virtual ~DBase();
  virtual DBase * clone() const;
};

template<typename T>
class DDeriv
  : public DBase {
public:
  template<typename ... Args>
  DDeriv(Args && ... args) : value(std::forward<Args>(args) ...) {}
  DDeriv * clone() const override {
    return new DDeriv(*this);
  }
  T value;
};

} // namespace utils
} // namespace data
} // namespace pm

#endif
