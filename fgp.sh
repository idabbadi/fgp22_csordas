#!/bin/bash

example_ass1="./bin/fgp query res/meshes/cow.ply 4 0"
example_ass2="./bin/fgp decimation res/meshes/cow.ply 10"
example_ass3="./bin/fgp smoothing res/meshes/cow_colour.ply 500 0.28"

function build() {
  mkdir -p build
  cd build 
  cmake .. $1
  make --silent
  exit $?
}

function clean() {
  rm -rf build/*
  rm -rf lib/*
  rm -rf bin/fgp bin/test_*
}

function ass1() {
  eval $example_ass1
}

function ass2() {
  eval $example_ass2
}

function ass3() {
  eval $example_ass3
}

function valgrind_ass1() {
  valgrind --leak-check=full --show-leak-kinds=all $example_ass1
}

function valgrind_ass2() {
  valgrind --leak-check=full --show-leak-kinds=all $example_ass2
}

function valgrind_ass3() {
  valgrind --leak-check=full --show-leak-kinds=all $example_ass3
}

function analyze() {
  cppcheck --enable=all --quiet --force \
    --std=c++11 --std=posix \
    --suppress=missingIncludeSystem -ibuild/ src

  cppcheck --check-config --quiet \
    --suppress=missingIncludeSystem -ibuild/ src
}

function format() {
  clang-format -style=LLVM -i src/*.cpp src/*.h src/helper/*.cpp \
    src/helper/*.cpp src/student/*.cpp src/student/*.h
}

case "$1" in
  "build") build $2 ;;
  "clean") clean ;;
  "ass1") ass1 ;;
  "ass2") ass2 ;;
  "ass3") ass3 ;;
  "valgrind_ass1") valgrind_ass1 ;;
  "valgrind_ass2") valgrind_ass2 ;;
  "valgrind_ass3") valgrind_ass3 ;;
  "format") format ;;
  "analyze") analyze ;;
  *)
    echo "Available targets:"
    echo -e "\t- build"
    echo -e "\t- clean"
    echo -e "\t- ass1"
    echo -e "\t- ass2"
    echo -e "\t- ass3"
    echo -e "\t- valgrind_ass1"
    echo -e "\t- valgrind_ass2"
    echo -e "\t- valgrind_ass3"
    echo -e "\t- analyze"
    echo -e "\t- format"
    ;;
esac
