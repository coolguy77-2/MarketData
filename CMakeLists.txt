cmake_minimum_required(VERSION 3.16)

project (MarketDataProject LANGUAGES "CXX")

set (CMAKE_CXX_STANDARD 20)

add_library(MarketData ${sources})

find_package (Boost REQUIRED)

target_include_directories(MarketData PUBLIC include)

include_directories(${BOOST_INCLUDE_DIRS})

target_link_libraries(MarketData PUBLIC ${Boost_LIBRARIES})

add_subdirectory(src)

target_compile_options(MarketData PRIVATE -Wall PUBLIC -std=gnu++0x)

install(TARGETS MarketData
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)

install(DIRECTORY
	include/ DESTINATION include/MarketData)
