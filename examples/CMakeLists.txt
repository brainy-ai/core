add_executable (
  xor
  xor.cpp
)
target_link_libraries (xor brainy)

add_executable (
  mnist
  mnist.cc
)
target_link_libraries (mnist brainy)
