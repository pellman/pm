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
#include "grammar/action.hpp"

#include <utility>

namespace pm {
namespace grammar {

void Action::set_alt(const std::vector<size_t> & nodes) {
  unset_control_();
  t_ = ALTERNATIVE;
  nodes_ = nodes;
}

void Action::set_alt(std::vector<size_t> && nodes) {
  unset_control_();
  t_ = ALTERNATIVE;
  nodes_ = std::move(nodes);
}

void Action::set_next(size_t node) {
  unset_control_();
  t_ = NEXT;
  next_ = node;
}

void Action::set_re(const regexp::Regexp & re) {
  unset_control_();
  t_ = REGEXP;
  re_ = re;
}

void Action::set_re(regexp::Regexp && re) {
  unset_control_();
  t_ = REGEXP;
  re_ = std::move(re);
}

void Action::set_rule(const std::vector<size_t> & nodes) {
  unset_control_();
  t_ = RULE;
  nodes_ = nodes;
}

void Action::set_rule(std::vector<size_t> && nodes) {
  unset_control_();
  t_ = RULE;
  nodes_ = std::move(nodes);
}

void Action::unset() {
  unset_control();
  unset_data();
  t_ = TRIVIAL;
}

void Action::unset_control() {
  unset_control_();
  t_ = TRIVIAL;
}

void Action::unset_() {
  unset_control_();
  unset_data();
}

void Action::unset_control_() {
  switch(t_) {
  case REGEXP:
    re_.unset();
    break;
  case ALTERNATIVE:
  case RULE:
    nodes_.unset();
    break;
  case NEXT:
    next_.unset();
  default:
    break;
  }
}

Action trivial_action;

Action alt(const std::vector<size_t> & nodes) {
  Action res;
  res.set_alt(nodes);
  return res;
}

Action alt(std::vector<size_t> && nodes) {
  Action res;
  res.set_alt(std::move(nodes));
  return res;
}

Action re(const regexp::Regexp & re) {
  Action res;
  res.set_re(re);
  return res;
}

Action re(regexp::Regexp && re) {
  Action res;
  res.set_re(std::move(re));
  return res;
}

Action rule(const std::vector<size_t> & nodes) {
  Action res;
  res.set_rule(nodes);
  return res;
}

Action rule(std::vector<size_t> && nodes) {
  Action res;
  res.set_rule(std::move(nodes));
  return res;
}

Action next(size_t node) {
  Action res;
  res.set_next(node);
  return res;
}

} // namespace grammar
} // namespace pm
