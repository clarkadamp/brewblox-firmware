

/*
 * Copyright 2018 BrewPi
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

#include "CboxPtr.h"
#include "ObjectContainer.h"
#include "TestObjects.h"
#include "catch.hpp"

using namespace cbox;

SCENARIO("A CboxPtr is a dynamic lookup that checks type compatibility and works similar to a weak pointer")
{

    ObjectContainer objects = {
        ContainedObject(1, 0xFF, std::make_shared<LongIntObject>(0x11111111)),
        ContainedObject(2, 0xFF, std::make_shared<LongIntObject>(0x11111111)),
    };

    CboxPtr<LongIntObject> liPtr(objects);
    CboxPtr<LongIntVectorObject> livPtr(objects);

    WHEN("Calling lock() on a CboxPtr that does not have a valid ID return an empty shared pointer")
    {
        CHECK(!liPtr.lock());
        CHECK(!livPtr.lock());
    }

    WHEN("Calling lock() on a CboxPtr that does not implement the requested type returns an empty shared pointer")
    {
        liPtr.setId(1);
        livPtr.setId(1);

        CHECK(liPtr.lock());
        CHECK(!livPtr.lock());
    }
}
