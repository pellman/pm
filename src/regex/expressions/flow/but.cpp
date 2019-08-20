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
#include "pm/regex/expressions/flow/but.hpp"

#include <utility>

//#include "pm/regex/regex.hpp"
#include "pm/regex/utils/parser.hpp"

namespace pm {
namespace regex {

namespace {

// core
class ParserBut
  : public utils::Parser {
public:
  ParserBut(utils::ParserPtr ptr, utils::ParserPtr exclude);
  bool match(stream::Stream & is, DataContext & context) const override;

private:
  const utils::ParserPtr ptr_;
  const utils::ParserPtr exclude_;
};

// core implementation
ParserBut::ParserBut(utils::ParserPtr ptr, utils::ParserPtr exclude)
  : ptr_(std::move(ptr)),
    exclude_(std::move(exclude)) {}

bool ParserBut::match(stream::Stream & is, DataContext & context) const {
  stream::Stream pis = is;
  DataContext pcontext(context.flag
                              ? context
                              : DataContext()
                             );
  if(!ptr_->match(pis, pcontext)) {
    return false;
  }
  {
    stream::Stream nis = is.prefix(pis.pos());
    DataContext ncontext;
    if(exclude_->match(nis, ncontext)) {
      return false;
    }
  }
  if(context.flag) {
    context.dcur.swap(pcontext.dcur);
    context.dacc.swap(pcontext.dacc);
  }
  is.reposition(pis.pos());
  return true;
}

} // namespace

// interface
Regex but(Regex r, Regex exclude) {
  return new ParserBut(std::move(r).ptr(), std::move(exclude).ptr());
}

} // namespace regex
} // namespace pm
