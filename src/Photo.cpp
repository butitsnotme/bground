#include "Photo.h"

#include <cstdlib>
#include <list>
#include <sstream>
#include <vector>

using namespace std;
using namespace Magick;

Photo::Photo(string path) {
  photo.read(path);
  photo.magick("png");
}

Photo::~Photo() {
}

void Photo::resize(int x, int y) {
  stringstream ss;
  ss << x << "x" << y << "^";
  Geometry newSize(ss.str());
  photo.resize(newSize);
}

void Photo::setQuote(string quote) {
  int x_pos, y_pos = 0;
  int maxLength = 0;
  int numLines = 0;
  int ratio = photo.columns() * 9 / 16;
  // Determine the lowest position of the image that will be shown
  int bottom = (ratio < photo.rows() ? ratio : photo.rows());

  stringstream ss(quote);
  string sTmp;

  // Get the approximate size of the rendered text
  while(getline(ss, sTmp, '\n')) {
    if (sTmp.length() > maxLength) {
      maxLength = sTmp.length();
    }
    ++numLines;
  }
  // Calculate the position to draw at based on the above
  x_pos = photo.columns() - (maxLength * 42) - 10; // ~42 pixels per character
  y_pos = bottom - ((numLines * 80) / 2); // ~80 pixels per line

  // Determine whether the image is generally "light" or "dark"
  Image::ImageStatistics *s =
      (Image::ImageStatistics*) malloc(sizeof(Image::ImageStatistics));
  photo.statistics(s);
  const float cutoff = 0.90;
  bool dark = true;
  if (cutoff < s->red.mean &&
      cutoff < s->blue.mean &&
      cutoff < s->green.mean) {
    dark = false;
  }
  dark = true;

  // Draw the text on the image
  list<Magick::Drawable> to_draw;
  to_draw.push_back(DrawableFont(
      "DejaVu Sans Mono",
      StyleType::NormalStyle,
      400,
      StretchType::NormalStretch));
  to_draw.push_back(DrawablePointSize(70));
  to_draw.push_back(DrawableStrokeColor(
      ( dark ? Color("black") : Color("white"))));
  to_draw.push_back(DrawableStrokeWidth(3));
  to_draw.push_back(DrawableFillColor(
      ( dark ? Color("white") : Color("black"))));
  to_draw.push_back(DrawableText(x_pos, y_pos, quote));

  // Apply the draw operations to the image
  photo.draw(to_draw);
}

void Photo::createPhoto() {
  char *home = getenv("HOME");
  string sHome(home);
  string loc = sHome + "/.bground.png";

  photo.write(loc);
}

