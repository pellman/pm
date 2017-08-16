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
#ifndef __GRAMMAR_NODE_HPP
#define __GRAMMAR_NODE_HPP

#include <utility>
#include <dataset/function.hpp>
#include "grammar/action.hpp"

namespace pm {
namespace grammar {

class Node {
public:
  // DEFAULTS
  Node() = default;
  // CONSTRUCTORS
  inline Node(const Action & act);
  inline Node(Action && act);
  // ALTERING METHODS
  // = set =
  inline void set_action();
  inline void set_action(const Action & act);
  inline void set_action(Action && act);
  inline void set_post_fail();
  inline void set_post_fail(const dataset::Function & fun);
  inline void set_post_fail(dataset::Function && fun);
  inline void set_post_success();
  inline void set_post_success(const dataset::Function & fun);
  inline void set_post_success(dataset::Function && fun);
  inline void set_pre();
  inline void set_pre(const dataset::Function & fun);
  inline void set_pre(dataset::Function && fun);
  // = unset =
  void unset();
  inline void unset_action();
  inline void unset_post_fail();
  inline void unset_post_success();
  inline void unset_pre();
  // ACCESS METHODS
  // = check =
  inline bool has_act() const;
  inline bool has_post_fail() const;
  inline bool has_post_success() const;
  inline bool has_pre() const;
  // = get =
  inline Action & act();
  inline const Action & act() const;
  inline dataset::Function & post_fail();
  inline const dataset::Function & post_fail() const;
  inline dataset::Function & post_success();
  inline const dataset::Function & post_success() const;
  inline dataset::Function & pre();
  inline const dataset::Function & pre() const;

private:
  utils::Optional<Action> act_;
  utils::Optional<dataset::Function> pre_;
  utils::Optional<dataset::Function> post_success_;
  utils::Optional<dataset::Function> post_fail_;
};


// IMPLEMENTATION
Node::Node(const Action & act)
  : act_(act) {}

Node::Node(Action && act)
  : act_(std::move(act)) {}

void Node::set_action() {set_action(Action());}

void Node::set_action(const Action & act) {act_ = act;}

void Node::set_action(Action && act) {act_ = std::move(act);}

void Node::set_post_fail() {post_fail_ = dataset::f_trivial;}

void Node::set_post_fail(const dataset::Function & fun) {post_fail_ = fun;}

void Node::set_post_fail(dataset::Function && fun) {post_fail_ = std::move(fun);}

void Node::set_post_success() {post_success_ = dataset::f_trivial;}

void Node::set_post_success(const dataset::Function & fun) {post_success_ = fun;}

void Node::set_post_success(dataset::Function && fun) {post_success_ = std::move(fun);}

void Node::set_pre() {pre_ = dataset::f_trivial;}

void Node::set_pre(const dataset::Function & fun) {pre_ = fun;}

void Node::set_pre(dataset::Function && fun) {pre_ = std::move(fun);}

void Node::unset_action() {act_.unset();}

void Node::unset_post_fail() {post_fail_.unset();}

void Node::unset_post_success() {post_success_.unset();}

void Node::unset_pre() {pre_.unset();}

bool Node::has_act() const {return act_.has_value();}

bool Node::has_post_fail() const {return post_fail_.has_value();}

bool Node::has_post_success() const {return post_success_.has_value();}

bool Node::has_pre() const {return pre_.has_value();}

Action & Node::act() {return act_.value();}

const Action & Node::act() const {return act_.value();}

dataset::Function & Node::post_fail() {return post_fail_.value();}

const dataset::Function & Node::post_fail() const {return post_fail_.value();}

dataset::Function & Node::post_success() {return post_success_.value();}

const dataset::Function & Node::post_success() const {return post_success_.value();}

dataset::Function & Node::pre() {return pre_.value();}

const dataset::Function & Node::pre() const {return pre_.value();}

} // namespace grammar
} // namespace pm

#endif
