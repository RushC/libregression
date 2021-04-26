file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.h *.c)

add_executable(test ${SOURCES})
target_link_libraries(test PRIVATE regression)

if(Python_Interpreter_FOUND)
    add_custom_target(quadratic-py
        SOURCES
            regression.py
        COMMAND
            ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/regression.py)
endif()