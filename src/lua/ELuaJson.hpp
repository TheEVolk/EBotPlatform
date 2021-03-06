/*
    Copyright Elektro-Volk 2018
    EMail: elektro-volk@yandex.ru
    VK: https://vk.com/ebotp

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once
#include "rapidjson/document.h"
#include "luaheaders.hpp"

namespace ELuaJson {
    int decode(lua_State *L);
    namespace C2L {
        void pushObject(lua_State *L, const rapidjson::Value &j);
        void pushArray(lua_State *L, const rapidjson::Value &array);
        bool pushValue(lua_State *L, const rapidjson::Value &value);
    }
}
