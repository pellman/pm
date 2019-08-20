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
#ifndef PM_GRAMMAR_DEFINITIONS_DERIVED_HPP
#define PM_GRAMMAR_DEFINITIONS_DERIVED_HPP

//#include <string>
#include <utility>
//#include <vector>
#include "pm/regex/regex.hpp"
#include "pm/set/definition.hpp"

//#include "pm/grammar/definition.hpp"
#include "pm/grammar/definitions/alternative.hpp"
#include "pm/grammar/definitions/choose.hpp"
#include "pm/grammar/definitions/rule.hpp"

namespace pm {
namespace grammar {

// = alternative =
template<typename ... Definitions>
Definition alt(Definitions && ... dseq) {
  return alt(std::vector<Definition> {std::forward<Definitions>(dseq) ...});
}
Definition operator ||(Definition d1, Definition d2);
Definition operator ||(std::string d_name, Definition d);
Definition operator ||(Definition d, std::string d_name);
Definition operator ||(regex::Regex r, Definition d);
Definition operator ||(Definition d, regex::Regex r);
Definition operator ||(set::Definition df, Definition d);
Definition operator ||(Definition d, set::Definition df);
// = rule (concatenation) =
template<typename ... Definitions>
Definition rule(Definitions && ... dseq) {
  return rule(std::vector<Definition> {std::forward<Definitions>(dseq) ...});
}
Definition operator &&(Definition d1, Definition d2);
Definition operator &&(std::string d_name, Definition d);
Definition operator &&(Definition d, std::string d_name);
Definition operator &&(regex::Regex r, Definition d);
Definition operator &&(Definition d, regex::Regex r);
Definition operator &&(set::Definition df, Definition d);
Definition operator &&(Definition d, set::Definition df);
// = choose =
template<typename ... Definitions>
Definition choose(std::string data_name, Definitions && ... dseq) {
  return choose(std::move(data_name), std::vector<Definition> {std::forward<Definitions>(dseq) ...});
}
// = fail function =
Definition operator -(Definition d, set::Definition df);
// = optional =
Definition operator !(Definition d);
// = star =
Definition operator *(Definition d);

} // namespace grammar
namespace set {

// = alternative =
grammar::Definition operator ||(std::string d_name, Definition df);
grammar::Definition operator ||(Definition df, std::string d_name);
grammar::Definition operator ||(regex::Regex r, Definition df);
grammar::Definition operator ||(Definition df, regex::Regex r);
// = rule (concatenation) =
grammar::Definition operator &&(std::string d_name, Definition df);
grammar::Definition operator &&(Definition df, std::string d_name);
grammar::Definition operator &&(regex::Regex r, Definition df);
grammar::Definition operator &&(Definition df, regex::Regex r);
// = fail function =
grammar::Definition operator -(std::string d_name, Definition df);
grammar::Definition operator -(regex::Regex r, Definition df);
// = function =
grammar::Definition operator +(Definition df);

} // namespace set
namespace regex {

grammar::Definition operator >>(Regex r, std::string data_name);

} // namespace grammar
} // namespace pm

#endif
