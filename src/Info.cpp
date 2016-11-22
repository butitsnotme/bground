#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

#include "Info.h"
#include "data.h"

using namespace std;

DATA_FILE(license)
DATA_FILE(version)
DATA_FILE(version_temp)

Info::Info(string progName) {
  this->progName = progName;
}

Info::~Info() {
}

void Info::setHelp(string help) {
  this->helpText = help;
  this->helpIsSet = true;
}

void Info::showHelp() {
  this->help = true;
}

void Info::showVersion() {
  this->version = true;
}

void Info::showLicense() {
  this->license = true;
}

string Info::display() {
  stringstream ss;
  if (this->help) {
    ss << this->helpText << flush;
  }

  if (this->version) {
    // Change the version information file into an array
    string version(&version_begin);
    stringstream ssVersion(version);
    vector<string> vVersion;
    string line;
    while(getline(ssVersion, line)) {
      vVersion.push_back(line);
    }

    // Select the template
    version = &version_temp_begin;

    // Fill in the template
    version = regex_replace(version, regex("<PROG_NAME>"), this->progName);
    version = regex_replace(version, regex("<VERSION>"), vVersion.at(0));
#ifdef DEVELOPMENT_BUILD
    version = regex_replace(version, regex("<GIT_HASH>"), vVersion.at(1));
    version = regex_replace(version, regex("<GIT_BRANCH>"), vVersion.at(2));
    version = regex_replace(version, regex("<BUILDER>"), vVersion.at(3));
    version = regex_replace(version, regex("<DATE>"), vVersion.at(4));
#endif

    ss << version << flush;
  }

  if (this->license) {
    char* license = &license_begin;
    ss << license << flush;
  }
  
  return ss.str();
}
