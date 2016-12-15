// This file is part of boinc-app-api.
// https://boinc-next.github.io
// Copyright (C) 2008-2016 BOINC Next project and University of California
//
// boinc-app-api is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// boinc-app-api is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with boinc-app-api.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __BOINC_APP_API_MODELS_
#define __BOINC_APP_API_MODELS_

// Communication between the core client and the BOINC app library.
// This code is linked into both core client and app lib.
//
// Some apps may involve separate "coordinator" and "worker" programs.
// The coordinator runs one or more worker programs in sequence,
// and don't do work themselves.
//
// Includes the following:
// - shared memory (APP_CLIENT_SHM)
// - main init file
// - fd init file
// - graphics init file
// - conversion of symbolic links

// Shared memory is a set of MSG_CHANNELs.
// First byte of a channel is nonzero if
// the channel contains an unread data.
// This is set by the sender and cleared by the receiver.
// The sender doesn't write if the flag is set.
// Remaining 1023 bytes contain data.
//
#define MSG_CHANNEL_SIZE 1024

typedef struct {
    char buf[MSG_CHANNEL_SIZE];
} MSG_CHANNEL;
int msg_channel_peek_msg(const MSG_CHANNEL*, char*);
void msg_channel_delete_msg(MSG_CHANNEL*);
int msg_channel_get_msg(MSG_CHANNEL*, char*);
int msg_channel_has_msg(const MSG_CHANNEL*);
int msg_channel_send_msg(MSG_CHANNEL*, const char*);
void msg_channel_send_msg_overwrite(MSG_CHANNEL*, const char*);

typedef struct {
    MSG_CHANNEL process_control_request;
        // core->app
        // <quit/>
        // <suspend/>
        // <resume/>
    MSG_CHANNEL process_control_reply;
        // app->core
    MSG_CHANNEL graphics_request;
        // core->app
        // not currently used
    MSG_CHANNEL graphics_reply;
        // app->core
        // <web_graphics_url>
        // <remote_desktop_addr>
    MSG_CHANNEL heartbeat;
        // core->app
        // <heartbeat/>         sent every second, even while app is suspended
        // <wss>                app's current working set size
        // <max_wss>            max working set size
    MSG_CHANNEL app_status;
        // app->core
        // status message every second, of the form
        // <current_cpu_time>...
        // <checkpoint_cpu_time>...
        // <working_set_size>...
        // <fraction_done> ...
    MSG_CHANNEL trickle_up;
        // app->core
        // <have_new_trickle_up/>
    MSG_CHANNEL trickle_down;
        // core->app
        // <have_new_trickle_down/>
} SHARED_MEM;

#endif

