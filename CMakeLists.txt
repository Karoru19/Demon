cmake_minimum_required(VERSION 2.8)

project(Demon)
include_directories("include")
add_executable(${PROJECT_NAME} "main.c" "src/cstring.c" "include/cstring.h" "src/config.c" "include/config.h" "include/bool.h" "include/list.h" "src/list.c" "include/dir.h" "src/dir.c" "src/parse.c" "include/parse.h" "include/sync.h" "src/sync.c" "include/modtime.h" "src/modtime.c" "include/file.h" "src/file.c")
