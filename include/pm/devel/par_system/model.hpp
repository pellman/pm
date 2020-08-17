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
#ifndef PM_DEVEL_PAR_SET_MODEL_HPP
#define PM_DEVEL_PAR_SET_MODEL_HPP

#include <cstddef>

#include <memory>
#include <vector>

#include "pm/context.hpp"
#include "pm/parser.hpp"
#include "pm/stream.hpp"

namespace pm::devel::par_set {

class Model {
public:
  // = methods =
  // defaults
  Model() = default;
  Model(const Model & ml);
  Model(Model && ml) = default;
  Model & operator =(const Model & ml);
  Model & operator =(Model && ml) = default;
  // other
  size_t add(bool is_terminal);
  Parser & action(size_t index);
  Parser & skip();
  void set_terminality(size_t index, bool is_terminal);
  bool parse(size_t index, Stream & is, Context & con) const;
private:
  // = fields =
  std::vector<std::unique_ptr<Parser>> actions_;
  std::vector<bool> terminals_;
  Parser skip_;
};

} // namespace pm::devel::par_set

#endif
