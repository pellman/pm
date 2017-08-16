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
#include "grammar/context/adataset.hpp"

namespace pm {
namespace grammar {
namespace context {

void ADataSet::detach() {
  ac.detach();
  dc.detach();
}

void ADataSet::detach_receive(const ADataSet & adc) {
  ac.detach_receive(adc.ac);
  dc.detach_receive(adc.dc);
}

void ADataSet::detach_unset_activate() {
  ac.detach_activate();
  dc.detach_unset();
}

void ADataSet::detach_unset_deactivate() {
  ac.detach_deactivate();
  dc.detach_unset();
}

void ADataSet::receive(const ADataSet & adc) const {
  ac.receive(adc.ac);
  dc.receive(adc.dc);
}

void ADataSet::unset_activate() const {
  ac.activate();
  dc.unset();
}

void ADataSet::unset_deactivate() const {
  ac.deactivate();
  dc.unset();
}

void ADataSet::send(const ADataSet & adc) const {
  ac.send(adc.ac);
  dc.send(adc.dc);
}

} // namespace context
} // namespace grammar
} // namespace pm
