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
#include "grammar/syntax/interpreter.hpp"

#include <dataset/syntax/interpreter.hpp>

namespace pm {
namespace grammar {
namespace syntax {

grammar::Grammar Interpreter::interpret(const Grammar & sgr) {
  reset();
  grammar::Grammar gr;
  process_named_nodes_(sgr, gr);
  process_main_name_(sgr, gr);
  process_data_(sgr, gr);
  process_skip_(sgr, gr);
  return gr;
}

void Interpreter::reset() {
  data_.clear();
  node_mapping_.clear();
}

void Interpreter::process_named_nodes_(const Grammar & sgr, grammar::Grammar & gr) {
  for(const auto & name : sgr.node_names()) {
    process_named_node_(name, sgr.node(name), gr);
  }
}

void Interpreter::process_main_name_(const Grammar & sgr, grammar::Grammar & gr) {
  if(sgr.has_main_node()) {
    gr.set_main_index(node_mapping_.at(sgr.main_name()));
  }
}

void Interpreter::process_data_(const Grammar & sgr, grammar::Grammar & gr) {
  gr.set_data_size(data_.size());
  if(sgr.has_main_data()) {
    data_.add(sgr.main_data());
    gr.set_main_data_index(data_.index_of(sgr.main_data()));
  }
}

void Interpreter::process_skip_(const Grammar & sgr, grammar::Grammar & gr) {
  if(sgr.has_skip()) {
    gr.set_skip(sgr.skip());
  }
}

void Interpreter::fill_empty_action_(const Action & sact, size_t node_index, grammar::Grammar & gr) {
  switch(sact.type()) {
  case Action::ALTERNATIVE:
    return set_alternatives_to_action_(sact.actions(), node_index, gr);
  case Action::NAME:
    return set_next_to_action_(sact.name(), node_index, gr);
  case Action::REGEXP:
    return set_re_to_action_(sact.re(), node_index, gr);
  case Action::RULE:
    return set_rule_to_action_(sact.actions(), node_index, gr);
  default:
    return;
  }
}

void Interpreter::fill_empty_node_(const Node & snode, size_t node_index, grammar::Grammar & gr) {
  auto & node = gr.node(node_index);
  if(snode.post_fail.has_value()) {
    node.set_post_fail(translate_function_(snode.post_fail.value()));
  }
  if(snode.post_success.has_value()) {
    node.set_post_success(translate_function_(snode.post_success.value()));
  }
  if(snode.pre.has_value()) {
    node.set_pre(translate_function_(snode.pre.value()));
  }
  if(snode.data.has_value() || snode.action.has_value()) {
    node.set_action();
    if(snode.data.has_value()) {
      node.act().set_data(data_.add(snode.data.value()));
    }
    if(snode.action.has_value()) {
      fill_empty_action_(snode.action.value(), node_index, gr);
    }
  }
}

void Interpreter::process_named_node_(const std::string & name, const Node & snode, grammar::Grammar & gr) {fill_empty_node_(snode, push_node_and_get_index_(name, gr), gr);}

size_t Interpreter::process_unnamed_action_(const Action & sact, grammar::Grammar & gr) {
  if(sact.type() == Action::NAME) {
    return push_node_and_get_index_(sact.name(), gr);
  }
  else {
    size_t res = gr.push_node();
    gr.node(res).set_action();
    fill_empty_action_(sact, res, gr);
    return res;
  }
}

size_t Interpreter::push_node_and_get_index_(const std::string & name, grammar::Grammar & gr) {
  auto it = node_mapping_.find(name);
  return it == node_mapping_.end()
         ? (node_mapping_[name] = gr.push_node())
         : it->second;
}

void Interpreter::set_alternatives_to_action_(const std::vector<Action> & sactions, size_t node_index, grammar::Grammar & gr) {
  std::vector<size_t> actions;
  actions.reserve(sactions.size());
  for(const auto & sa : sactions) {
    actions.push_back(process_unnamed_action_(sa, gr));
  }
  gr.node(node_index).act().set_alt(actions);
}

void Interpreter::set_next_to_action_(const std::string & name, size_t node_index, grammar::Grammar & gr) {gr.node(node_index).act().set_next(push_node_and_get_index_(name, gr));}

void Interpreter::set_re_to_action_(const regexp::Regexp & re, size_t node_index, grammar::Grammar & gr) {gr.node(node_index).act().set_re(re);}

void Interpreter::set_rule_to_action_(const std::vector<Action> & sactions, size_t node_index, grammar::Grammar & gr) {
  std::vector<size_t> actions;
  actions.reserve(sactions.size());
  for(const auto & sa : sactions) {
    actions.push_back(process_unnamed_action_(sa, gr));
  }
  gr.node(node_index).act().set_rule(actions);
}

dataset::Function Interpreter::translate_function_(const dataset::syntax::Function & sfun) {
  data_.add(sfun);
  return dataset::syntax::interpret(sfun, data_);
}

} // namespace syntax
} // namespace grammar
} // namespace pm
