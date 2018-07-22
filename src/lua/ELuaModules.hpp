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
#include "common.hpp"
#include "luaheaders.hpp"
#include <vector>

struct ELuaModulesModule { string name; bool isLoaded; };

class ELuaModules {
private:
public:
    std::vector<ELuaModulesModule> modules;

    ELuaModules();
    void loadModules(lua_State *L);
    void clearModules();
    void startModules(lua_State *L);
    void load();
    ~ELuaModules();
protected:

};