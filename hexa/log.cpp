//---------------------------------------------------------------------------
// hexa/log.cpp
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
// Copyright 2013, nocte@hippie.nu
//---------------------------------------------------------------------------

#include "log.hpp"

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include "trace.hpp"

namespace hexa {

namespace {
    static std::ostream* out_ = nullptr;
    boost::mutex log_mutex;
}

void set_log_output (std::ostream& str)
{
    out_ = &str;
}

void log_msg (const std::string& msg)
{
    if (out_ == nullptr)
        return;

    boost::lock_guard<boost::mutex> lock (log_mutex);
    *out_ << msg << std::endl;

#ifndef NDEBUG
    //std::cout << msg << std::endl;
#endif
}

} // namespace hexa

