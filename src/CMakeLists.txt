
set(CC_SOURCE_FILES
    vulkan_application.cc
    vulkan_instance.cc
    vulkan_debug.cc
    log.cc
)

add_library(${NAME} SHARED ${CC_SOURCE_FILES})

#target_include_directories(${NAME} PUBLIC
target_include_directories(${NAME} SYSTEM PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${NAME}>
    #$<INSTALL_INTERFACE:include/${NAME} ${PROJECT_BINARY_DIR}/${NAME}_config.h>
)
target_link_libraries(${NAME} ${Vulkan_LIBRARY})

get_target_property(NLA ${NAME} INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS ${NLA})
#set_target_properties(${NAME} PROPERTIES PUBLIC_HEADER ${NLA})

install(TARGETS ${NAME}
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/${NAME})
#install(FILES ${PROJECT_SOURCE_DIR}/src/include DESTINATION include)
#install(FILES ${PROJECT_BINARY_DIR}/${NAME}_config.h DESTINATION include/${NAME})
