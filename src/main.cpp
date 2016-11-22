#include <iostream>
#include <sstream>

#include "args.hxx"
#include "Info.h"

using namespace std;

int main(int argc, char** argv) {

  string prog_name = "bg";

  args::ArgumentParser p("This is a skeleton program.");
  args::Flag license(p, "license", "Show the license", {"license"});
  args::HelpFlag help(p, "help", "Display this help text", {'h', "help"});
  args::Flag version(p, "version", "Show the program version", {"version"});

  Info info(prog_name);

  try {
    p.ParseCLI(argc, argv);
  } catch (args::Help) {
    stringstream help;
    help << p;
    info.setHelp(help.str());
    info.showHelp();
    cout << info.display();
    return 0;
  } catch (args::ParseError e) {
    cerr << e.what() << endl;
    stringstream help;
    help << p;
    info.setHelp(help.str());
    info.showHelp();
    cerr << info.display();
    return 1;
  }

  bool display = false;
  if (license) {
    info.showLicense();
    display = true;
  }
  if (help) {
    stringstream help;
    help << p;
    info.setHelp(help.str());
    info.showHelp();
    display = true;
  }
  if (version) {
    info.showVersion();
    display = true;
  }
  if (display) {
    cout << info.display();
    return 0;
  }

  return 0;

}
