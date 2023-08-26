
cmake_minimum_required(VERSION 3.10.0)
project(timer)

add_executable(timer_thread_demo timer_thread_demo.cpp)
target_link_libraries(timer_thread_demo pthread)


add_executable(timer_manager_demo timer_manager_demo.cpp)
target_link_libraries(timer_manager_demo pthread)
