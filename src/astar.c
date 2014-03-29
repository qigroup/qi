/*  
    Copyright 2012-2014 Qi Group
    
    This file is part of Qi.
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "astar.h"

struct open_node *find_smallest_open_node();

struct open_node *astar ()
{
  const struct point increment [4] =
    {
      {1,0},
      {0,1},
      {-1,0},
      {0,-1}
    };
  for(;;)
    {
      struct open_node *explore;
      explore = find_smallest_open_node();

      struct point *point_around;
      int turn;
      for(turn = 0; point_around = get_point_around ((*explore).x); turn++)
        {}}}
