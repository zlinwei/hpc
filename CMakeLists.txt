cmake_minimum_required(VERSION 3.10)
project(acc LANGUAGES CXX)

option(use_OpenACC "use OpenACC" ON)
option(use_OpenMP "use OpenMP" ON)
option(use_OpenMPI "use OpenMPI" ON)

option(use_GPU "use GPU" OFF)

message(STATUS "${CMAKE_CXX_COMPILER}")
message(STATUS "${CMAKE_CXX_COMPILER_ID}")

if (${use_GPU})
    add_definitions(-DUSE_GPU)
endif ()

# OpenACC
if (${use_OpenACC})
    add_definitions(-DUSE_OPENACC)
    find_package(OpenACC REQUIRED)
    if (${OpenACC_CXX_FOUND})
        message(STATUS "OpenACC CXX compiler found")
    endif ()
    if (${OpenACC_C_FOUND})
        message(STATUS "OpenACC C Compiler found")
    endif ()

    message(STATUS "OpenACC C FLAGS: ${OpenACC_C_FLAGS}")
    message(STATUS "OpenACC CXX FLAGS: ${OpenACC_CXX_FLAGS}")
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

    message(STATUS "OpenACC C version: ${OpenACC_C_VERSION}")
    message(STATUS "OpenACC CXX version: ${OpenACC_CXX_VERSION}")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenACC_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenACC_CXX_FLAGS}")

    if (${use_GPU})
    else ()
        #        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ta=multicore")
    endif ()

endif (${use_OpenACC})


# OpenMP
if (${use_OpenMP})
    add_definitions(-DUSE_OPENMP)
    find_package(OpenMP REQUIRED)
    if (${OpenMP_CXX_FOUND})
        message(STATUS "OpenMP CXX found")
    endif ()
    if (${OpenMP_C_FOUND})
        message(STATUS "OpenMP C found")
    endif ()

    message(STATUS "OpenMP_CXX_FLAGS ${OpenMP_CXX_FLAGS}")
    message(STATUS "OpenMP_C_FLAGS ${OpenMP_C_FLAGS}")


    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif (${use_OpenMP})


message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")


message(STATUS "${OpenMP_CXX_LIBRARIES}")

add_executable(acc main.cpp)
target_link_libraries(acc)