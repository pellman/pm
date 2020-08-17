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
#ifndef PM_PAR_SYSTEM_HPP
#define PM_PAR_SYSTEM_HPP

#include <cstddef>

#include <map>
#include <memory>
#include <string>

#include "pm/parser.hpp"

#include "pm/devel/par_system/model.hpp"

namespace pm {

class ParSystem {
public:
  // = methods =
  // defaults
  ParSystem();
  ParSystem(const ParSystem & g) = delete;
  ParSystem(ParSystem && g);
  ParSystem & operator =(const ParSystem & g) = delete;
  ParSystem & operator =(ParSystem && g);
  // manage content
  Parser & skipped(const std::string & name);
  Parser & skipped(std::string && name);
  Parser & unskipped(const std::string & name);
  Parser & unskipped(std::string && name);
  Parser & action(const std::string & name, bool skip_hint = false);
  Parser & action(std::string && name, bool skip_hint = false);
  Parser & skip();
  Parser parser(const std::string & name, bool skip_hint = false);
  Parser parser(std::string && name, bool skip_hint = false);
private:
  // = methods =
  size_t get_index_strong_(const std::string & name, bool is_terminal);
  size_t get_index_strong_(std::string && name, bool is_terminal);
  size_t get_index_weak_(const std::string & name, bool is_terminal);
  size_t get_index_weak_(std::string && name, bool is_terminal);
  // = fields =
  std::map<std::string, size_t> domain_;
  std::shared_ptr<devel::par_set::Model> model_;
};

} // namespace pm

#endif
