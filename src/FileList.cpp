#include "FileList.h"

#include <cstdio>
#include <cstdlib>
#include <experimental/filesystem>
#include <iostream>
#include <random>

using namespace std;
using namespace experimental::filesystem;

FileList::FileList() {
}

FileList::~FileList() {
}

void FileList::addDirectory(string directory) {
  for (auto i: recursive_directory_iterator(directory)) {
    list.push_back(i.path().string());
  }
}

void FileList::removeDirectory(string directory) {
  int len = directory.length();
  auto i = list.begin();
  while (i != list.end()) {
    if (0 == i->compare(0, len, directory, 0, len)) {
      i = list.erase(i);
    } else {
      ++i;
    }
  }
}

void FileList::addAllowableExtension(string extension) {
  exts.push_back(extension);
}

string FileList::getRandomFile() {
  vector<string> tmp;
  for (auto& ext: exts) {
    auto file = list.begin();
    while (file != list.end()) {
      if (file->substr(file->length() - ext.length()) == ext) {
        tmp.push_back(*file);
        file = list.erase(file);
      } else {
        ++file;
      }
    }
  }
  list = move(tmp);

  random_device r;
  int len = list.size();
  int item = r() % len;
  return list.at(item);
}

