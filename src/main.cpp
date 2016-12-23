#include <cstdlib>
#include <iostream>
#include <sstream>

#include "Database.h"
#include "Output.h"
#include "Info.h"
#include "Photo.h"
#include "args.hxx"
#include "data.h"

using namespace std;

DATA_FILE(program_description)

int main(int argc, char** argv) {

  string prog_name = "bground";
  string description(&program_description_begin);

  args::ArgumentParser p(description);
  args::Flag license(p, "license", "Show the license", {"license"});
  args::Flag help(p, "help", "Output this help text", {'h', "help"});
  args::Flag version(p, "version", "Show the program version", {"version"});
  args::Flag badi(p, "bad image",
      "Add the currently displayed image to the blacklist so that it "
      "will never be shown again", {'b', "bad-image"});
  args::Flag badq(p, "bad quote",
      "Add the currently displayed quote to the blacklist so that it "
      "will never be show again", {'d', "bad-quote"});
  args::Flag updateFlag(p, "update", "Change the image and quote displayed",
      {'u', "update"});
  args::ValueFlag<string> addf(p, "path", "Add a folder of images",
      {'f', "add-images"});
  args::ValueFlag<string> addef(p, "path", "Add a folder to the exception list",
      {'e', "add-images-exception"});
  args::ValueFlag<string> addq(p, "quote", "Add a quote to the database",
      {'q', "add-quote"});
  args::ValueFlag<string> remove(p, "path", "Remove a folder from the database",
      {'r', "remove"});

  Info info(prog_name);

  try {
    p.ParseCLI(argc, argv);
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

  Database d;
  bool update = false;

  if (badi) {
    d.blacklistCurrentImage();
    update = true;
  }

  if (badq) {
    d.deleteCurrentQuote();
    update = true;
  }

  if (addf) {
    d.addFolder(args::get(addf));
  }

  if (addef) {
    d.addFolderException(args::get(addef));
  }

  if (remove) {
    d.removeFolder(args::get(remove));
    update = true;
  }

  if (addq) {
    d.addQuote(args::get(addq));
  }

  if (update || updateFlag) {
    d.update();

    cout << "Image selected: " << d.getImage() << endl;
    cout << "Quote selected: " << d.getQuote() << endl;

    Output disp;
    Output::Resolution maxres = disp.getMaxResolution();

    Photo photo(d.getImage());
    photo.resize(maxres.x, maxres.y);
    photo.setQuote(d.getQuote());
    photo.createPhoto();

    char *home = getenv("HOME");
    string sHome(home);
    string loc = sHome + "/.bground.png";

    do {
      system(("/usr/bin/feh --bg-fill " + loc).c_str());
    } while(disp.nextOutput());
  }

  return 0;

}
