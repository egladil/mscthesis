cmake_minimum_required (VERSION 2.6) 
project(libpgf+)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES
	${PROJECT_SOURCE_DIR}/src/*.cpp
	${PROJECT_SOURCE_DIR}/src/linearizer/*.cpp
	${PROJECT_SOURCE_DIR}/src/parser/*.cpp
	${PROJECT_SOURCE_DIR}/src/reader/*.cpp
	${PROJECT_SOURCE_DIR}/src/trees/*.C
)

file(GLOB HEADERS
	${PROJECT_SOURCE_DIR}/include/gf/*.h
	${PROJECT_SOURCE_DIR}/include/gf/linearizer/*.h
	${PROJECT_SOURCE_DIR}/include/gf/parser/*.h
	${PROJECT_SOURCE_DIR}/include/gf/reader/*.h
	${PROJECT_SOURCE_DIR}/include/gf/trees/*.H
)

add_library(libpgf+, ${SOURCES} ${HEADERS})

# add_subdirectory(test)
