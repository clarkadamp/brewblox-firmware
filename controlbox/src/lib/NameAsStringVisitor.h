/*
 * Copyright 2018 Elco Jacobs / BrewBlox
 *
 * This file is part of ControlBox.
 *
 * Controlbox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Controlbox.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>
#include <type_traits>
#include <typeinfo>
#include "ObjectVisitorBase.h"

namespace cbox {

class NameAsStringVisitor : public ObjectVisitorBase {
private:
    std::string className;

public:
    NameAsStringVisitor()
        : className("unknown")
    {
    }
    virtual ~NameAsStringVisitor() = default;

    template <typename T>
    void
    visit(T* visited)
    {
        className = typeid(T);
    };
};

} // end namespace cbox
