// This file is part of boinc-app-api.
// https://boinc-next.github.io
// Copyright (C) 2008-2016 BOINC Next project and University of California
//
// boinc-app-apiis free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// boinc-app-apiis distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with boinc-app-api.  If not, see <http://www.gnu.org/licenses/>.

#include "models.h"

#include <string.h>

int msg_channel_peek_msg(const MSG_CHANNEL* self, char* msg) {
    if (!self->buf[0]) return 0;
    strncpy(msg, self->buf+1, MSG_CHANNEL_SIZE-1);
    msg[MSG_CHANNEL_SIZE-1] = 0;
    return 1;
}
void msg_channel_delete_msg(MSG_CHANNEL* self) {
    self->buf[0] = 0;
}
int msg_channel_get_msg(MSG_CHANNEL* self, char* msg) {
    if (!msg_channel_peek_msg(self, msg)) return 0;
    msg_channel_delete_msg(self);
    return 1;
}
int msg_channel_has_msg(const MSG_CHANNEL* self) {
    return self->buf[0] ? 1 : 0;
}
void msg_channel_send_msg_overwrite(MSG_CHANNEL* self, const char* msg) {
    strncpy(self->buf+1, msg, MSG_CHANNEL_SIZE-1);
    self->buf[MSG_CHANNEL_SIZE-1] = 0;
    self->buf[0] = 1;
}
int msg_channel_send_msg(MSG_CHANNEL* self, const char* msg) {
    if (msg_channel_has_msg(self)) return 0;
    msg_channel_send_msg_overwrite(self, msg);
    return 1;
}
