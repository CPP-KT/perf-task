
add_compile_options(-Wall -pedantic -Wextra -Wno-sign-compare)
add_compile_options(-Wold-style-cast -Wextra-semi -Woverloaded-virtual -Wzero-as-null-pointer-constant)
if(TREAT_WARNINGS_AS_ERRORS)
  add_compile_options(-Werror -pedantic-errors)
endif()

add_executable(bench_jpeg bench_jpeg.cpp)
target_link_libraries(bench_jpeg benchmark::benchmark)

add_executable(bench_pi bench_pi.cpp)
target_link_libraries(bench_pi benchmark::benchmark)

add_executable(bench_radix_sort bench_radix_sort.cpp)
target_link_libraries(bench_radix_sort benchmark::benchmark)

add_executable(bench_json bench_json.cpp)
target_link_libraries(bench_json benchmark::benchmark)

add_executable(bench_logger bench_logger.cpp)
target_link_libraries(bench_logger benchmark::benchmark)
