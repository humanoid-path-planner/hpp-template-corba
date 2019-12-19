# Copyright 2011, Florent Lamiraux, CNRS
#
# This file is part of hpp.
# This software is free software: you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of
# the License, or (at your option) any later version.
#
# This software is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Lesser Public License for more details.  You should have
# received a copy of the GNU Lesser General Public License along with
# dynamic-graph. If not, see <http://www.gnu.org/licenses/>.

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(PROJECT_NAME hpp-template-corba)
SET(PROJECT_DESCRIPTION "Template corba server")

INCLUDE(cmake/hpp.cmake)

SET(CUSTOM_HEADER_DIR "hpp/corba/template")

COMPUTE_PROJECT_ARGS(PROJECT_ARGS LANGUAGES CXX)
PROJECT(${PROJECT_NAME} ${PROJECT_ARGS})

# Defines paths.
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Trigger dependency to jrl-mal
ADD_REQUIRED_DEPENDENCY("omniORB4")
OPTION(HPP_CORBA_ENABLE_HPP_UTIL OFF "Use hpp-util to log messages.")
IF(HPP_CORBA_ENABLE_HPP_UTIL)
  ADD_REQUIRED_DEPENDENCY("hpp-util >= 0.4")
ENDIF(HPP_CORBA_ENABLE_HPP_UTIL)

SET(${PROJECT_NAME}_HEADERS
  include/${CUSTOM_HEADER_DIR}/doc.hh
  include/${CUSTOM_HEADER_DIR}/server.hh
  include/${CUSTOM_HEADER_DIR}/server.hxx
)

ADD_LIBRARY(${PROJECT_NAME} SHARED src/server.cc)
PKG_CONFIG_USE_DEPENDENCY(${PROJECT_NAME} omniORB4)
INSTALL(TARGETS ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_LIBDIR})
PKG_CONFIG_APPEND_LIBS(${PROJECT_NAME})

ADD_SUBDIRECTORY(doc)
ADD_SUBDIRECTORY(include)
