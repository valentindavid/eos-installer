/*
 * Copyright (C) 2014 Endless Mobile, Inc
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef __GIS_KEYBOARD_DETECTOR_H__
#define __GIS_KEYBOARD_DETECTOR_H__

#include <gtk/gtk.h>

#define GNOME_DESKTOP_USE_UNSTABLE_API
#include <libgnome-desktop/gnome-xkb-info.h>


G_BEGIN_DECLS

GtkWidget   *cc_keyboard_detector_new          (GtkWindow    *parent,
                                                GnomeXkbInfo *xkb_info,
                                                GHashTable   *ibus_engines);
void         cc_keyboard_detector_set_ibus_engines (GtkWidget *detector,
                                                    GHashTable *ibus_engines);
gboolean     cc_keyboard_detector_get_selected (GtkWidget    *detector,
                                                gchar       **type,
                                                gchar       **id,
                                                gchar       **name);

G_END_DECLS

#endif /* __GIS_KEYBOARD_DETECTOR_H__ */
