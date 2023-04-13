set(Sources
  field.cpp
  heliostat.cpp
  facet.cpp
  limbDarkenedSunPointGenerator.cpp
  sunPointGenerator.cpp
  tower.cpp
  utils.cpp)

add_library(cspflux STATIC
  ${Sources})

target_compile_options(cspflux PRIVATE
  -Wall -Wextra -Wpedantic -Werror)
