/*
Copyright (C) 2007 Dmitry Baikov

This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include "JackPortType.h"
#include <string.h>
#include <assert.h>

namespace Jack
{

static const JackPortType* port_types[] =
    {
        &gAudioPortType,
        &gMidiPortType,
    };

enum
{
    PORT_TYPES_MAX = sizeof(port_types) / sizeof(port_types[0])
};

int GetPortTypeId(const char* port_type)
{
    for (int i = 0; i < PORT_TYPES_MAX; ++i) {
        const JackPortType* type = port_types[i];
        assert(type != 0);
        if (strcmp(port_type, type->name) == 0)
            return i;
    }
    return -1;
}

const JackPortType* GetPortType(int type_id)
{
    assert(type_id >= 0 && type_id <= PORT_TYPES_MAX);
    const JackPortType* type = port_types[type_id];
    assert(type != 0);
    return type;
}

} // namespace Jack
