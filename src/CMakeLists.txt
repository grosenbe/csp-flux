set(Sources field.cpp heliostat.cpp facet.cpp tower.cpp)

add_library(cspflux STATIC
  ${Sources})

target_compile_options(cspflux PRIVATE
  -Wall -Wextra -Wpedantic -Werror)
