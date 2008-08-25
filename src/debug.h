/*
 * QMPDClient - An MPD client written in Qt 4.
 * Copyright (C) 2005-2008 Håvard Tautra Knutsen <havtknut@tihlde.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef DEBUG_H
#define DEBUG_H

extern int g_debugLevel;

#define DEBUG(STR, ...) qWarning(STR, ##__VA_ARGS__)
#define DEBUG1(STR, ...) do { if (g_debugLevel > 0) qWarning(STR, ##__VA_ARGS__); } while (0)
#define DEBUG2(STR, ...) do { if (g_debugLevel > 1) qWarning(STR, ##__VA_ARGS__); } while (0)
#define DEBUG3(STR, ...) do { if (g_debugLevel > 2) qWarning(STR, ##__VA_ARGS__); } while (0)
#define DEBUG4(STR, ...) do { if (g_debugLevel > 3) qWarning(STR, ##__VA_ARGS__); } while (0)
#define BTS(A) A ? "true" : "false"

#endif
