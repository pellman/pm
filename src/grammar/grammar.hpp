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
#ifndef __GRAMMAR_GRAMMAR_HPP
#define __GRAMMAR_GRAMMAR_HPP

#include <cstddef>
#include <utility>
#include <vector>
#include <regexp/literal.hpp>
#include <regexp/regexp.hpp>
#include <regexp/basic/fail.hpp>
#include "grammar/context.hpp"
#include "grammar/node.hpp"

namespace pm {
namespace grammar {

class Grammar
  : public regexp::Literal {
public:
  // ALTERING METHODS
  // = push node =
  size_t push_alt(const std::vector<size_t> & nodes);
  size_t push_alt(std::vector<size_t> && nodes);
  size_t push_next(size_t node);
  inline size_t push_node();
  size_t push_node(const Node & node);
  size_t push_node(Node && node);
  size_t push_re(const regexp::Regexp & re);
  size_t push_re(regexp::Regexp && re);
  size_t push_rule(const std::vector<size_t> & nodes);
  size_t push_rule(std::vector<size_t> && nodes);
  // = set =
  inline void set_data_size(size_t size);
  inline void set_main_data_index(size_t i);
  inline void set_main_index(size_t i);
  inline void set_nodes(const std::vector<Node> & nodes);
  inline void set_nodes(std::vector<Node> && nodes);
  inline void set_skip(const regexp::Regexp & re);
  inline void set_skip(regexp::Regexp && re);
  inline void unset_main_data_index();
  // PRESERVING METHODS
  inline bool gmatch(stream::Stream & stream, Context & gcontext = default_context) const;
  bool gmatch(std::istream & stream, Context & gcontext = default_context) const;
  bool gmatch(const std::string & stream, Context & gcontext = default_context) const;
  inline bool gmatch_full(stream::Stream & stream, Context & gcontext) const;
  bool match_full(stream::Stream & stream, regexp::Context & context) const override;
  // ACCESS METHODS
  inline size_t data_size() const;
  inline bool has_main_data() const;
  inline size_t main_data_index() const;
  inline size_t main_index() const;
  inline Node & main_node();
  inline const Node & main_node() const;
  inline Node & node(size_t i);
  inline const Node & node(size_t i) const;
  inline regexp::Regexp skip() const;

private:
  // PRESERVING METHODS
  bool gmatch_(const Node & node, stream::Stream & stream, Context & gcontext) const;
  bool gmatch_(const Action & act, stream::Stream & stream, Context & gcontext) const;
  bool gmatch_alt_(const Action & act, stream::Stream & stream, Context & gcontext) const;
  inline bool gmatch_next_(const Action & act, stream::Stream & stream, Context & gcontext) const;
  bool gmatch_re_(const Action & act, stream::Stream & stream, Context & gcontext) const;
  bool gmatch_rule_(const Action & act, stream::Stream & stream, Context & gcontext) const;
  // FIELDS
  std::vector<Node> nodes_ = std::vector<Node>(1);
  size_t main_index_ = 0;
  regexp::Regexp skip_ = regexp::fail;
  size_t data_size_ = 0;
  utils::Optional<size_t> main_data_index_;
};


// IMPLEMENTATION
size_t Grammar::push_node() {return push_node(Node());}

void Grammar::set_data_size(size_t size) {data_size_ = size;}

void Grammar::set_main_data_index(size_t i) {main_data_index_ = i;}

void Grammar::set_main_index(size_t i) {main_index_ = i;}

void Grammar::set_nodes(const std::vector<Node> & nodes) {nodes_ = nodes;}

void Grammar::set_nodes(std::vector<Node> && nodes) {nodes_ = std::move(nodes);}

void Grammar::set_skip(const regexp::Regexp & re) {skip_ = re;}

void Grammar::set_skip(regexp::Regexp && re) {skip_ = std::move(re);}

void Grammar::unset_main_data_index() {main_data_index_.unset();}

bool Grammar::gmatch(stream::Stream & stream, Context & gcontext) const {return gmatch_full(stream, gcontext);}

bool Grammar::gmatch_full(stream::Stream & stream, Context & gcontext) const {return gmatch_(nodes_[main_index_], stream, gcontext);}

size_t Grammar::data_size() const {return data_size_;}

bool Grammar::has_main_data() const {return main_data_index_.has_value();}

size_t Grammar::main_data_index() const {return main_data_index_.value();}

size_t Grammar::main_index() const {return main_index_;}

Node & Grammar::main_node() {return nodes_[main_index_];}

const Node & Grammar::main_node() const {return nodes_[main_index_];}

Node & Grammar::node(size_t i) {return nodes_[i];}

const Node & Grammar::node(size_t i) const {return nodes_[i];}

regexp::Regexp Grammar::skip() const {return skip_;}

bool Grammar::gmatch_next_(const Action & act, stream::Stream & stream, Context & gcontext) const {return gmatch_(nodes_[act.next()], stream, gcontext);}

} // namespace grammar
} // namespace pm

#endif
