//---------------------------------------------------------------------------
/// \file   server/server_entity_system.hpp
/// \brief  Server-specific extensions to the entity system
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
// Copyright 2013-2014, nocte@hippie.nu
//---------------------------------------------------------------------------

#pragma once

#include <string>
#include <hexa/entity_system.hpp>
#include <hexa/serialize.hpp>

namespace hexa {

class server_entity_system : public entity_system
{
public:
    enum server_components
    {
        c_ip_addr = c_last_component,   // ip_addr
        c_player_uid,                   // uint64_t
        c_last_server_component
    };

public:
    server_entity_system();
};

} // namespace hexa

namespace es {

template<> inline
void serialize<std::string>(const std::string& obj, std::vector<char>& buf)
{
    buf.push_back(uint8_t(obj.size() & 0xff));
    buf.push_back(uint8_t((obj.size() >> 8) & 0xff));
    buf.insert(buf.end(), obj.begin(), obj.end());
}

template<> inline
std::vector<char>::const_iterator
deserialize<std::string>(std::string& obj,
                         std::vector<char>::const_iterator first,
                         std::vector<char>::const_iterator last)
{
    if (std::distance(first,last) < 2)
        throw std::runtime_error("can't serialize");

    uint16_t len (uint8_t(*first) + (uint16_t(uint8_t(*(first+1))) << 8));
    first += 2;

    auto end (first + len);
    if (end > last)
    {
        throw std::runtime_error("not enough data");
    }

    obj.assign(first, end);

    return end;
}

}
