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

#include <glib/gi18n.h>

#include "cc-keyboard-query.h"
#include "cc-key-row.h"

typedef struct
{
  // CcKeyboardDetector *detector;

  const char *press_string;
  const char *present_string;

  GtkWidget *vbox;
  GtkWidget *heading;
  GtkWidget *keyrow;
  GtkWidget *buttons;
} CcKeyboardQueryPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CcKeyboardQuery, cc_keyboard_query, GTK_TYPE_DIALOG);

enum {
  LAYOUT_RESULT,
  N_SIGNALS,
};

static unsigned cc_keyboard_query_signals[N_SIGNALS] = { 0, };

static void
have_key (GtkButton *button, gpointer data)
{

}

static void
no_have_key (GtkButton *button, gpointer data)
{

}

static void
key_press_event (GtkWidget *widget, GdkEvent *event, gpointer data)
{

}

static void
cc_keyboard_query_constructed (GObject *object)
{
  CcKeyboardQuery *self = CC_KEYBOARD_QUERY (object);
  CcKeyboardQueryPrivate *priv = cc_keyboard_query_get_instance_private (self);

  priv->keyrow = cc_key_row_new ();
  gtk_box_pack_start (GTK_BOX (priv->vbox), priv->keyrow, FALSE, TRUE, 0);
  gtk_box_reorder_child (GTK_BOX (priv->vbox), priv->keyrow, 1);

  g_printerr("in constructed\n");

  gtk_widget_hide (priv->buttons);
}

static void
cc_keyboard_query_finalize (GObject *object)
{
  G_OBJECT_CLASS (cc_keyboard_query_parent_class)->finalize (object);
}

static void
cc_keyboard_query_class_init (CcKeyboardQueryClass *klass)
{
  cc_keyboard_query_signals[LAYOUT_RESULT] =
    g_signal_new ("layout-result", CC_TYPE_KEYBOARD_QUERY, G_SIGNAL_RUN_FIRST,
                  0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE,
                  1, G_TYPE_STRING);

  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  object_class->constructed = cc_keyboard_query_constructed;
  object_class->finalize = cc_keyboard_query_finalize;

  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  gtk_widget_class_set_template_from_resource (widget_class,
                                               "/org/gnome/initial-setup/keyboard-detector.ui");
  gtk_widget_class_bind_template_child_private (widget_class, CcKeyboardQuery, vbox);
  gtk_widget_class_bind_template_child_private (widget_class, CcKeyboardQuery, heading);
  gtk_widget_class_bind_template_child_private (widget_class, CcKeyboardQuery, buttons);
  gtk_widget_class_bind_template_callback (widget_class, have_key);
  gtk_widget_class_bind_template_callback (widget_class, no_have_key);
  gtk_widget_class_bind_template_callback (widget_class, key_press_event);
}

static void
cc_keyboard_query_init (CcKeyboardQuery *self)
{
  CcKeyboardQueryPrivate *priv = cc_keyboard_query_get_instance_private (self);

  gtk_widget_init_template (GTK_WIDGET (self));

  priv->press_string = _("Please press one of the following keys:");
  priv->present_string = _("Is the following key present on your keyboard?");
}

GtkWidget *
cc_keyboard_query_new (GtkWindow    *main_window,
                       gpointer      xkb_info,
                       gpointer      ibus_engines)
{
  GtkWidget *window;
  window = GTK_WIDGET (g_object_new (CC_TYPE_KEYBOARD_QUERY, NULL));
  gtk_window_set_transient_for (GTK_WINDOW (window), main_window);
  return window;
}
