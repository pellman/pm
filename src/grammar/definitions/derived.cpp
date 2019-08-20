/*
    This file is part of the pm library package.
    Copyright (C) 2017-2019 Vladislav Podymov

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
#include "pm/grammar/definitions/derived.hpp"

//#include <string>
//#include <utility>
//#include <vector>
//#include "pm/regex/regex.hpp"
//#include "pm/set/definition.hpp"
#include "pm/set/utils/function.hpp"

//#include "pm/grammar/definition.hpp"
//#include "pm/grammar/definitions/alternative.hpp"
//#include "pm/grammar/definitions/choose.hpp"
#include "pm/grammar/definitions/fail_function.hpp"
#include "pm/grammar/definitions/function.hpp"
#include "pm/grammar/definitions/next.hpp"
#include "pm/grammar/definitions/optional.hpp"
#include "pm/grammar/definitions/regex.hpp"
//#include "pm/grammar/definitions/rule.hpp"
#include "pm/grammar/definitions/star.hpp"

namespace pm {
namespace grammar {

// = alternative =
Definition operator ||(Definition d1, Definition d2) {
  return alt(std::vector<Definition> {std::move(d1), std::move(d2)});
}
Definition operator ||(std::string d_name, Definition d) {
  return next(std::move(d_name)) || std::move(d);
}
Definition operator ||(Definition d, std::string d_name) {
  return std::move(d) || next(std::move(d_name));
}
Definition operator ||(regex::Regex r, Definition d) {
  return re(std::move(r)) || std::move(d);
}
Definition operator ||(Definition d, regex::Regex r) {
  return std::move(d) || re(std::move(r));
}
Definition operator ||(set::Definition df, Definition d) {
  return fun(std::move(df)) || std::move(d);
}
Definition operator ||(Definition d, set::Definition df) {
  return std::move(d) || fun(std::move(df));
}
// = rule (concatenation) =
Definition operator &&(Definition d1, Definition d2) {
  return rule(std::vector<Definition> {std::move(d1), std::move(d2)});
}
Definition operator &&(std::string d_name, Definition d) {
  return next(std::move(d_name)) && std::move(d);
}
Definition operator &&(Definition d, std::string d_name) {
  return std::move(d) && next(std::move(d_name));
}
Definition operator &&(regex::Regex r, Definition d) {
  return re(std::move(r)) && std::move(d);
}
Definition operator &&(Definition d, regex::Regex r) {
  return std::move(d) && re(std::move(r));
}
Definition operator &&(set::Definition df, Definition d) {
  return fun(std::move(df)) && std::move(d);
}
Definition operator &&(Definition d, set::Definition df) {
  return std::move(d) && fun(std::move(df));
}
// = fail function =
Definition operator -(Definition d, set::Definition df) {
  return ffun(std::move(d), std::move(df));
}
// = optional =
Definition operator !(Definition d) {
  return opt(std::move(d));
}
// = star =
Definition operator *(Definition d) {
  return star(std::move(d));
}

} // namespace grammar
namespace set {

// = alternative =
grammar::Definition operator ||(std::string d_name, Definition df) {
  return grammar::next(std::move(d_name)) || grammar::fun(std::move(df));
}
grammar::Definition operator ||(Definition df, std::string d_name) {
  return grammar::fun(std::move(df)) || grammar::next(std::move(d_name));
}
grammar::Definition operator ||(regex::Regex r, Definition df) {
  return grammar::re(std::move(r)) || grammar::fun(std::move(df));
}
grammar::Definition operator ||(Definition df, regex::Regex r) {
  return grammar::fun(std::move(df)) || grammar::re(std::move(r));
}
// = rule (concatenation) =
grammar::Definition operator &&(std::string d_name, Definition df) {
  return grammar::next(std::move(d_name)) && grammar::fun(std::move(df));
}
grammar::Definition operator &&(Definition df, std::string d_name) {
  return grammar::fun(std::move(df)) && grammar::next(std::move(d_name));
}
grammar::Definition operator &&(regex::Regex r, Definition df) {
  return grammar::re(std::move(r)) && grammar::fun(std::move(df));
}
grammar::Definition operator &&(Definition df, regex::Regex r) {
  return grammar::fun(std::move(df)) && grammar::re(std::move(r));
}
// = fail function =
grammar::Definition operator -(std::string d_name, Definition df) {
  return grammar::next(std::move(d_name)) - std::move(df);
}
grammar::Definition operator -(regex::Regex r, Definition df) {
  return grammar::re(std::move(r)) - std::move(df);
}
// = function =
grammar::Definition operator +(Definition df) {
  return grammar::fun(std::move(df));
}

} // namespace set
namespace regex {

grammar::Definition operator >>(Regex r, std::string data_name) {
  return grammar::re(std::move(r), std::move(data_name));
}

} // namespace regex
} // namespace pm
