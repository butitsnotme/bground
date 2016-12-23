#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include <string>
#include <vector>

class Output {
public:
  struct Resolution {
    int x;
    int y;
  };
  Output();
  ~Output();

  Resolution getMaxResolution();
  bool nextOutput();
private:
  std::vector<std::string> displays;
  std::vector<std::string>::iterator currentOutput;
  Resolution maxRes;
};

#endif //OUTPUT_H_INCLUDED
