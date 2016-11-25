#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <string>

#include "SQLiteCpp/SQLiteCpp.h"

class Database {
public:
  Database();
  ~Database();
  void addQuote(std::string quote);
  void addFolder(std::string folder);
  void addFolderException(std::string folder);
  void removeFolder(std::string folder);
  void deleteCurrentQuote();
  void blacklistCurrentImage();
  void update();
  std::string getImage();
  std::string getQuote();

private:
  SQLite::Database *db;
};

#endif //DATABASE_H_INCLUDED

