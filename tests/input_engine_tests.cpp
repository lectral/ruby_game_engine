#include "catch.hpp"
#include "engine/input_engine.h"

TEST_CASE("input_engine_mouse","[mouse]"){

  SECTION("initialization"){
    InputEngine input;

  }

  SECTION("set and get position"){
    InputEngine input;
    input.SetMouse(10,10);
    REQUIRE(input.GetMouseX() == 10);
    REQUIRE(input.GetMouseY() == 10);
  }


}

