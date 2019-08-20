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
#ifndef PM_SET_DOMAIN_HPP
#define PM_SET_DOMAIN_HPP

#include <cstddef>
#include <map>
#include <string>
#include <vector>

namespace pm {
namespace set {

class Domain {
public:
  // TYPES
  class Iterator {
  public:
    Iterator & operator ++();
    Iterator operator ++(int);
    Iterator & operator --();
    Iterator operator --(int);
    bool operator ==(const Iterator & it) const;
    bool operator !=(const Iterator & it) const;
    bool operator >(const Iterator & it) const;
    bool operator >=(const Iterator & it) const;
    bool operator <(const Iterator & it) const;
    bool operator <=(const Iterator & it) const;
    const std::string & operator *() const;
    std::vector<std::map<std::string, size_t>::iterator>::const_iterator it_;
  };
  // DEFAULTS
  Domain() = default;
  Domain(const Domain & dom);
  Domain(Domain && dom) = default;
  Domain & operator =(const Domain & dom);
  Domain & operator =(Domain && dom);
  // OPERATORS
  const std::string & operator [](size_t index) const;
  size_t operator [](const std::string & name) const;
  // ALTERING METHODS
  size_t add(const std::string & name);
  size_t add(std::string && name);
  void clear();
  void erase(size_t index);
  void erase(const std::string & name);
  // PRESERVING METHODS
  Iterator begin() const;
  bool contains(const std::string & name) const;
  bool empty() const;
  Iterator end() const;
  size_t size() const;
  // ACCESS METHODS
  size_t index(const std::string & name) const;
  const std::string & name(size_t index) const;
private:
  // ALTERING METHODS
  void renew_iterators_();
  // FIELDS
  std::map<std::string, size_t> forward_;
  std::vector<std::map<std::string, size_t>::iterator> backward_;
};

} // namespace set
} // namespace pm

#endif
