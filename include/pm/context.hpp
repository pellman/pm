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
#ifndef PM_CONTEXT_HPP
#define PM_CONTEXT_HPP

#include <cstddef>

#include <memory>
#include <vector>

#include "pm/data.hpp"

namespace pm {

class Context {
public:
  // = methods =
  // defaults
  Context() = default;
  Context(const Context & con);
  Context(Context && con);
  Context & operator =(const Context & con);
  Context & operator =(Context && con);
  // constructors
  Context(size_t max_index_hint);
  // operators
  Data & operator [](size_t data_index);
  const Data & operator [](size_t data_index) const;
  // content manipulation
  void swap(Context & con);
  void swap(const std::vector<size_t> & data_indexes, Context & con);
  void clear();
private:
  // = methods =
  void enlarge_(size_t data_index) const;
  // = fields =
  mutable std::vector<std::unique_ptr<Data>> vec_;
};

void swap(Context & con1, Context & con);

} // namespace pm

#endif
