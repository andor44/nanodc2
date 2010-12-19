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

#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <core/properties.h>
#include <utils/instance.h>
#include <string>
#include <tr1/functional>
#include <boost/signal.hpp>

namespace core {

class Settings:
    public core::Properties,
    public utils::Instance<core::Settings> 
{
public:
    Settings() { }
    void properties_changed();
    /** Read settings from a file.  */
    void read(const std::string &file);
    boost::signals::connection add_listener(std::tr1::function<void ()> slot) { return m_listeners.connect(slot); }
private:
    boost::signal<void ()> m_listeners;
};

} // namespace core

#endif // _SETTINGS_H_

