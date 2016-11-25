#ifndef FILELIST_H_INCLUDED
#define FILELIST_H_INCLUDED

#include <string>
#include <vector>

class FileList {
public:
  FileList();
  ~FileList();
  void addDirectory(std::string directory);
  void removeDirectory(std::string directory);
  void addAllowableExtension(std::string extension);
  std::string getRandomFile();
private:
  std::vector<std::string> list;
  std::vector<std::string> exts;
};

#endif

