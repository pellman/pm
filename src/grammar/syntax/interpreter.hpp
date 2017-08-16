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
#ifndef __GRAMMAR_SYNTAX_INTERPRETER_HPP
#define __GRAMMAR_SYNTAX_INTERPRETER_HPP

#include <cstddef>
#include <map>
#include <string>
#include <dataset/function.hpp>
#include <dataset/syntax/function.hpp>
#include <dataset/syntax/set.hpp>
#include "grammar/grammar.hpp"
#include "grammar/syntax/grammar.hpp"

namespace pm {
namespace grammar {
namespace syntax {

class Interpreter {
public:
  // ALTERING METHODS
  grammar::Grammar interpret(const Grammar & sgr);
  void reset();

private:
  // ALTERING METHODS
  // = high-level =
  void process_named_nodes_(const Grammar & sgr, grammar::Grammar & gr);
  void process_main_name_(const Grammar & sgr, grammar::Grammar & gr);
  void process_data_(const Grammar & sgr, grammar::Grammar & gr);
  void process_skip_(const Grammar & sgr, grammar::Grammar & gr);
  // = low-level =
  void fill_empty_action_(const Action & sact, size_t node_index, grammar::Grammar & gr);
  void fill_empty_node_(const Node & snode, size_t node_index, grammar::Grammar & gr);
  void process_named_node_(const std::string & name, const Node & snode, grammar::Grammar & gr);
  size_t process_unnamed_action_(const Action & sact, grammar::Grammar & gr);
  size_t push_node_and_get_index_(const std::string & name, grammar::Grammar & gr);
  void set_alternatives_to_action_(const std::vector<Action> & sactions, size_t node_index, grammar::Grammar & gr);
  void set_next_to_action_(const std::string & name, size_t node_index, grammar::Grammar & gr);
  void set_re_to_action_(const regexp::Regexp & re, size_t node_index, grammar::Grammar & gr);
  void set_rule_to_action_(const std::vector<Action> & sactions, size_t node_index, grammar::Grammar & gr);
  dataset::Function translate_function_(const dataset::syntax::Function & sfun);
  // FIELDS
  dataset::syntax::Set data_;
  std::map<std::string, size_t> node_mapping_;
};

} // namespace syntax
} // namespace grammar
} // namespace pm

#endif
