#include "Output.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <X11/Xlib.h>

Output::Output() {
  this->maxRes.x = 0;
  this->maxRes.y = 0;

  // Directory containing X11 sockets
  DIR* d = opendir("/tmp/.X11-unix");

  if (NULL != d) {
    struct dirent *dr;
    while(NULL != (dr = readdir(d))) {
      // If the file begins with 'X'
      if ('X' != dr->d_name[0]) {
        continue;
      }

      // Then build the display name
      char display_name[64] = ":";
      // ...Skipping the 'X'
      strcat(display_name, dr->d_name + 1);

      // Open the display
      Display *disp = XOpenDisplay(display_name);
      if (NULL != disp) {
        // Iterate over all the screen to get the maximum size
        int count = XScreenCount(disp);
        this->displays.push_back(display_name); // Also record the name...
        for (int i = 0; i < count; i++) {
          if (this->maxRes.x < XDisplayWidth(disp, i)) {
            this->maxRes.x = XDisplayWidth(disp, i);
          }

          if (this->maxRes.y < XDisplayHeight(disp, i)) {
            this->maxRes.y = XDisplayHeight(disp, i);
          }
        }
        // Don't forget to close the display
        XCloseDisplay(disp);
        disp = NULL;
      }
    }
    // Or the directory when all done
    closedir(d);
  }

  // Set the first display
  this->currentOutput = this->displays.begin();
}

Output::~Output() {
}

Output::Resolution Output::getMaxResolution() {
  return this->maxRes;
}

bool Output::nextOutput() {
  this->currentOutput++;
  if (this->displays.end() == this->currentOutput) {
    return false;
  }
  setenv("DISPLAY", this->currentOutput->c_str(), 1);
  return true;
}
