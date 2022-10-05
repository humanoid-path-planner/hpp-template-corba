# Copyright 2011, 2020, Florent Lamiraux, Guilhem Saurel, CNRS
#
# This file is part of hpp. This software is free software: you can redistribute
# it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License,
# or (at your option) any later version.
#
# This software is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more
# details.  You should have received a copy of the GNU Lesser General Public
# License along with dynamic-graph. If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME hpp-template-corba)
set(PROJECT_DESCRIPTION "Template corba server")

set(PROJECT_USE_CMAKE_EXPORT TRUE)
set(CUSTOM_HEADER_DIR "hpp/corba/template")

include(cmake/hpp.cmake)
include(cmake/idl.cmake)

compute_project_args(PROJECT_ARGS LANGUAGES CXX)
project(${PROJECT_NAME} ${PROJECT_ARGS})

# Defines paths.
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Trigger dependency to jrl-mal
add_required_dependency("omniORB4")
option(HPP_CORBA_ENABLE_HPP_UTIL OFF "Use hpp-util to log messages.")
if(HPP_CORBA_ENABLE_HPP_UTIL)
  add_project_dependency(hpp-util REQUIRED)
endif(HPP_CORBA_ENABLE_HPP_UTIL)

set(${PROJECT_NAME}_HEADERS
    include/${CUSTOM_HEADER_DIR}/doc.hh include/${CUSTOM_HEADER_DIR}/server.hh
    include/${CUSTOM_HEADER_DIR}/server.hxx)

set(${PROJECT_NAME}_SOURCES src/server.cc)

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES}
                                   ${${PROJECT_NAME}_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:include>)
pkg_config_use_dependency(${PROJECT_NAME} omniORB4)

if(HPP_CORBA_ENABLE_HPP_UTIL)
  target_link_libraries(${PROJECT_NAME} hpp-util::hpp-util)
endif(HPP_CORBA_ENABLE_HPP_UTIL)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${TARGETS_EXPORT_NAME}
  DESTINATION lib)

pkg_config_append_libs(${PROJECT_NAME})

add_subdirectory(doc)
add_subdirectory(include)
add_subdirectory(tests)

install(FILES package.xml DESTINATION share/${PROJECT_NAME})
