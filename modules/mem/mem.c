// Copyright (C) 2026  Davide Gessa

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "py/runtime.h"

static mp_obj_t mem_peek8(mp_obj_t addr_obj) {
    uintptr_t addr = mp_obj_get_int(addr_obj);
    return mp_obj_new_int(*(volatile uint8_t*)addr);
}
static MP_DEFINE_CONST_FUN_OBJ_1(mem_peek8_obj, mem_peek8);

static mp_obj_t mem_poke8(mp_obj_t addr_obj, mp_obj_t val_obj) {
    uintptr_t addr = mp_obj_get_int(addr_obj);
    uint8_t val = mp_obj_get_int(val_obj);
    *(volatile uint8_t*)addr = val;
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(mem_poke8_obj, mem_poke8);

// static mp_obj_t mem_peek16(mp_obj_t addr_obj) {
//     uintptr_t addr = mp_obj_get_int(addr_obj);
//     return mp_obj_new_int(*(volatile uint16_t*)addr);
// }
// static MP_DEFINE_CONST_FUN_OBJ_1(mem_peek16_obj, mem_peek16);

// static mp_obj_t mem_poke16(mp_obj_t addr_obj, mp_obj_t val_obj) {
//     uintptr_t addr = mp_obj_get_int(addr_obj);
//     uint16_t val = mp_obj_get_int(val_obj);
//     *(volatile uint16_t*)addr = val;
//     return mp_const_none;
// }
// static MP_DEFINE_CONST_FUN_OBJ_2(mem_poke16_obj, mem_poke16);

// static mp_obj_t mem_peek32(mp_obj_t addr_obj) {
//     uintptr_t addr = mp_obj_get_int(addr_obj);
//     return mp_obj_new_int(*(volatile uint32_t*)addr);
// }
// static MP_DEFINE_CONST_FUN_OBJ_1(mem_peek32_obj, mem_peek32);

// static mp_obj_t mem_poke32(mp_obj_t addr_obj, mp_obj_t val_obj) {
//     uintptr_t addr = mp_obj_get_int(addr_obj);
//     uint32_t val = mp_obj_get_int(val_obj);
//     *(volatile uint32_t*)addr = val;
//     return mp_const_none;
// }
// static MP_DEFINE_CONST_FUN_OBJ_2(mem_poke32_obj, mem_poke32);

// static mp_obj_t mem_read(mp_obj_t addr_obj, mp_obj_t size_obj) {
//     uintptr_t addr = mp_obj_get_int(addr_obj);
//     size_t size = mp_obj_get_int(size_obj);
//     mp_obj_t buf = mp_obj_new_bytes(size, NULL);
//     memcpy(mp_obj_str_get_data(buf), (void*)addr, size);
//     return buf;
// }
// static MP_DEFINE_CONST_FUN_OBJ_2(mem_read_obj, mem_read);

// static mp_obj_t mem_write(mp_obj_t addr_obj, mp_obj_t buf_obj) {
//     uintptr_t addr = mp_obj_get_int(addr_obj);
//     const void *buf = mp_obj_str_get_data(buf_obj);
//     size_t len = mp_obj_get_buffer_len(buf_obj);
//     memcpy((void*)addr, buf, len);
//     return mp_const_none;
// }
// static MP_DEFINE_CONST_FUN_OBJ_2(mem_write_obj, mem_write);

static const mp_rom_map_elem_t mem_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_mem) },
    { MP_ROM_QSTR(MP_QSTR_peek8), MP_ROM_PTR(&mem_peek8_obj) },
    { MP_ROM_QSTR(MP_QSTR_poke8), MP_ROM_PTR(&mem_poke8_obj) },
    // { MP_ROM_QSTR(MP_QSTR_peek16), MP_ROM_PTR(&mem_peek16_obj) },
    // { MP_ROM_QSTR(MP_QSTR_poke16), MP_ROM_PTR(&mem_poke16_obj) },
    // { MP_ROM_QSTR(MP_QSTR_peek32), MP_ROM_PTR(&mem_peek32_obj) },
    // { MP_ROM_QSTR(MP_QSTR_poke32), MP_ROM_PTR(&mem_poke32_obj) },
    // { MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&mem_read_obj) },
    // { MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&mem_write_obj) },
};
static MP_DEFINE_CONST_DICT(mem_module_globals, mem_module_globals_table);

const mp_obj_module_t mem_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mem_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_mem, mem_user_cmodule);