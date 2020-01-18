cmake_minimum_required(VERSION 3.10)
project(project)

include_directories(../include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)

#library lib paths
link_directories(
	C:/Libraries/curl/lib
	C:/Libraries/curlpp/lib	
)
#library include paths
include_directories(
	C:/Libraries/curl/include
	C:/Libraries/curlpp/include
)

add_executable(project
	../src/main.cpp
)

#User libs
set(LIBRARIES
	color
	input
	menu
	riot
	json
	account
	console
)	

#Other libs
set(POST_LINK_LIBRARIES
	curl
	curlpp
)


# Link user libraries
foreach(LIBRARY ${LIBRARIES})
	add_library(${LIBRARY} OBJECT ../src/${LIBRARY}.cpp)
	target_compile_options(${LIBRARY} PUBLIC -g )
	target_link_libraries(project ${LIBRARY})
endforeach()

# Link mandatory libraries
foreach(LIBRARY ${POST_LINK_LIBRARIES})
	target_link_libraries(project ${LIBRARY})
endforeach()