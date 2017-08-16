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
#ifndef __GRAMMAR_ACTION_HPP
#define __GRAMMAR_ACTION_HPP

#include <cstddef>
#include <vector>
#include <regexp/regexp.hpp>
#include <utils/optional.hpp>

namespace pm {
namespace grammar {

class Action {
public:
  // TYPES
  enum T {TRIVIAL, ALTERNATIVE, NEXT, REGEXP, RULE};
  // ALTERING METHODS
  void set_alt(const std::vector<size_t> & nodes);
  void set_alt(std::vector<size_t> && nodes);
  inline void set_data(size_t data);
  void set_next(size_t node);
  void set_re(const regexp::Regexp & re);
  void set_re(regexp::Regexp && re);
  void set_rule(const std::vector<size_t> & nodes);
  void set_rule(std::vector<size_t> && nodes);
  void unset();
  void unset_control();
  inline void unset_data();
  // ACCESS METHODS
  // = type =
  inline T type() const;
  // = check =
  inline bool has_data() const;
  inline bool has_next() const;
  inline bool has_nodes() const;
  inline bool has_re() const;
  // = get =
  inline size_t & data();
  inline const size_t & data() const;
  inline size_t & next();
  inline const size_t & next() const;
  inline std::vector<size_t> & nodes();
  inline const std::vector<size_t> & nodes() const;
  inline regexp::Regexp & re();
  inline const regexp::Regexp & re() const;

private:
  // METHODS
  void unset_();
  void unset_control_();
  // FIELDS
  T t_ = TRIVIAL;
  utils::Optional<size_t> data_;
  utils::Optional<size_t> next_;
  utils::Optional<std::vector<size_t>> nodes_;
  utils::Optional<regexp::Regexp> re_;
};

extern Action trivial_action;

Action alt(const std::vector<size_t> & nodes);
Action alt(std::vector<size_t> && nodes);
Action next(size_t node);
Action re(const regexp::Regexp & re);
Action re(regexp::Regexp && re);
Action rule(const std::vector<size_t> & nodes);
Action rule(std::vector<size_t> && nodes);


// IMPLEMENTATION
void Action::set_data(size_t data) {data_ = data;}

void Action::unset_data() {data_.unset();}

Action::T Action::type() const {return t_;}

bool Action::has_data() const {return data_.has_value();}

bool Action::has_next() const {return next_.has_value();}

bool Action::has_nodes() const {return nodes_.has_value();}

bool Action::has_re() const {return re_.has_value();}

size_t & Action::data() {return data_.value();}

const size_t & Action::data() const {return data_.value();}

size_t & Action::next() {return next_.value();}

const size_t & Action::next() const {return next_.value();}

std::vector<size_t> & Action::nodes() {return nodes_.value();}

const std::vector<size_t> & Action::nodes() const {return nodes_.value();}

regexp::Regexp & Action::re() {return re_.value();}

const regexp::Regexp & Action::re() const {return re_.value();}

} // namespace grammar
} // namespace pm

#endif
