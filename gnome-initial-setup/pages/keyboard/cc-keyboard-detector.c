/*
 * Copyright (C) 2014 Endless Mobile, Inc.
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

#include <config.h>
//#include <locale.h>
#include <glib/gi18n.h>

#define GNOME_DESKTOP_USE_UNSTABLE_API
#include <libgnome-desktop/gnome-languages.h>

#include <../language/cc-common-language.h>
#include <../language/cc-util.h>
#include "cc-keyboard-detector.h"

#ifdef HAVE_IBUS
#include <ibus.h>
#include "cc-ibus-utils.h"
#endif  /* HAVE_IBUS */

typedef struct {
  /* Not owned */
  GnomeXkbInfo *xkb_info;
  GHashTable *ibus_engines;

  /* Owned */
} CcKeyboardDetectorPrivate;

#define GET_PRIVATE(detector) ((CcKeyboardDetectorPrivate *) g_object_get_data (G_OBJECT (detector), "private"))
#define WID(name) ((GtkWidget *) gtk_builder_get_object (builder, name))

static void
cc_keyboard_detector_private_free (gpointer data)
{
  CcKeyboardDetectorPrivate *priv = data;

  g_free (priv);
}

GtkWidget *
cc_keyboard_detector_new (GtkWindow    *main_window,
                          GnomeXkbInfo *xkb_info,
                          GHashTable   *ibus_engines)
{
  GtkBuilder *builder;
  GtkWidget *detector;
  CcKeyboardDetectorPrivate *priv;
  gint width;
  GError *error = NULL;

  builder = gtk_builder_new ();
  if (gtk_builder_add_from_resource (builder, "/org/gnome/initial-setup/keyboard-detector.ui", &error) == 0)
    {
      g_object_unref (builder);
      g_warning ("failed to load keyboard detector: %s", error->message);
      g_error_free (error);
      return NULL;
    }
  detector = WID ("input-dialog");
  priv = g_new0 (CcKeyboardDetectorPrivate, 1);
  g_object_set_data_full (G_OBJECT (detector), "private", priv, cc_keyboard_detector_private_free);
  g_object_set_data_full (G_OBJECT (detector), "builder", builder, g_object_unref);

  priv->xkb_info = xkb_info;
  priv->ibus_engines = ibus_engines;

  gtk_window_set_transient_for (GTK_WINDOW (detector), main_window);

  return detector;
}

void
cc_keyboard_detector_set_ibus_engines (GtkWidget  *detector,
                                       GHashTable *ibus_engines)
{
#ifdef HAVE_IBUS
  CcKeyboardDetectorPrivate *priv = GET_PRIVATE (detector);

  /* This should only be called once when IBus shows up in case it
     wasn't up yet when the user opened the keyboard detector dialog. */
  g_return_if_fail (priv->ibus_engines == NULL);

  priv->ibus_engines = ibus_engines;
  //get_ibus_locale_infos (detector);
#endif  /* HAVE_IBUS */
}

gboolean
cc_keyboard_detector_get_selected (GtkWidget  *detector,
                                   gchar     **type,
                                   gchar     **id,
                                   gchar     **name)
{
  CcKeyboardDetectorPrivate *priv = GET_PRIVATE (detector);
  GtkWidget *selected;
  const gchar *t, *i, *n;

  //selected = egg_list_box_get_selected_child (EGG_LIST_BOX (priv->list));
  //if (!selected)
  //  return FALSE;

  t = g_object_get_data (G_OBJECT (selected), "type");
  i = g_object_get_data (G_OBJECT (selected), "id");
  n = g_object_get_data (G_OBJECT (selected), "name");

  if (!t || !i || !n)
    return FALSE;

  *type = g_strdup (t);
  *id = g_strdup (i);
  *name = g_strdup (n);

  return TRUE;
}
