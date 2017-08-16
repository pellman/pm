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
#include "grammar/grammar.hpp"

namespace pm {
namespace grammar {

size_t Grammar::push_node(const Node & node) {
  size_t res = nodes_.size();
  nodes_.push_back(node);
  return res;
}

size_t Grammar::push_node(Node && node) {
  size_t res = nodes_.size();
  nodes_.push_back(std::move(node));
  return res;
}

size_t Grammar::push_alt(const std::vector<size_t> & nodes) {
  size_t res = nodes_.size();
  nodes_.emplace_back(alt(nodes));
  return res;
}

size_t Grammar::push_alt(std::vector<size_t> && nodes) {
  size_t res = nodes_.size();
  nodes_.emplace_back(alt(std::move(nodes)));
  return res;
}

size_t Grammar::push_next(size_t node) {
  size_t res = nodes_.size();
  nodes_.emplace_back(next(node));
  return res;
}

size_t Grammar::push_re(const regexp::Regexp & re) {
  size_t res = nodes_.size();
  nodes_.emplace_back(grammar::re(re));
  return res;
}

size_t Grammar::push_re(regexp::Regexp && re) {
  size_t res = nodes_.size();
  nodes_.emplace_back(grammar::re(std::move(re)));
  return res;
}

size_t Grammar::push_rule(const std::vector<size_t> & nodes) {
  size_t res = nodes_.size();
  nodes_.emplace_back(rule(nodes));
  return res;
}

size_t Grammar::push_rule(std::vector<size_t> && nodes) {
  size_t res = nodes_.size();
  nodes_.emplace_back(rule(std::move(nodes)));
  return res;
}

bool Grammar::gmatch(std::istream & stream, Context & gcontext) const {
  stream::Stream str(stream);
  return gmatch(str, gcontext);
}

bool Grammar::gmatch(const std::string & stream, Context & gcontext) const {
  std::stringstream str(stream);
  return gmatch(str, gcontext);
}

bool Grammar::match_full(stream::Stream & stream, regexp::Context & context) const {
  if(context.adc.is_active() && !main_data_index_.has_value()) {
    return false;
  }
  Context gcontext(data_size_);
  if(main_data_index_.has_value()) {
    gcontext.data(main_data_index_.value()) = context.adc.dc;
  }
  gcontext.adc.ac.receive(context.adc.ac);
  gcontext.asc = context.asc;
  return gmatch_full(stream, gcontext);
}

bool Grammar::gmatch_(const Node & node, stream::Stream & stream, Context & gcontext) const {
  if(node.has_pre()) {
    node.pre().apply(gcontext.adc.dc);
  }
  bool res = true;
  if(node.has_act()) {
    res = gmatch_(node.act(), stream, gcontext);
  }
  if(res && node.has_post_success()) {
    node.post_success().apply(gcontext.adc.dc);
  }
  if(!res && node.has_post_fail()) {
    node.post_fail().apply(gcontext.adc.dc);
  }
  return res;
}

bool Grammar::gmatch_(const Action & act, stream::Stream & stream, Context & gcontext) const {
  switch(act.type()) {
  case Action::ALTERNATIVE:
    return gmatch_alt_(act, stream, gcontext);
  case Action::NEXT:
    return gmatch_next_(act, stream, gcontext);
  case Action::REGEXP:
    return gmatch_re_(act, stream, gcontext);
  case Action::RULE:
    return gmatch_rule_(act, stream, gcontext);
  default:
    return true;
  }
}

bool Grammar::gmatch_alt_(const Action & act, stream::Stream & stream, Context & gcontext) const {
  // TODO no string duplicates in data, maybe fix it later
  for(const auto & i : act.nodes()) {
    if(gmatch_(nodes_[i], stream, gcontext)) return true;
  }
  return false;
}

bool Grammar::gmatch_re_(const Action & act, stream::Stream & stream, Context & gcontext) const {
  regexp::Context con;
  con.asc.activate();
  while(skip_.match(stream, con));
  if(gcontext.asc.is_inactive()) {
    con.asc.deactivate();
  }
  if(act.has_data()) {
    con.adc.dc = gcontext.data(act.data());
    if(gcontext.adc.is_active()) {
      con.adc.activate();
    }
  }
  bool res = act.re().match(stream, con);
  if(res) {
    if(gcontext.asc.is_active()) {
      gcontext.string() += std::move(con.string());
    }
    return true;
  }
  else {
    stream.unget(con.string());
    return false;
  }
}

bool Grammar::gmatch_rule_(const Action & act, stream::Stream & stream, Context & gcontext) const {
  // TODO no string duplicates in data, maybe fix it later
  Context con = gcontext;
  con.asc.detach_set_activate("");
  for(const auto & i : act.nodes()) {
    if(!gmatch_(nodes_[i], stream, con)) {
      stream.unget(con.string());
      return false;
    }
  }
  if(gcontext.asc.is_active()) {
    gcontext.string() += std::move(con.string());
  }
  return true;
}

} // namespace grammar
} // namespace pm
