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
#include "ELua.hpp"
#include "core/EConsole.hpp"
#include "ELuaError.hpp"

ELua *e_lua;

ELua::ELua()
{

}

void ELua::start()
{
    try {
        state = new ELuaState();
        pool = new EThreadPool();
    }
    catch (ELuaError& err) {
        e_console->error("Lua", "При загрузке Lua скриптов возникла ошибка.");
        e_console->error("Lua", "Исправьте все ошибки и перезагрузите скрипты командой `relua`.");
        e_console->error("Lua", err.what());

        if (state) delete state;
        if (pool) delete pool;
    }
}

void ELua::reload()
{

}

void ELua::add(string type, rapidjson::Value &msg)
{
    if (state == nullptr) throw std::runtime_error("Lua is not working.");
    pool->add(type, msg);
}

void ELua::call(lua_State* L, int argnum, int retnum)
{
    if(lua_pcall(L, argnum, retnum, 0)) throw ELuaError(L);
}


bool ELua::safeCall(lua_State* L, int argnum, int retnum)
{
  try {
      call(L, argnum, retnum);
      return true;
  }
  catch (ELuaError& err) {
      e_console->error("Lua", err.what());
      return false;
  }
}

ELua::~ELua()
{

}
