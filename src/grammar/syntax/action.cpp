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
#include "grammar/syntax/action.hpp"

#include <utility>

namespace pm {
namespace grammar {
namespace syntax {

void Action::set_alt(const std::vector<Action> & actions) {
  unset_();
  t_ = ALTERNATIVE;
  actions_ = actions;
}

void Action::set_alt(std::vector<Action> && actions) {
  unset_();
  t_ = ALTERNATIVE;
  actions_ = std::move(actions);
}

void Action::set_name(const std::string & name) {
  unset_();
  t_ = NAME;
  name_ = name;
}

void Action::set_name(std::string && name) {
  unset_();
  t_ = NAME;
  name_ = std::move(name);
}

void Action::set_re(const regexp::Regexp & re) {
  unset_();
  t_ = REGEXP;
  re_ = re;
}

void Action::set_re(regexp::Regexp && re) {
  unset_();
  t_ = REGEXP;
  re_ = std::move(re);
}

void Action::set_rule(const std::vector<Action> & actions) {
  unset_();
  t_ = RULE;
  actions_ = actions;
}

void Action::set_rule(std::vector<Action> && actions) {
  unset_();
  t_ = RULE;
  actions_ = std::move(actions);
}

void Action::unset() {
  unset_();
  t_ = TRIVIAL;
}

void Action::unset_() {
  switch(t_) {
  case REGEXP:
    re_.unset();
    break;
  case ALTERNATIVE:
  case RULE:
    actions_.unset();
    break;
  case NAME:
    name_.unset();
    break;
  default:
    break;
  }
}

Action trivial_action;

Action alt(const std::vector<Action> & actions) {
  Action res;
  res.set_alt(actions);
  return res;
}

Action alt(std::vector<Action> && actions) {
  Action res;
  res.set_alt(std::move(actions));
  return res;
}

Action name(const std::string & name) {
  Action res;
  res.set_name(name);
  return res;
}

Action name(std::string && name) {
  Action res;
  res.set_name(std::move(name));
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

Action rule(const std::vector<Action> & actions) {
  Action res;
  res.set_rule(actions);
  return res;
}

Action rule(std::vector<Action> && actions) {
  Action res;
  res.set_rule(std::move(actions));
  return res;
}

} // namespace syntax
} // namespace grammar
} // namespace pm
