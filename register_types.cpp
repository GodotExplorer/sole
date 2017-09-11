/*************************************************************************/
/*  register_types.cpp                                                   */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2017 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include <core/reference.h>
#include <core/class_db.h>
#include "register_types.h"
#include "sole.hpp"

class Sole : public Reference {
    GDCLASS(Sole, Reference);

public:
    enum UUID_VERSION {
        VERSION_0,
        VERSION_1,
        VERSION_4
    };

protected:
    sole::uuid generator = sole::uuid4();
    UUID_VERSION version = VERSION_4;

    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("pretty"), &Sole::pretty);
        ClassDB::bind_method(D_METHOD("base62"), &Sole::base62);
        ClassDB::bind_method(D_METHOD("uuid"), &Sole::uuid);
        ClassDB::bind_method(D_METHOD("set_version", "version"), &Sole::set_version);
        ClassDB::bind_method(D_METHOD("get_version"), &Sole::get_version);

        ADD_PROPERTY(PropertyInfo(Variant::INT, "version"), "set_version", "get_version");

        BIND_ENUM_CONSTANT(VERSION_0);
        BIND_ENUM_CONSTANT(VERSION_1);
        BIND_ENUM_CONSTANT(VERSION_4);
    }

public:
    String pretty() const { return generator.pretty().c_str(); }
    String base62() const { return generator.base62().c_str(); }
    String uuid() const { return generator.str().c_str(); }
    UUID_VERSION get_version() const { return version; }

    void set_version(UUID_VERSION p_version) {
        version = p_version;
        switch (version) {
            case VERSION_0:
                generator = sole::uuid0();
                break;
            case VERSION_1:
                generator = sole::uuid1();
                break;
            case VERSION_4:
                generator = sole::uuid4();
                break;
        }
    }

    operator String() { return uuid(); }
};
VARIANT_ENUM_CAST(Sole::UUID_VERSION);

void register_sole_types() {
    ClassDB::register_class<Sole>();
}

void unregister_sole_types() {
}
