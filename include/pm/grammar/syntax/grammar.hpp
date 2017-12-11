/*
    This file is part of the pm library package.
    Copyright (C) 2017, 2018 Vladislav Podymov
    
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
#ifndef __PM_GRAMMAR_SYNTAX_GRAMMAR_HPP
#define __PM_GRAMMAR_SYNTAX_GRAMMAR_HPP

#include <map>
#include <set>
#include <string>
#include <utility>
#include "pm/regexp/regexp.hpp"
#include "pm/utils/optional.hpp"
#include "pm/grammar/grammar.hpp"
#include "pm/grammar/syntax/action.hpp"
#include "pm/grammar/syntax/actions/base.hpp"
#include "pm/grammar/syntax/interpret_info.hpp"

namespace pm {
namespace grammar {
namespace syntax {

class Grammar {
public:
  // OPERATORS
  inline Action & operator [](const std::string & name);
  inline Action & operator [](std::string && name);
  // ALTERING METHODS
  inline void add(const std::string & name, const Action & a);
  inline void add(const std::string & name, Action && a);
  inline void add(std::string && name, const Action & a);
  inline void add(std::string && name, Action && a);
  template<typename ... Args>
  void add(const std::string & name, Args && ... args);
  template<typename ... Args>
  void add(std::string && name, Args && ... args);
  inline void erase(const std::string & action_name);
  inline void set_main(const std::string & name);
  inline void set_main(std::string && name);
  inline void set_main_data(const std::string & name);
  inline void set_main_data(std::string && name);
  inline void set_skip(const regexp::Regexp & re);
  inline void set_skip(regexp::Regexp && re);
  inline void unset_main();
  inline void unset_main_data();
  inline void unset_skip();
  // PRESERVING METHODS
  grammar::Grammar interpret() const;
  grammar::Grammar interpret(InterpretInfo & ii) const;
  
private:
  // PRESERVING METHODS
  // FIELDS
  std::map<std::string, Action> actions_;
  utils::Optional<std::string> main_;
  utils::Optional<std::string> main_data_;
  utils::Optional<regexp::Regexp> skip_;
};


// implementation
Action & Grammar::operator [](const std::string & name) {return actions_[name];}

Action & Grammar::operator [](std::string && name) {return actions_[name];}

void Grammar::add(const std::string & name, const Action & a) {actions_[name] = a;}

void Grammar::add(const std::string & name, Action && a) {actions_[name] = std::move(a);}

void Grammar::add(std::string && name, const Action & a) {actions_[std::move(name)] = a;}

void Grammar::add(std::string && name, Action && a) {actions_[std::move(name)] = std::move(a);}

template<typename ... Args>
void Grammar::add(const std::string & name, Args && ... args) {add(name, ac(std::forward<Args>(args) ...));}

template<typename ... Args>
void Grammar::add(std::string && name, Args && ... args) {add(std::move(name), ac(std::forward<Args>(args) ...));}

void Grammar::erase(const std::string & action_name) {actions_.erase(action_name);}

void Grammar::set_main(const std::string & name) {main_ = name;}

void Grammar::set_main(std::string && name) {main_ = std::move(name);}

void Grammar::set_main_data(const std::string & name) {main_data_ = name;}

void Grammar::set_main_data(std::string && name) {main_data_ = std::move(name);}

void Grammar::set_skip(const regexp::Regexp & re) {skip_ = re;}

void Grammar::set_skip(regexp::Regexp && re) {skip_ = std::move(re);}

void Grammar::unset_main() {main_.unset();}

void Grammar::unset_main_data() {main_data_.unset();}

void Grammar::unset_skip() {skip_.unset();}

} // namespace syntax
} // namespace grammar
} // namespace pm

#endif
