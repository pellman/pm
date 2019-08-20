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
#ifndef PM_GRAMMAR_GRAMMAR_HPP
#define PM_GRAMMAR_GRAMMAR_HPP

//#include <cstddef>
//#include <map>
//#include <string>
//#include "pm/regex/regex.hpp"
//#include "pm/set/domain.hpp"

#include "pm/grammar/definition.hpp"
#include "pm/grammar/nonterminal.hpp"
//#include "pm/grammar/utils/interpret_info.hpp"
//#include "pm/grammar/utils/model.hpp"

namespace pm {
namespace grammar {

class Grammar {
public:
  // ALTERING METHODS
  void set_skip(regex::Regex r);
  void synchronize();
  void unset_skip();
  // PRESERVING METHODS
  bool has_data(const std::string & data_name) const;
  bool has_nt(const std::string & nt_name) const;
  bool has_skip() const;
  // ACCESS METHODS
  set::Domain data_domain() const;
  size_t data_index(const std::string & data_name) const;
  Nonterminal nt(const std::string & nt_name) const;
  std::map<std::string, Nonterminal> nt_map() const;
  regex::Regex re(const std::string & nt_name) const;
  regex::Regex re(const std::string & nt_name, const std::string & data_name) const;
  // FIELDS
  std::map<std::string, Definition> definitions;
  
private:
  // FIELDS
  utils::InterpretInfo ii_;
  utils::ModelPtr model_ptr_ = utils::ModelPtr(new utils::Model());
};

} // namespace grammar
} // namespace pm

#endif
