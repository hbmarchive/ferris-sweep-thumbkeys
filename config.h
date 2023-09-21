/*
Copyright 2020 Pierre Chevalier <pierrechevalier83@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Enable inertia mouse
#define MOUSEKEY_INERTIA

#define MOUSEKEY_DELAY 100
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MAX_SPEED 30
#define MOUSEKEY_TIME_TO_MAX 40
#define MOUSEKEY_FRICTION 21
#define MOUSEKEY_MOVE_DELTA 1

#define MOUSEKEY_WHEEL_DELAY 100
#define MOUSEKEY_WHEEL_INTERVAL 80
#define MOUSEKEY_WHEEL_MAX_SPEED 6
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

// Default tapping term
#define TAPPING_TERM 190
#define PERMISSIVE_HOLD
#define TAPPING_TERM_PER_KEY

// Tapping term for the homerow mod keys
#define TAPPING_TERM_MODS 700
