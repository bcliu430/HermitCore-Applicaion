cmake_minimum_required(VERSION 3.7)
include(../../cmake/HermitCore-Application.cmake)

project(hermit_server C)

set(HEADER src/headers/handler.h src/headers/httptime.h )

add_executable( ServerLight 
    src/handler.c src/httptime.c src/server.c ${HEADER}
)


target_compile_options(ServerLight PRIVATE -pthread)
target_link_libraries(ServerLight pthread)

