/*
 * Copyright 2018 BrewPi B.V.
 *
 * This file is part of BrewPi.
 *
 * BrewPi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BrewPi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "TempSensorWidget.h"
#include "BrewBlox.h"

TempSensorWidget::TempSensorWidget(WidgetWrapper& myWrapper, const cbox::obj_id_t& id)
    : ProcessValueWidgetBase(myWrapper)
    , lookup(brewbloxBox().makeCboxPtr<TempSensor>(id))
{
}

void
TempSensorWidget::update()
{
    if (auto ptr = lookup.const_lock()) {
        enableBackground(true);
        char buf[12];
        to_chars(ptr->value(), buf, 12, 1);
        setValue(buf, true);
        setSetting("", true);
        return;
    }
    setValue("", false);
    setSetting("", false);
    enableBackground(false);
}
