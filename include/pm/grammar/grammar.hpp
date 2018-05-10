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
#ifndef __PM_GRAMMAR_GRAMMAR_HPP
#define __PM_GRAMMAR_GRAMMAR_HPP

#include <cstddef>
#include <vector>
#include "pm/regexp/regexp.hpp"
#include "pm/utils/optional.hpp"
#include "pm/grammar/action.hpp"
#include "pm/grammar/actions.hpp"

namespace pm {
namespace grammar {

class Grammar
  : public regexp::RegexpInterface {
public:
  // ALTERING METHODS
  size_t add();
  size_t add(const Action & a);
  size_t add(Action && a);
  template<typename ... Args>
  size_t add(Args && ... args);
  inline void set_main(size_t i);
  inline void set_main_data(size_t i);
  inline void set_skip(const regexp::Regexp & re);
  inline void set_skip(regexp::Regexp && re);
  inline void unset_main();
  inline void unset_main_data();
  inline void unset_skip();
  // PRESERVING METHODS
  inline bool gmatch(stream::Stream & s, const Context & gcontext = default_context) const;
  bool gmatch(std::istream & s, const Context & gcontext = default_context) const;
  bool gmatch(const std::string & s, const Context & gcontext = default_context) const;
  inline bool gmatch_full(stream::Stream & s, const Context & gcontext) const;
  bool match_full(stream::Stream & s, const regexp::Context & context) const override;
  // ACCESS METHODS
  inline Action & action(size_t i);
  inline const Action & action(size_t i) const;
  inline bool has_skip() const;
  inline Action & main_action();
  inline const Action & main_action() const;
  inline size_t main_data() const;
  inline size_t main_index() const;
  inline regexp::Regexp & skip();
  inline const regexp::Regexp & skip() const;

private:
  // FIELDS
  std::vector<Action> actions_{ac_false()};
  size_t main_ = 0;
  size_t main_data_ = 0;
  utils::Optional<regexp::Regexp> skip_;
};


// implementation
template<typename ... Args>
size_t Grammar::add(Args && ... args) {return add(ac(std::forward<Args>(args) ...));}

void Grammar::set_main(size_t i) {main_ = i;}

void Grammar::set_main_data(size_t i) {main_data_ = i;}

void Grammar::set_skip(const regexp::Regexp & re) {skip_ = re;}

void Grammar::set_skip(regexp::Regexp && re) {skip_ = std::move(re);}

void Grammar::unset_main() {main_ = 0;}

void Grammar::unset_main_data() {main_data_ = 0;}

void Grammar::unset_skip() {skip_.unset();}

bool Grammar::gmatch(stream::Stream & s, const Context & gcontext) const {return gmatch_full(s, gcontext);}

bool Grammar::gmatch_full(stream::Stream & s, const Context & gcontext) const {return main_action().gamatch(s, *this, gcontext);}

Action & Grammar::action(size_t i) {return actions_[i];}

const Action & Grammar::action(size_t i) const {return actions_[i];}

bool Grammar::has_skip() const {return skip_.nonempty();}

Action & Grammar::main_action() {return action(main_index());}

const Action & Grammar::main_action() const {return action(main_index());}

size_t Grammar::main_data() const {return main_data_;}

size_t Grammar::main_index() const {return main_;}

regexp::Regexp & Grammar::skip() {return skip_.val();}

const regexp::Regexp & Grammar::skip() const {return skip_.val();}

} // namespace grammar
} // namespace pm

#endif
