# Создание библиотеки
add_library(starship
    datatypes.h datatypes.cpp
    interfaces.h interfaces.cpp
    implementations.h implementations.cpp
    adaptors.h adaptors.cpp
    commands.h commands.cpp
    starship.h
    fuel_adaptors.h fuel_adaptors.cpp
    fuel_interfaces.h fuel_interfaces.cpp
    fuel_commands.h fuel_commands.cpp
)

# Интерфейс библиотеки (заголовки)
target_include_directories(starship PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

