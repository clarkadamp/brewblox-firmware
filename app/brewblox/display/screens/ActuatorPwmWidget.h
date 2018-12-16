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

#pragma once
#include "ActuatorPwm.h"
#include "ProcessValueWidgetBase.h"
#include "cbox/CboxPtr.h"

class ActuatorPwmWidget : public ProcessValueWidgetBase {
private:
    cbox::CboxPtr<ActuatorPwm> lookup;

public:
    ActuatorPwmWidget(WidgetWrapper& myWrapper, const cbox::obj_id_t& id);
    virtual ~ActuatorPwmWidget() = default;

    virtual void update() override final;

    static void
    onClickStatic(void* thisPtr)
    {
    }
    void
    onClick()
    {
    }
};