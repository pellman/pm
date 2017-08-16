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
#ifndef __GRAMMAR_SYNTAX_GRAMMAR_HPP
#define __GRAMMAR_SYNTAX_GRAMMAR_HPP

#include <map>
#include <string>
#include <utility>
#include <regexp/regexp.hpp>
#include <utils/container_functions.hpp>
#include <utils/numeration.hpp>
#include <utils/optional.hpp>
#include "grammar/syntax/action.hpp"
#include "grammar/syntax/node.hpp"

namespace pm {
namespace grammar {
namespace syntax {

class Grammar {
public:
  // ALTERING METHODS
  // = set node: actions =
  void set_action(const std::string & name, const Action & action);
  void set_action(const std::string & name, Action && action);
  void set_action(std::string && name, const Action & action);
  void set_action(std::string && name, Action && action);
  inline void set_alt(const std::string & name, const std::vector<Action> & actions);
  inline void set_alt(const std::string & name, std::vector<Action> && actions);
  inline void set_alt(std::string && name, const std::vector<Action> & actions);
  inline void set_alt(std::string && name, std::vector<Action> && actions);
  inline void set_next(const std::string & name, const std::string & next_name);
  inline void set_next(const std::string & name, std::string && next_name);
  inline void set_next(std::string && name, const std::string & next_name);
  inline void set_next(std::string && name, std::string && next_name);
  void set_nonterminal(const std::string & name, const std::vector<std::vector<Action>> & action_matrix);
  void set_nonterminal(const std::string & name, std::vector<std::vector<Action>> && action_matrix);
  void set_nonterminal(std::string && name, const std::vector<std::vector<Action>> & action_matrix);
  void set_nonterminal(std::string && name, std::vector<std::vector<Action>> && action_matrix);
  inline void set_re(const std::string & name, const regexp::Regexp & re);
  inline void set_re(const std::string & name, regexp::Regexp && re);
  inline void set_re(std::string && name, const regexp::Regexp & re);
  inline void set_re(std::string && name, regexp::Regexp && re);
  inline void set_rule(const std::string & name, const std::vector<Action> & actions);
  inline void set_rule(const std::string & name, std::vector<Action> && actions);
  inline void set_rule(std::string && name, const std::vector<Action> & actions);
  inline void set_rule(std::string && name, std::vector<Action> && actions);
  // = set node: other =
  void set_data(const std::string & name, const std::string & data);
  void set_data(const std::string & name, std::string && data);
  void set_data(std::string && name, const std::string & data);
  void set_data(std::string && name, std::string && data);
  void set_post_fail(const std::string & name, const dataset::syntax::Function & fun);
  void set_post_fail(const std::string & name, dataset::syntax::Function && fun);
  void set_post_fail(std::string && name, const dataset::syntax::Function & fun);
  void set_post_fail(std::string && name, dataset::syntax::Function && fun);
  void set_post_success(const std::string & name, const dataset::syntax::Function & fun);
  void set_post_success(const std::string & name, dataset::syntax::Function && fun);
  void set_post_success(std::string && name, const dataset::syntax::Function & fun);
  void set_post_success(std::string && name, dataset::syntax::Function && fun);
  void set_pre(const std::string & name, const dataset::syntax::Function & fun);
  void set_pre(const std::string & name, dataset::syntax::Function && fun);
  void set_pre(std::string && name, const dataset::syntax::Function & fun);
  void set_pre(std::string && name, dataset::syntax::Function && fun);
  // = set other =
  inline void set_main_data(const std::string & name);
  inline void set_main_data(std::string && name);
  void set_main_name(const std::string & name);
  void set_main_name(std::string && name);
  inline void set_skip(const regexp::Regexp & re);
  inline void set_skip(regexp::Regexp && re);
  // = unset =
  void unset(const std::string & name);
  void unset_action(const std::string & name);
  void unset_data(const std::string & name);
  inline void unset_main_data();
  inline void unset_main_name();
  void unset_post_fail(const std::string & name);
  void unset_post_success(const std::string & name);
  void unset_pre(const std::string & name);
  inline void unset_skip();
  // ACCESS METHODS
  // = check
  inline bool has_main_data() const;
  inline bool has_main_node() const;
  inline bool has_node(const std::string & name) const;
  inline bool has_skip() const;
  // = get =
  inline std::string & main_data();
  inline const std::string & main_data() const;
  inline const std::string & main_name() const;
  inline Node & main_node();
  inline const Node & main_node() const;
  inline Node & node(const std::string & name);
  inline const Node & node(const std::string & name) const;
  inline const utils::Numeration<std::string> & node_names() const;
  inline regexp::Regexp & skip();
  inline const regexp::Regexp & skip() const;

private:
  // FIELDS
  std::map<std::string, Node> nodes_;
  utils::Numeration<std::string> node_name_set_;
  utils::Optional<std::string> main_node_;
  utils::Optional<regexp::Regexp> skip_;
  utils::Optional<std::string> main_data_;
};


// IMPLEMENTATION
void Grammar::set_alt(const std::string & name, const std::vector<Action> & actions) {set_action(name, alt(actions));}

void Grammar::set_alt(const std::string & name, std::vector<Action> && actions) {set_action(name, alt(std::move(actions)));}

void Grammar::set_alt(std::string && name, const std::vector<Action> & actions) {set_action(std::move(name), alt(actions));}

void Grammar::set_alt(std::string && name, std::vector<Action> && actions) {set_action(std::move(name), alt(std::move(actions)));}

void Grammar::set_next(const std::string & name, const std::string & next_name) {set_action(name, syntax::name(next_name));}

void Grammar::set_next(const std::string & name, std::string && next_name) {set_action(name, syntax::name(std::move(next_name)));}

void Grammar::set_next(std::string && name, const std::string & next_name) {set_action(std::move(name), syntax::name(next_name));}

void Grammar::set_next(std::string && name, std::string && next_name) {set_action(std::move(name), syntax::name(std::move(next_name)));}

void Grammar::set_re(const std::string & name, const regexp::Regexp & re) {set_action(name, syntax::re(re));}

void Grammar::set_re(const std::string & name, regexp::Regexp && re) {set_action(name, syntax::re(std::move(re)));}

void Grammar::set_re(std::string && name, const regexp::Regexp & re) {set_action(std::move(name), syntax::re(re));}

void Grammar::set_re(std::string && name, regexp::Regexp && re) {set_action(std::move(name), syntax::re(std::move(re)));}

void Grammar::set_rule(const std::string & name, const std::vector<Action> & actions) {set_action(name, rule(actions));}

void Grammar::set_rule(const std::string & name, std::vector<Action> && actions) {set_action(name, rule(std::move(actions)));}

void Grammar::set_rule(std::string && name, const std::vector<Action> & actions) {set_action(std::move(name), rule(actions));}

void Grammar::set_rule(std::string && name, std::vector<Action> && actions) {set_action(std::move(name), rule(std::move(actions)));}

void Grammar::set_main_data(const std::string & name) {main_data_ = name;}

void Grammar::set_main_data(std::string && name) {main_data_ = std::move(name);}

void Grammar::set_skip(const regexp::Regexp & re) {skip_ = re;}

void Grammar::set_skip(regexp::Regexp && re) {skip_ = std::move(re);}

void Grammar::unset_main_data() {main_data_.unset();}

void Grammar::unset_main_name() {main_node_.unset();}

void Grammar::unset_skip() {skip_.unset();}

bool Grammar::has_main_data() const {return main_data_.has_value();}

bool Grammar::has_main_node() const {return main_node_.has_value();}

bool Grammar::has_node(const std::string & name) const {return utils::is_in(name, nodes_);}

bool Grammar::has_skip() const {return skip_.has_value();}

std::string & Grammar::main_data() {return main_data_.value();}

const std::string & Grammar::main_data() const {return main_data_.value();}

const std::string & Grammar::main_name() const {return main_node_.value();}

Node & Grammar::main_node() {return nodes_.at(main_name());}

const Node & Grammar::main_node() const {return nodes_.at(main_name());}

Node & Grammar::node(const std::string & name) {return nodes_.at(name);}

const Node & Grammar::node(const std::string & name) const {return nodes_.at(name);}

const utils::Numeration<std::string> & Grammar::node_names() const {return node_name_set_;}

regexp::Regexp & Grammar::skip() {return skip_.value();}

const regexp::Regexp & Grammar::skip() const {return skip_.value();}

} // namespace syntax
} // namespace grammar
} // namespace pm

#endif
