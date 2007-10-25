/***************************************************************************
 *   Copyright (C) 2005 Nicolas Hadacek <hadacek@kde.org>                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "pic_group.h"

#include "pic_memory.h"

Device::Memory *Pic::Group::createMemory(const Device::Data &data) const
{
  return new Memory(static_cast<const Pic::Data &>(data));
}