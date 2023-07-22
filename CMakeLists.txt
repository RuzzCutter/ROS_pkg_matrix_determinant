cmake_minimum_required(VERSION 3.0.2)
project(matrix_determinant)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  message_runtime
  roscpp
  std_msgs
)

add_service_files(
  FILES
  MatrixDeterminant.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES dinogen
  CATKIN_DEPENDS message_generation message_runtime roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ../../devel/include
)

add_executable(matrix_determinant_server src/matrix_determinant_server.cpp)
target_link_libraries(matrix_determinant_server ${catkin_LIBRARIES})
add_dependencies(matrix_determinant_server matrix_determinant_gencpp)