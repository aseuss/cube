set(CC_TEST_SOURCE_FILES
    dummy_test.cc
)

add_executable(${NAME}_tests ${CC_TEST_SOURCE_FILES})
target_link_libraries(${NAME}_tests gtest gtest_main)

add_test(unit_tests ${NAME}_tests)
