#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/class_db.hpp>
#include "postgresql.h"

using namespace godot;

void initialize_postgresql_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        return;
    }
    ClassDB::register_class<PostgreSQL>();
}

void uninitialize_postgresql_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        return;
    }
}

extern "C"
{
    // Initialization.
    GDExtensionBool GDE_EXPORT postgresql_library_init(const GDExtensionInterface *p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
    {
        godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

        init_obj.register_initializer(initialize_postgresql_module);
        init_obj.register_terminator(uninitialize_postgresql_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
