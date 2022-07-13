
add_executable(main_app
  "main.cpp"
  )

#include_directories(
    #"${INCLUDE_BASE}"
    #)

find_package(Boost 1.79 COMPONENTS program_options REQUIRED)

include_directories(
  SYSTEM
  ${INCLUDE_BASE}
  ${Boost_INCLUDE_DIR}
  )

target_link_libraries(main_app PRIVATE tsp Boost::program_options)
