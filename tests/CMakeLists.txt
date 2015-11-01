find_package (Threads REQUIRED)

add_executable(sigmoid Sigmoid.cpp)
target_link_libraries (sigmoid brainy ${GTEST_LIBRARY} ${GTEST_LIBRARY_MAIN} ${CMAKE_THREAD_LIBS_INIT})
add_test(NAME sigmoid COMMAND sigmoid)

add_executable(tanh Tanh.cpp)
target_link_libraries (tanh brainy ${GTEST_LIBRARY} ${GTEST_LIBRARY_MAIN} ${CMAKE_THREAD_LIBS_INIT})
add_test(NAME tanh COMMAND tanh)

add_executable(neuron Neuron.cpp)
target_link_libraries (neuron brainy ${GTEST_LIBRARY} ${GTEST_LIBRARY_MAIN} ${CMAKE_THREAD_LIBS_INIT})
add_test(NAME neuron COMMAND neuron)

add_executable(connection Connection.cpp)
target_link_libraries (connection brainy ${GTEST_LIBRARY} ${GTEST_LIBRARY_MAIN} ${CMAKE_THREAD_LIBS_INIT})
add_test(NAME connection COMMAND connection)
