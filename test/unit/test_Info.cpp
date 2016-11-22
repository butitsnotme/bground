#include "catch.hpp"
#include "Info.h"

using namespace std;


SCENARIO( "Information and help system works" ) {
  string prog_name = "skeleton";
  Info* tmpInfo = new Info(prog_name);
  string help_string = "This is the help";
  tmpInfo->setHelp(help_string);
  tmpInfo->showHelp();
  string help = tmpInfo->display();
  delete tmpInfo;
  tmpInfo = new Info(prog_name);
  tmpInfo->showLicense();
  string license = tmpInfo->display();
  delete tmpInfo;
  tmpInfo = new Info(prog_name);
  tmpInfo->showVersion();
  string version = tmpInfo->display();
  delete tmpInfo;
  tmpInfo = NULL;

  Info i(prog_name);
  GIVEN( "A request for help" ) { 

    i.setHelp(help_string);
    i.showHelp();

    WHEN( "The result is retrieved" ) {
      string result = i.display();

      THEN( "The output will be equal to the help file" ) {
        REQUIRE( result == help );
        REQUIRE( result != "" );
      }
    }
  }

  GIVEN( "A request for the version" ) {
    i.showVersion();

    WHEN( "The result is retrieved" ) {
      string result = i.display();

      THEN( "The output will be equal to the version file" ) {
        REQUIRE( result == version );
        REQUIRE( result != "" );
      }
    }
  }

  GIVEN( "A request for the license" ) {
    i.showLicense();

    WHEN( "The result is retrieved" ) {
      string result = i.display();

      THEN( "The output will be equal to the license file" ) {
        REQUIRE( result == license );
        REQUIRE( result != "" );
      }
    }
  }

  GIVEN( "A request for the license and version" ) {
    i.showLicense();
    i.showVersion();

    WHEN( "The result is retrieved" ) {
      string result = i.display();

      THEN( "The output will be equal to the version and license files" ) {
        REQUIRE( result == version + license );
        REQUIRE( result != "" );
      }
    }
  }

  GIVEN( "A request for the help and version" ) {
    i.setHelp(help_string);
    i.showHelp();
    i.showVersion();

    WHEN( "The result is retrieved" ) {
      string result = i.display();

      THEN( "The output will be equal to the help and version files" ) {
        REQUIRE( result == help + version );
        REQUIRE( result != "" );
      }
    }
  }
}
