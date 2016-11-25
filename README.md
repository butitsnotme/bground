# bground
The purpose of this program is to set the desktop background to a randomly
selected image with a randomly selected quote printed on top.

The program makes use of the Image Magick Magick++ library for the image
manipulation and the `feh` commandline program to set the image. 

## Files
 * `${HOME}/.bground`: Settings for the program, including quotes, directories
   to search and blacklisted images
 * `${HOME}/.bground.png`: The current background image in PNG format
 * `/usr/bin/feh`: The `feh` commandline program

## Usage
`bground` processes a series of directories, either adding images from each or
removing them depending on whether the directory is to be included or excluded.
Additionally, any blacklisted images are removed from the list (if they exist).
Directories are processed in the order that they were added to the database.

### Adding a directory
The following tells `bground` that it should look in the directory
`/home/user/Pictures/` for images.

```bash
bground -f /home/user/Pictures/
```

### Excluding a directory
Similarly, this says that any images found in the directory
`/home/user/Pictures/private/` should be ignored.

```bash
bground -e /home/user/Pictures/private/`
```

### Adding a quote
In order for `bground` to be able to display quotes on the images the quote list
needs to be populated. This can be achieved through commands similar to the
follwing:

```bash
bground -q "Line one of the quote
Line two
Line three
Line four is really long and will cause things to look funny"
```

### Discarding Things
The following command prevents the currently displayed image from ever being
shown again.

```bash
bground -b
```

This command deletes the current quote from the database

```bash
bground -d
```

## License
bground - Sets the desktop background to an image with a quote
Copyright (C) 2016 Dennis Bellinger

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
