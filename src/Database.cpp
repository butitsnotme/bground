#include "Database.h"

#include <cstdlib>

#include "FileList.h"

using namespace std;

Database::Database() {
  char *home = getenv("HOME");
  string sHome(home);
  string loc = sHome + "/.bground";
  this->db = new SQLite::Database(loc, SQLite::OPEN_READWRITE);
}

Database::~Database() {
  delete db;
}

void Database::addQuote(string quote) {
  SQLite::Statement query(*db,
    "INSERT OR IGNORE INTO quotes (Quote) VALUES(?)");
  query.bind(1, quote);
  query.exec();
}

void Database::addFolder(string folder) {
  SQLite::Statement query(*db,
    "INSERT OR REPLACE INTO directories (Folder) VALUES(?)");
  query.bind(1, folder);
  query.exec();
}

void Database::addFolderException(string folder) {
  SQLite::Statement query(*db,
    "INSERT OR REPLACE INTO directories (Folder, Type) VALUES(?, ?)");
  query.bind(1, folder);
  query.bind(2, "exclude");
  query.exec();
}

void Database::removeFolder(string folder) {
  SQLite::Statement query(*db, "DELETE FROM directories WHERE Folder = ?");
  query.bind(1, folder);
  query.exec();
}

void Database::deleteCurrentQuote() {
  SQLite::Statement query(*db,
    "DELETE FROM quotes WHERE rowid = (SELECT Value FROM preferences "
    "WHERE Key = ? LIMIT 1)");
  query.bind(1, "CurrentQuote");
  query.exec();
}

void Database::blacklistCurrentImage() {
  SQLite::Statement query(*db,
    "INSERT OR IGNORE INTO blacklist (Image) VALUES ((SELECT Value FROM "
    "Preferences WHERE Key = ? LIMIT 1))");
  query.bind(1, "CurrentImage");
  query.exec();
}

void Database::update() {
  // Update quote
  SQLite::Statement qQuery(*db,
    "INSERT OR REPLACE INTO preferences (Key, Value) VALUES (?, (SELECT rowid "
    "FROM quotes ORDER BY RANDOM() LIMIT 1))");
  qQuery.bind(1, "CurrentQuote");
  qQuery.exec();

  // Update image
  FileList fl;
  SQLite::Statement dQuery(*db,
    "SELECT Folder, Type FROM directories ORDER BY rowid");
  while (dQuery.executeStep()) {
    if ("include" == dQuery.getColumn(1).getString()) {
      fl.addDirectory(dQuery.getColumn(0).getString());
    } else {
      fl.removeDirectory(dQuery.getColumn(0).getString());
    }
  }

  SQLite::Statement eQuery(*db, "SELECT Extension FROM extensions");
  while (eQuery.executeStep()) {
    fl.addAllowableExtension(eQuery.getColumn(0).getString());
  }

  string image = fl.getRandomFile();
  
  SQLite::Statement iQuery(*db, "INSERT OR REPLACE INTO preferences (Key, "
    "Value) VALUES (?, ?)");
  iQuery.bind(1, "CurrentImage");
  iQuery.bind(2, image);
  iQuery.exec();
}

string Database::getImage() {
  SQLite::Statement query(*db,
    "SELECT Value FROM preferences WHERE Key = ? LIMIT 1");
  query.bind(1, "CurrentImage");
  if (query.executeStep()) {
    string image(query.getColumn(0).getString());
    return image;
  }
  return "";
}

string Database::getQuote() {
  SQLite::Statement query(*db,
    "SELECT Quote FROM quotes WHERE rowid = (SELECT Value FROM preferences "
    "WHERE Key = ? LIMIT 1)");
  query.bind(1, "CurrentQuote");
  if (query.executeStep()) {
    string quote(query.getColumn(0).getString());
    return quote;
  }
  return "";
}

