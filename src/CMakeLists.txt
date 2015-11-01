file(GLOB_RECURSE brainy_sources *.cpp)

add_library(brainy SHARED ${brainy_sources})

target_link_libraries(brainy ${JSONCPP_LIBRARY})

install(TARGETS brainy
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
