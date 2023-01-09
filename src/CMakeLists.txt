include_directories(${PROJECT_SOURCE_DIR}/lib/SFML-2.5.1/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/InteractiveConsoleMenu)

# cmake_policy(SET CMP0074 OLD)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML REQUIRED COMPONENTS system window graphics audio)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

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
    
target_link_libraries(${PROJECT_NAME} sfml-graphics)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/lib/SFML-2.5.1/lib/cmake/SFML)

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

