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
#ifndef __GRAMMAR_SYNTAX_ACTION_HPP
#define __GRAMMAR_SYNTAX_ACTION_HPP

#include <string>
#include <vector>
#include <regexp/regexp.hpp>
#include <utils/optional.hpp>

namespace pm {
namespace grammar {
namespace syntax {

class Action {
public:
  // TYPES
  enum T {TRIVIAL, ALTERNATIVE, NAME, REGEXP, RULE};
  // ALTERING METHODS
  void set_alt(const std::vector<Action> & actions);
  void set_alt(std::vector<Action> && actions);
  void set_name(const std::string & name);
  void set_name(std::string && name);
  void set_re(const regexp::Regexp & re);
  void set_re(regexp::Regexp && re);
  void set_rule(const std::vector<Action> & actions);
  void set_rule(std::vector<Action> && actions);
  void unset();
  // ACCESS METHODS
  // = type =
  inline T type() const;
  // = check =
  inline bool has_actions() const;
  inline bool has_name() const;
  inline bool has_re() const;
  // = get =
  inline std::vector<Action> & actions();
  inline const std::vector<Action> & actions() const;
  inline std::string & name();
  inline const std::string & name() const;
  inline regexp::Regexp & re();
  inline const regexp::Regexp & re() const;

private:
  // ALTERING METHODS
  void unset_();
  // FIELDS
  T t_ = TRIVIAL;
  utils::Optional<std::vector<Action>> actions_;
  utils::Optional<std::string> name_;
  utils::Optional<regexp::Regexp> re_;
};

extern Action trivial_action;

Action alt(const std::vector<Action> & actions);
Action alt(std::vector<Action> && actions);
Action name(const std::string & name);
Action name(std::string && name);
Action re(const regexp::Regexp & re);
Action re(regexp::Regexp && re);
Action rule(const std::vector<Action> & actions);
Action rule(std::vector<Action> && actions);


// IMPLEMENTATION
Action::T Action::type() const {return t_;}

bool Action::has_actions() const {return actions_.has_value();}

bool Action::has_name() const {return name_.has_value();}

bool Action::has_re() const {return re_.has_value();}

std::vector<Action> & Action::actions() {return actions_.value();}

const std::vector<Action> & Action::actions() const {return actions_.value();}

std::string & Action::name() {return name_.value();}

const std::string & Action::name() const {return name_.value();}

regexp::Regexp & Action::re() {return re_.value();}

const regexp::Regexp & Action::re() const {return re_.value();}

} // namespace syntax
} // namespace grammar
} // namespace pm

#endif
