set(SAMPLE_NAME device_info)

add_executable(${SAMPLE_NAME} main.cc)

target_link_libraries(${SAMPLE_NAME} LINK_PUBLIC cube)
