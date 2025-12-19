add_executable(soa_template_cpu.out soa_template.cpp)
add_test(NAME soa_template_cpu_test COMMAND soa_template_cpu.out)

target_include_directories(
  soa_template_cpu.out PRIVATE ${CMAKE_SOURCE_DIR}/../include
                               ${doctest_SOURCE_DIR}/doctest)

target_link_libraries(soa_template_cpu.out PRIVATE Boost::boost
                                                   doctest::doctest)

if(COVERAGE)
  target_compile_options(soa_template_cpu.out PRIVATE -g --coverage)
  target_link_options(soa_template_cpu.out PRIVATE --coverage)
endif()
