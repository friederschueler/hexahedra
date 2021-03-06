//---------------------------------------------------------------------------
// lib/basic_types.cpp
//
// This file is part of Hexahedra.
//
// Hexahedra is free software; you can redistribute it and/or modify it
// under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2014, nocte@hippie.nu
//---------------------------------------------------------------------------

#include "basic_types.hpp"

namespace hexa {

const block_vector dir_vector[] =
    { block_vector( 1, 0, 0),
      block_vector(-1, 0, 0),
      block_vector( 0, 1, 0),
      block_vector( 0,-1, 0),
      block_vector( 0, 0, 1),
      block_vector( 0, 0,-1) };

const block_vector neumann_neighborhood[] =
    { block_vector(-1, 0, 0),
      block_vector( 0,-1, 0),
      block_vector( 0, 0,-1),
      block_vector( 0, 0, 0),
      block_vector( 0, 0, 1),
      block_vector( 0, 1, 0),
      block_vector( 1, 0, 0) };

}

