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
#ifndef __GRAMMAR_SYNTAX_NODE_HPP
#define __GRAMMAR_SYNTAX_NODE_HPP

#include <dataset/syntax/function.hpp>
#include <utils/optional.hpp>
#include "grammar/syntax/action.hpp"

namespace pm {
namespace grammar {
namespace syntax {

struct Node {
  utils::Optional<Action> action;
  utils::Optional<std::string> data;
  utils::Optional<dataset::syntax::Function> post_fail;
  utils::Optional<dataset::syntax::Function> post_success;
  utils::Optional<dataset::syntax::Function> pre;
};

} // namespace syntax
} // namespace grammar
} // namespace pm

#endif