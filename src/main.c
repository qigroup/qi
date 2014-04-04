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
#include "main.h"

main (int argc, char *argv[])
{
  printf ("Qi %s %s", VERSION, TYPE);
  /* echo the version of Qi */

  GtkWidget *window, *hello;
  
  gtk_init (&argc, &argv);
  
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (window), "delete_event", gtk_main_quit, NULL);
  hello = gtk_label_new ("Qi Group\n歧研发小组\n2014\n");
  gtk_container_set_border_width (GTK_CONTAINER (window), 50);
  gtk_window_set_title (GTK_WINDOW (window), "Qi Group");
  gtk_container_add (GTK_CONTAINER (window), hello);
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_widget_show_all (window);
  gtk_main ();
  
  return 0;
}
