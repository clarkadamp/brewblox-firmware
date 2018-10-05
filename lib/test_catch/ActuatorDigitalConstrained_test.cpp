/*
 * Copyright 2018 BrewPi B.V.
 *
 * This file is part of the BrewBlox Control Library.
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

#include <catch.hpp>

#include "ActuatorDigitalConstrained.h"
#include "ActuatorDigitalMock.h"

using State = ActuatorDigital::State;

SCENARIO("ActuatorDigitalConstrained", "[constraints]")
{
    auto now = ticks_millis_t(0);
    auto mock = ActuatorDigitalMock();
    auto constrained = ActuatorDigitalConstrained(mock, now);

    WHEN("A minimum ON time constrained is added, the actuator cannot turn off before it has passed")
    {
        constrained.addConstraint(ADConstraints::MinOnTime(1500));
        constrained.state(State::Active, now);
        CHECK(constrained.state() == State::Active);
        CHECK(mock.state() == State::Active);

        now += 1499;
        constrained.state(ActuatorDigital::Inactive, now);
        CHECK(constrained.state() == State::Active);
        CHECK(mock.state() == State::Active);

        now += 1;
        constrained.state(ActuatorDigital::Inactive, now);
        CHECK(constrained.state() == State::Inactive);
        CHECK(mock.state() == State::Inactive);
    }

    WHEN("A minimum OFF time constrained is added, the actuator cannot turn on before it has passed")
    {
        constrained.addConstraint(ADConstraints::MinOffTime(1500));
        constrained.state(State::Inactive, now);
        CHECK(constrained.state() == State::Inactive);
        CHECK(mock.state() == State::Inactive);

        now += 1499;
        constrained.state(ActuatorDigital::Active, now);
        CHECK(constrained.state() == State::Inactive);
        CHECK(mock.state() == State::Inactive);

        now += 1;
        constrained.state(ActuatorDigital::Active, now);
        CHECK(constrained.state() == State::Active);
        CHECK(mock.state() == State::Active);
    }

    WHEN("A minimum ON and a minimum OFF time are added, both are honored")
    {
        constrained.state(State::Inactive, now);
        constrained.addConstraint(ADConstraints::MinOffTime(1000));
        constrained.addConstraint(ADConstraints::MinOnTime(2000));

        while (constrained.state() == State::Inactive) {
            constrained.state(State::Active, ++now);
        }
        auto timesOff = constrained.getLastStartEndTime(State::Inactive, now);
        CHECK(timesOff.end - timesOff.start == 1000);

        while (constrained.state() == State::Active) {
            constrained.state(State::Inactive, ++now);
        }

        auto timesOn = constrained.getLastStartEndTime(State::Active, now);
        CHECK(timesOn.end - timesOn.start == 2000);
    }
}

SCENARIO("Mutex contraint", "[constraints]")
{
    auto now = ticks_millis_t(0);
    auto mock1 = ActuatorDigitalMock();
    auto constrained1 = ActuatorDigitalConstrained(mock1, now);
    auto mock2 = ActuatorDigitalMock();
    auto constrained2 = ActuatorDigitalConstrained(mock2, now);
    auto mut = std::make_shared<std::mutex>();

    constrained1.state(State::Inactive, now);
    constrained2.state(State::Inactive, now);

    constrained1.addConstraint(ADConstraints::Mutex<std::mutex>(
        [&mut]() {
            return mut;
        }));
    constrained2.addConstraint(ADConstraints::Mutex<std::mutex>(
        [&mut]() {
            return mut;
        }));

    WHEN("Two actuators share a mutex, they cannot be active at the same time")
    {
        constrained1.state(State::Active, ++now);
        CHECK(constrained1.state() == State::Active);
        constrained2.state(State::Active, ++now);
        CHECK(constrained2.state() == State::Inactive);

        constrained1.state(State::Inactive, ++now);
        constrained2.state(State::Active, ++now);
        CHECK(constrained2.state() == State::Active);

        constrained1.state(State::Active, ++now);
        CHECK(constrained1.state() == State::Inactive);
    }

    WHEN("A minimum OFF time constraint holds an actuator low, it doesn't lock the mutex")
    {
        constrained1.addConstraint(ADConstraints::MinOffTime(1000));
        constrained1.state(State::Active, ++now);
        CHECK(constrained1.state() == State::Inactive);
        constrained2.state(State::Active, ++now);
        CHECK(constrained2.state() == State::Active);
    }
}
