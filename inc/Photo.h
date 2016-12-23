#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <string>
#include <Magick++.h>

class Photo {
public:
  Photo(std::string path);
  ~Photo();
  void resize(int x, int y);
  void setQuote(std::string quote);
  void createPhoto();
private:
  Magick::Image photo;
};

#endif //IMAGE_H_INCLUDED
