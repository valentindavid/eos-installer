/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/*
 * Copyright © 2018 Endless Mobile, Inc.
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
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GIS_DMI_H
#define GIS_DMI_H

#include <glib.h>

G_BEGIN_DECLS

gchar *gis_dmi_sanitize_string (const gchar *string);

gboolean gis_dmi_read_vendor_product (gchar  **vendor,
                                      gchar  **product,
                                      GError **error);

G_END_DECLS

#endif /* GIS_DMI_H */
