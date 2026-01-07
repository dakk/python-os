// Copyright (C) 2009-2026  Davide Gessa

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

static mp_obj_t io_inb(mp_obj_t port_obj) {
    uint16_t port = mp_obj_get_int(port_obj);
    uint8_t value;
    __asm__ __volatile__("inb %1, %0" : "=a" (value) : "dN" (port));
    return mp_obj_new_int(value);
}
static MP_DEFINE_CONST_FUN_OBJ_1(io_inb_obj, io_inb);

static mp_obj_t io_outb(mp_obj_t data_obj, mp_obj_t port_obj) {
    uint8_t data = mp_obj_get_int(data_obj);
    uint16_t port = mp_obj_get_int(port_obj);
    __asm__ __volatile__("outb %1, %0" : : "dN" (port), "a" (data));
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(io_outb_obj, io_outb);

static mp_obj_t io_inw(mp_obj_t port_obj) {
    uint16_t port = mp_obj_get_int(port_obj);
    uint16_t value;
    __asm__ __volatile__("inw %1, %0" : "=a" (value) : "dN" (port));
    return mp_obj_new_int(value);
}
static MP_DEFINE_CONST_FUN_OBJ_1(io_inw_obj, io_inw);

static mp_obj_t io_outw(mp_obj_t data_obj, mp_obj_t port_obj) {
    uint16_t data = mp_obj_get_int(data_obj);
    uint16_t port = mp_obj_get_int(port_obj);
    __asm__ __volatile__("outw %1, %0" : : "dN" (port), "a" (data));
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(io_outw_obj, io_outw);

static mp_obj_t io_inl(mp_obj_t port_obj) {
    uint16_t port = mp_obj_get_int(port_obj);
    uint32_t value;
    __asm__ __volatile__("inl %1, %0" : "=a" (value) : "dN" (port));
    return mp_obj_new_int(value);
}
static MP_DEFINE_CONST_FUN_OBJ_1(io_inl_obj, io_inl);

static mp_obj_t io_outl(mp_obj_t data_obj, mp_obj_t port_obj) {
    uint32_t data = mp_obj_get_int(data_obj);
    uint16_t port = mp_obj_get_int(port_obj);
    __asm__ __volatile__("outl %1, %0" : : "dN" (port), "a" (data));
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(io_outl_obj, io_outl);

static const mp_rom_map_elem_t io_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_io) },
    { MP_ROM_QSTR(MP_QSTR_inb), MP_ROM_PTR(&io_inb_obj) },
    { MP_ROM_QSTR(MP_QSTR_outb), MP_ROM_PTR(&io_outb_obj) },
    { MP_ROM_QSTR(MP_QSTR_inw), MP_ROM_PTR(&io_inw_obj) },
    { MP_ROM_QSTR(MP_QSTR_outw), MP_ROM_PTR(&io_outw_obj) },
    { MP_ROM_QSTR(MP_QSTR_inl), MP_ROM_PTR(&io_inl_obj) },
    { MP_ROM_QSTR(MP_QSTR_outl), MP_ROM_PTR(&io_outl_obj) },
};
static MP_DEFINE_CONST_DICT(io_module_globals, io_module_globals_table);

const mp_obj_module_t io_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&io_module_globals,
};
MP_REGISTER_MODULE(MP_QSTR_io, io_user_cmodule);
