cmake_minimum_required(VERSION 3.10)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set SFML path
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

# Find SFML 2.5.1
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

# Add source files
set(SOURCES
    "Board.cpp"
    "main.cpp"
    "Parts.cpp"
    "Sounds.cpp"
    "UI.cpp"
)

# Add header files
set(HEADERS
    Board.hpp
    Parts.hpp
    Sounds.hpp
    UI.hpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source)
target_include_directories(${PROJECT_NAME} PRIVATE "C:/SFML/include")

# Copy resource files to build directory
set(RESOURCE_FILES
    gameOver.ogg
    line.ogg
    ka1.ttf
    music.wav
    newScore.wav
)

foreach(RESOURCE ${RESOURCE_FILES})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE} ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE} COPYONLY)
endforeach()

# Set the runtime path for SFML DLLs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
file(COPY "C:/SFML/bin/sfml-graphics-2.dll" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "C:/SFML/bin/sfml-audio-2.dll" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "C:/SFML/bin/sfml-system-2.dll" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "C:/SFML/bin/sfml-window-2.dll" DESTINATION ${CMAKE_BINARY_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")