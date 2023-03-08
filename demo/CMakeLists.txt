add_executable(cspflux-demo demo.cpp)

target_include_directories(cspflux-demo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(cspflux-demo
  cspflux
  spa
)
