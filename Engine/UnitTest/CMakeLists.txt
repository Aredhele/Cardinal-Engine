# Copyright (C) 2018-2019 Cardinal Engine
# Vincent STEHLY--CALISTO, vincentstehly@hotmail.fr

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# he Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

INCLUDE_DIRECTORIES(
        ${DISPARITY_GTEST_INC_DIR}
        ${DISPARITY_GMOCK_INC_DIR}
        ${DISPARITY_INCLUDE_DIR})

LINK_DIRECTORIES(
        ${DISPARITY_LIB_DIR})

ADD_SUBDIRECTORY(SandBox)
ADD_SUBDIRECTORY(SDL)
