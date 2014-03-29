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
#include "common.h"

struct point
{
  int x;
  int y;
};

struct open_node                /* the point to compare and explore next time */
{
  struct point x;
  long f;
  struct close_node *previous;   /* from which point */
  struct open_node 
    *f_nbigger,
    *f_bigger,
    *name_nbigger,
    *name_bigger;                /* nbigger = not bigger */
};

struct close_node
{
  struct point x;
  struct close_node
    *f_nbigger,
    *f_bigger,
    *name_nbigger,
    *name_bigger;
};

#define OPEN_BUFFER_SIZE (64 * sizeof (struct open_node))
#define CLOSE_BUFFER_SIZE (64 * sizeof (struct close_node))
