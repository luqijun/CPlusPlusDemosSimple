# cmake for OpenCV Cookbook 3rd edition chapter 01
# your opencv/build directory should be in your system PATH

# set minimum required version for cmake
cmake_minimum_required(VERSION 2.8)

project("02_Algorithms")

# 生成可执行文件
# add_executable( 02_Algorithms main.cpp Demo.cpp Demo.h )
# aux_source_directory(${PROJECT_SOURCE_DIR} sourcefiles)
# add_executable( 02_Algorithms ${sourcefiles} )
add_executable( 02_Algorithms_Dijkstra Dijkstra.cpp )
add_executable( 02_Algorithms_NegligenceProposition NegligenceProposition.cpp )
add_executable( 02_Algorithms_SocialTerrorismParty SocialTerrorismParty.cpp )
add_executable( 02_Algorithms_HungaryMatch HungaryMatch.cpp )

# 规定.h头文件路径
include_directories(${PROJECT_SOURCE_DIR})

# link libraries
target_link_libraries( 02_Algorithms ${OpenCV_LIBS})


# output messages
message(STATUS "02_Algorithms Info :")
message(STATUS "    -- PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "    -- PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "    -- sourcefiles: ${sourcefiles}")