#include "catch.hpp"
#include "engine/strings_manager.h"


TEST_CASE( "strings_manager", "[strings]" ) {

    SECTION( "initialization" ) {
      StringsManager strings;
    }

    SECTION("load string of default lanauge"){
      StringsManager strings;
      strings.LoadStrings("core");
      //std::cout<<strings.GetStringCount();
      REQUIRE(strings.GetStringCount() != 0);
    }

    SECTION("get string"){
      StringsManager strings;
      strings.LoadStrings("core");
      REQUIRE(strings.GetString("DUMMY") == "Hey! Dummy!");
    }

    SECTION("string not defined"){
      StringsManager strings;
      strings.LoadStrings("core");
      REQUIRE(strings.GetString("HEHE_NOPE") == "<NO_STRING>");
    }

    SECTION("change language"){
      StringsManager strings;
      strings.ChangeLanguage("fr");
      strings.LoadStrings("core");
      REQUIRE(strings.GetString("DUMMY") == "[french] Hey! Dummy!");

    }

    SECTION("change language after loading another one"){
      StringsManager strings;
      strings.LoadStrings("core"); //loading default language
      strings.ChangeLanguage("fr");
      strings.LoadStrings("core");
      REQUIRE(strings.GetString("DUMMY") == "[french] Hey! Dummy!");

    }

    SECTION("clear strings"){

      StringsManager strings;
      strings.LoadStrings("core");
      strings.ClearStrings();
      REQUIRE(strings.GetStringCount() == 0);
    }

}

