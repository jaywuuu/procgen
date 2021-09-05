cmake_minimum_required(VERSION 3.10)

# set the project name
project(ProcGen)

# add the executable
add_executable(ProcGen
    src/main.cpp
    src/tileset.cpp
    src/dungeongen.cpp
    src/random.cpp
)

# test executables
add_executable(Grid2D_Test
    test/grid2d_test.cpp
)

add_executable(NoiseFunc_Test
    test/noisefunc_test.cpp
)

add_executable(NoiseFuncRNG_Test
    test/noisefuncrng_test.cpp
    src/random.cpp
)

add_executable(WinTest
    test/wintest.cpp
)

include_directories(PUBLIC
    "include/"
)
