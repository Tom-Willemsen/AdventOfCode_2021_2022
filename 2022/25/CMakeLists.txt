add_library(2022_day25_impl SHARED day25_impl.c)
add_executable(2022_day25 day25.c)
target_link_libraries(2022_day25_impl m)
target_link_libraries(2022_day25 2022_day25_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day25_tests day25_tests.c 2022_day25_impl) 
