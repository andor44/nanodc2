/* vim:set ts=4 sw=4 sts=4 et cindent: */
/*
 * nanodc - The ncurses DC++ client
 * Copyright © 2005-2006 Markus Lindqvist <nanodc.developer@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Contributor(s):
 *  
 */

#include <sstream>
#include <stdexcept>
#include <functional>
#include <utils/utils.h>
#include <core/events.h>
#include <core/log.h>

namespace modules {

class Rot13
{
public:
    Rot13() {
//        events::add_listener_first("key pressed",
//                std::bind(&Rot13::key_pressed, this));
    }

    void key_pressed()
    {
        wint_t ch = events::arg<wint_t>(1);

        if(std::isalpha(ch)) {
            if(toupper(ch) < ('A' + 13))
                ch += 13;
            else
                ch -= 13;
        }
        events::arg(1) = ch;
        std::ostringstream oss;
        oss << (char)ch << " - " << (char)events::arg<wint_t>(1);

        core::Log::get()->log(oss.str(), core::MT_DEBUG);
    }
};

} // namespace modules

static modules::Rot13 initialize;

