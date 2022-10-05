# Copyright 2011, Florent Lamiraux, CNRS
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

config_files(hpp/corba/template/debug.hh)
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/hpp/corba/template/debug.hh
  DESTINATION include/hpp/corba/template
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE)
