#ifndef INFO_H_INCLUDED
#define INFO_H_INCLUDED

#include <string>

class Info {
public:
  Info(std::string progName);
  ~Info();

  void setHelp(std::string help);
  void showHelp();
  void showVersion();
  void showLicense();

  std::string display();
private:
  bool help = false;
  bool version = false;
  bool license = false;
  std::string progName;
  std::string helpText;
  bool helpIsSet = false;
};

#endif //INFO_H_INCLUDED
