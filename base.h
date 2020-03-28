// Copyright 2009 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Base header.

#ifndef AVRLIB_BASE_H_
#define AVRLIB_BASE_H_

#include <stdint.h>

#ifndef NULL
#define NULL 0
#endif

union Word {
  uint16_t value;
  uint8_t bytes[2];
};

union LongWord {
  uint32_t value;
  uint16_t words[2];
  uint8_t bytes[4];
};

struct uint24_t {
  uint16_t integral;
  uint8_t fractional;
};

struct uint24c_t {
  uint8_t carry;
  uint16_t integral;
  uint8_t fractional;
};


#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#endif  // AVRLIB_BASE_H_
