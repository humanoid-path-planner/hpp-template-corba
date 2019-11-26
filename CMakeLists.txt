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

# Defines paths.
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

COMPUTE_PROJECT_ARGS(PROJECT_ARGS LANGUAGES CXX)
PROJECT(${PROJECT_NAME} ${PROJECT_ARGS})

# Trigger dependency to jrl-mal
ADD_REQUIRED_DEPENDENCY("omniORB4")
ADD_REQUIRED_DEPENDENCY("hpp-util >= 0.4")

SET(${PROJECT_NAME}_HEADERS
  include/${CUSTOM_HEADER_DIR}/doc.hh
  include/${CUSTOM_HEADER_DIR}/server.hh
  include/${CUSTOM_HEADER_DIR}/server.hxx
)

ADD_SUBDIRECTORY(doc)
ADD_SUBDIRECTORY(include)
