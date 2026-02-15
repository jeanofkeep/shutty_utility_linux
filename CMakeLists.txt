cmake_minimum_required(VERSION 3.16)
project(MyGTKApp C)

set(CMAKE_C_STANDARD 11)

# Найти GTK через pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})
add_definitions(${GTK4_CFLAGS_OTHER})

# Добавляем исполняемый файл
add_executable(MyGTKApp main.c
        shutdown.c
        shutdown.h)

# Линкуем GTK
target_link_libraries(MyGTKApp ${GTK4_LIBRARIES})

