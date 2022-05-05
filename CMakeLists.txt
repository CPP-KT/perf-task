cmake_minimum_required(VERSION 3.21)
project(perf)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

add_subdirectory(perf)


if (ENABLE_SLOW_TEST)
  add_subdirectory(ci-extra/perf)
endif ()

option(USE_SANITIZERS "Enable to build with undefined,leak and address sanitizers" OFF)
if (USE_SANITIZERS)
  target_compile_options(tests PUBLIC -fsanitize=address,undefined,leak -fno-sanitize-recover=all)
  target_link_options(tests PUBLIC -fsanitize=address,undefined,leak)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(tests PUBLIC -stdlib=libc++)
endif()

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  target_compile_options(tests PUBLIC -D_GLIBCXX_DEBUG)
endif()
