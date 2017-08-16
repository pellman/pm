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
#include "grammar/syntax/grammar.hpp"

namespace pm {
namespace grammar {
namespace syntax {

void Grammar::set_action(const std::string & name, const Action & action) {
  node_name_set_.add(name);
  nodes_[name].action = action;
}

void Grammar::set_action(const std::string & name, Action && action) {
  node_name_set_.add(name);
  nodes_[name].action = std::move(action);
}

void Grammar::set_action(std::string && name, const Action & action) {
  node_name_set_.add(name);
  nodes_[std::move(name)].action = action;
}

void Grammar::set_action(std::string && name, Action && action) {
  node_name_set_.add(name);
  nodes_[std::move(name)].action = std::move(action);
}

void Grammar::set_nonterminal(const std::string & name, const std::vector<std::vector<Action>> & action_matrix) {
  std::vector<Action> alternatives;
  alternatives.reserve(action_matrix.size());
  for(const auto & action_line : action_matrix) {
    alternatives.push_back(rule(action_line));
  }
  set_alt(name, std::move(alternatives));
}

void Grammar::set_nonterminal(const std::string & name, std::vector<std::vector<Action>> && action_matrix) {
  std::vector<Action> alternatives;
  alternatives.reserve(action_matrix.size());
  for(const auto & action_line : action_matrix) {
    alternatives.push_back(rule(std::move(action_line)));
  }
  set_alt(name, std::move(alternatives));
}

void Grammar::set_nonterminal(std::string && name, const std::vector<std::vector<Action>> & action_matrix) {
  std::vector<Action> alternatives;
  alternatives.reserve(action_matrix.size());
  for(const auto & action_line : action_matrix) {
    alternatives.push_back(rule(action_line));
  }
  set_alt(std::move(name), std::move(alternatives));
}

void Grammar::set_nonterminal(std::string && name, std::vector<std::vector<Action>> && action_matrix) {
  std::vector<Action> alternatives;
  alternatives.reserve(action_matrix.size());
  for(const auto & action_line : action_matrix) {
    alternatives.push_back(rule(std::move(action_line)));
  }
  set_alt(std::move(name), std::move(alternatives));
}

void Grammar::set_data(const std::string & name, const std::string & data) {
  node_name_set_.add(name);
  nodes_[name].data = data;
}

void Grammar::set_data(const std::string & name, std::string && data) {
  node_name_set_.add(name);
  nodes_[name].data = std::move(data);
}

void Grammar::set_data(std::string && name, const std::string & data) {
  node_name_set_.add(name);
  nodes_[std::move(name)].data = data;
}

void Grammar::set_data(std::string && name, std::string && data) {
  node_name_set_.add(name);
  nodes_[std::move(name)].data = std::move(data);
}

void Grammar::set_post_fail(const std::string & name, const dataset::syntax::Function & fun) {
  node_name_set_.add(name);
  nodes_[name].post_fail = fun;
}

void Grammar::set_post_fail(const std::string & name, dataset::syntax::Function && fun) {
  node_name_set_.add(name);
  nodes_[name].post_fail = std::move(fun);
}

void Grammar::set_post_fail(std::string && name, const dataset::syntax::Function & fun) {
  node_name_set_.add(name);
  nodes_[std::move(name)].post_fail = fun;
}

void Grammar::set_post_fail(std::string && name, dataset::syntax::Function && fun) {
  node_name_set_.add(name);
  nodes_[std::move(name)].post_fail = std::move(fun);
}

void Grammar::set_post_success(const std::string & name, const dataset::syntax::Function & fun) {
  node_name_set_.add(name);
  nodes_[name].post_success = fun;
}

void Grammar::set_post_success(const std::string & name, dataset::syntax::Function && fun) {
  node_name_set_.add(name);
  nodes_[name].post_success = std::move(fun);
}

void Grammar::set_post_success(std::string && name, const dataset::syntax::Function & fun) {
  node_name_set_.add(name);
  nodes_[std::move(name)].post_success = fun;
}

void Grammar::set_post_success(std::string && name, dataset::syntax::Function && fun) {
  node_name_set_.add(name);
  nodes_[std::move(name)].post_success = std::move(fun);
}

void Grammar::set_pre(const std::string & name, const dataset::syntax::Function & fun) {
  node_name_set_.add(name);
  nodes_[name].pre = fun;
}

void Grammar::set_pre(const std::string & name, dataset::syntax::Function && fun) {
  node_name_set_.add(name);
  nodes_[name].pre = std::move(fun);
}

void Grammar::set_pre(std::string && name, const dataset::syntax::Function & fun) {
  node_name_set_.add(name);
  nodes_[std::move(name)].pre = fun;
}

void Grammar::set_pre(std::string && name, dataset::syntax::Function && fun) {
  node_name_set_.add(name);
  nodes_[std::move(name)].pre = std::move(fun);
}

void Grammar::set_main_name(const std::string & name) {
  node_name_set_.add(name);
  nodes_[name];
  main_node_ = name;
}

void Grammar::set_main_name(std::string && name) {
  node_name_set_.add(name);
  nodes_[name];
  main_node_ = std::move(name);
}


void Grammar::unset(const std::string & name) {
  nodes_.erase(name);
  node_name_set_.remove(name);
}

void Grammar::unset_action(const std::string & name) {
  auto it = nodes_.find(name);
  if(it != nodes_.end()) {
    it->second.action.unset();
  }
}

void Grammar::unset_data(const std::string & name) {
  auto it = nodes_.find(name);
  if(it != nodes_.end()) {
    it->second.data.unset();
  }
}

void Grammar::unset_post_fail(const std::string & name) {
  auto it = nodes_.find(name);
  if(it != nodes_.end()) {
    it->second.post_fail.unset();
  }
}

void Grammar::unset_post_success(const std::string & name) {
  auto it = nodes_.find(name);
  if(it != nodes_.end()) {
    it->second.post_success.unset();
  }
}

void Grammar::unset_pre(const std::string & name) {
  auto it = nodes_.find(name);
  if(it != nodes_.end()) {
    it->second.pre.unset();
  }
}

} // namespace syntax
} // namespace grammar
} // namespace pm
