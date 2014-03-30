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

struct open_node *find_smallest_open_node ();
int get_point_around (struct point, struct point *);
int in_close_node (struct point);
int accessible (struct point);
long distance (struct point, struct point);
struct open_node *add_open_node (struct point, struct open_node *, long, long);
void remove_open_node (struct open_node *);

struct open_node *astar (int *map, struct point start, struct point end)
/* find the shortest path from point start to point end on the map */
{
  struct open_node *explore;
  for (; explore = find_smallest_open_node ();)
    /* explore the point in open_node whose estimate is the smallest until reaching point end */
    {
      struct point point_around;
      int turn;

      for (turn = 0; get_point_around ((*explore).p, &point_around); turn ++)
        /* estimate each point around point explore */
        {
          if (in_close_node (point_around))
            continue;
          if (!accessible (point_around))
            continue;
          /* skip the points which are explored or inaccessible */

          long distance, evaluation;
          struct open_node *new_node;
          
          distance = (*explore).distance + 1;
          evaluation = evaluate (point_around, end) + distance;
          
          add_open_node (point_around, explore, distance, evaluation);
          /* add point_around into open_node */
          if (point_around.x == (*explore).p.x && point_around.y == (*explore).p.y)
            /* if point_around is point end, return it and stop astar */
            return new_node;
        }
          
      remove_open_node (explore);
      /* remove point explore from open_node and add it to close_node */
    }
  return NULL;
  /* if no path is found, return NULL */
}
