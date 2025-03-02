include_directories(${PROJECT_SOURCE_DIR}/lib/InteractiveConsoleMenu)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW TRUE
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME}
    ConsoleGraph.cpp
    area.cpp
    area.h
    ImgToAsciiConverter.cpp
    ImgToAsciiConverter.h
    ScreenSettings.cpp
    ScreenSettings.h
    VideoToAscii.cpp
    VideoToAscii.h
    ${PROJECT_SOURCE_DIR}/lib/InteractiveConsoleMenu/Menu.h
    )

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        $<TARGET_FILE:SFML::Graphics>
#        $<TARGET_FILE:SFML::Audio>
#        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
#target_link_libraries(${PROJECT_NAME} SDL3_image::SDL3_image SDL3::SDL3)

target_link_libraries(${PROJECT_NAME} SFML::Graphics SFML::Audio)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# message(STATUS "${CMAKE_PREFIX_PATH}")
# macro(print_all_variables)
#     message(STATUS "print_all_variables------------------------------------------{")
#     get_cmake_property(_variableNames VARIABLES)
#     foreach (_variableName ${_variableNames})
#         message(STATUS "${_variableName}=${${_variableName}}")
#     endforeach()
#     message(STATUS "print_all_variables------------------------------------------}")
# endmacro()
# print_all_variables()

