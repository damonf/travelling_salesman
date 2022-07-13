#!/bin/bash

set -eu

usage()
{
  echo "usage: $0 [-r|-c|-t|-tt]"
  echo "builds the project"
  echo "where -r = rebuild, -c = generate compile_commands.json, -t = run tests, -tt = run failed tests"
}

compile_commands()
{
  echo "regenerating compile_commands.json"
  cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
  cp compile_commands.json ..
}

full_build()
{
  mkdir build
  cd build
  # build with debugging symbols
  cmake .. -DCMAKE_BUILD_TYPE=Debug 
  cmake --build .
  compile_commands
}

case "$#" in

  0 ) echo "building"
      if [ ! -d build ]; then
        echo "doing full build"
        full_build
      else
        cd build
        cmake --build .
        compile_commands
      fi
      ;;

  1 ) 
      if [ $1 = -r ]; then

        echo "re-building"
        rm -rf build
        full_build

      elif [ $1 = -c ]; then

        cd build
        compile_commands

      elif [ $1 = -t ]; then

        echo "running tests"
        cd build
        ctest

      elif [ $1 = -tt ]; then

        echo "re-running failed tests"
        cd build
        ctest --rerun-failed --output-on-failure 

      else

        usage
        exit 1

      fi
      ;;


  * ) echo "too many args"
      usage
      ;;

esac


