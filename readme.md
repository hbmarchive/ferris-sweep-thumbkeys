# Hannah's Thumbkey Ferris Sweep Layout

This is yet another evolution of the first 34-key layout I designed for my
Ferris Sweep. This layout uses the thumb keys for layer switching as well as for
some important non-alphabetic keypresses, leaving the rest of the keyboard free
of complications.

![My Ferris Sweep](https://i.imgur.com/XRqipdX.png)

The four thumbkeys are responsible for `Shift`, `Space`, `Enter` and `Sym` keys
in the base layer. Both `Shift` and `Sym` are one-tap keys, the latter
activating the **Sym Layer**, In addition, holding down `Space` activates the
**Nav Layer** and holding down `Enter` activates the **Num Layer**.

Finally, some thumbkeys are overriden in the other layers so that the following
keypresses work:

* `Enter-Space` (in other words, holding down `Enter` and tapping `Space`)
  produces `Tab`
* `Enter-Shift` produces `Caps Word`
* `Space-Enter` produces `Esc`
* `Space-Sym` activates the **Shortcut Layer**

### Credit

Once again, I want to give credit and a massive amount of thanks to [Ben
Vallack](https://www.youtube.com/benvallack) for talking through his
tap-not-hold approach and for all of his inspirational work on ergonomic
keyboards and layouts. My initial layout drew heavily from his [Ferris Sweep
layout](https://github.com/benvallack/34-QMK-Ferris-Sweep).

The contributers who make QMK possible are an incredible bunch of people and the
ErgoMechKeyboard community as a whole has been welcoming and helpful. Please
support open source projects and communities.

## Layers

### Base Layer

![Base Layer](https://i.imgur.com/LwmRn8r.png)

The base layer is set out in the Colemak Mod-DH format with a `Backspace` key at
the top right-hand side instead of a semicolon key. Holding shift and pressing
the `Backspace` key will produce `Delete`.

In addition to the shortcuts mentioned in the introduction, the bottom row has
home row modifier keys available:

* The `X` / `.` keys produce `Ctrl` when held down
* The `C` / `,` keys produce `Alt` (or `Option`) when held down
* The `D` / `H` keys produce `Win` (or `Cmd` or `Search`) when held down

### Sym Layer

![Sym Layer](https://i.imgur.com/wsbYv9L.png)

This layer contains symbols that have been laid out based on the design of UK
ISO keyboards. The top row has symbols usually found on the number keys. The
symbols that usually appear on the right of the keyboard around the `Enter` key
are on the right side. Braces and brackets are paired off on the left side
alongside `\` and `|`. Finally, the grave and `Caps Lock` are on the far left
underneath `!`.

### Num Layer

![Num Layer](https://i.imgur.com/AhG56m0.png)

This layer contains numbers in a keypad-like layout on the left-hand side of the
keyboard. Function keys are available on the right-hand side.

### Nav Layer

![Nav Layer](https://i.imgur.com/98XJFgm.png)

This layer contains navigation controls on the right-hand side of the keyboard.
Media, volume and brightness controls are available on the left-hand side.

Two keys on the far left change the keyboard's shortcuts to be compatible with
Windows and ChromeOS. On boot, the keyboard will start in Windows-mode by
default.

### Shortcuts Layer

![Shortcuts Layer](https://i.imgur.com/RrJ74hA.png)

This layer contains a number of window and application shortcuts for Windows and
ChromeOS. Windows shortcuts rely on AutoHotKey - I have included a sample script
that can be used to drive them in this repo.
