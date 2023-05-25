cmake_minimum_required(VERSION 3.25)
project(Lab6_7)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab6_7 main.cpp Headers/Contract.h Contract.cpp Headers/Repo.h Repo.cpp Headers/validator.h validator.cpp Headers/Service.h Service.cpp Headers/console.h console.cpp Headers/VektorTemplate.h)
