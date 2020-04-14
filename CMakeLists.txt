# Copyright 2011, 2020, Florent Lamiraux, Guilhem Saurel, CNRS
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

CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

SET(PROJECT_NAME hpp-template-corba)
SET(PROJECT_DESCRIPTION "Template corba server")

SET(PROJECT_USE_CMAKE_EXPORT TRUE)
SET(CUSTOM_HEADER_DIR "hpp/corba/template")

INCLUDE(cmake/hpp.cmake)
INCLUDE(cmake/idl.cmake)

COMPUTE_PROJECT_ARGS(PROJECT_ARGS LANGUAGES CXX)
PROJECT(${PROJECT_NAME} ${PROJECT_ARGS})

# Defines paths.
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Trigger dependency to jrl-mal
ADD_REQUIRED_DEPENDENCY("omniORB4")
OPTION(HPP_CORBA_ENABLE_HPP_UTIL OFF "Use hpp-util to log messages.")
IF(HPP_CORBA_ENABLE_HPP_UTIL)
  ADD_PROJECT_DEPENDENCY(hpp-util REQUIRED)
ENDIF(HPP_CORBA_ENABLE_HPP_UTIL)

SET(${PROJECT_NAME}_HEADERS
  include/${CUSTOM_HEADER_DIR}/doc.hh
  include/${CUSTOM_HEADER_DIR}/server.hh
  include/${CUSTOM_HEADER_DIR}/server.hxx
  )

SET(${PROJECT_NAME}_SOURCES
  src/server.cc
  )

ADD_LIBRARY(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS})
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:include>)
PKG_CONFIG_USE_DEPENDENCY(${PROJECT_NAME} omniORB4)

IF(HPP_CORBA_ENABLE_HPP_UTIL)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} hpp-util::hpp-util)
ENDIF(HPP_CORBA_ENABLE_HPP_UTIL)

INSTALL(TARGETS ${PROJECT_NAME} EXPORT ${TARGETS_EXPORT_NAME} DESTINATION lib)

PKG_CONFIG_APPEND_LIBS(${PROJECT_NAME})

ADD_SUBDIRECTORY(doc)
ADD_SUBDIRECTORY(include)
ADD_SUBDIRECTORY(tests)
