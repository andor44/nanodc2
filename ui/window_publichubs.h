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


#ifndef _WINDOWHUBS_H_
#define _WINDOWHUBS_H_

#include <vector>
#include <client/stdinc.h>
#include <client/DCPlusPlus.h>
#include <client/FavoriteManager.h>
#include <core/log.h>
#include <utils/mutex.h>
#include <utils/lock.h>
#include <display/listview.h>

namespace ui {

class WindowHubs:
    public display::ListView,
    public FavoriteManagerListener
{
public:
    WindowHubs();

    void connect();
    void favorite();
    void download();
    void show_entries();

    void handle_line(const std::string &line);

    std::string get_infobox_line(unsigned int n);

    virtual void on(DownloadStarting, const std::string&) throw();
    virtual void on(DownloadFailed, const std::string&) throw();
    virtual void on(DownloadFinished, const std::string&) throw();

    /** Destructor. */
    ~WindowHubs();
private:
    enum Property {
        PROP_NONE,
        PROP_DESCRIPTION,
        PROP_ADDRESS,
        PROP_HUBLIST,
        PROP_USERS,
        PROP_MINSHARE,
        PROP_MAXSHARE
    };

    std::vector<HubEntry> m_hubs;
    int m_hublist;
    utils::Mutex m_entryLock;

    // hub filters
    std::vector<std::string> m_words;
    std::string m_addressFilter;
    int64_t m_minShare;
    int64_t m_maxShare;
    int64_t m_minUsers;
    bool m_shutdown;

    void set_property(Property property);
    Property m_property;

    /** Returns true if search result matches current filters. */
    bool matches(HubEntry &entry);

    utils::Mutex m_mutex;
};

} // namespace ui

#endif // _WINDOWHUBS_H_
