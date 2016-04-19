#include "catch.hpp"
#include "engine/input/input_engine.h"

TEST_CASE("input_engine_mouse","[mouse]"){

  SECTION("initialization"){
    sf::RenderWindow window;
    InputEngine input(window);

  }

  SECTION("set and get position"){
    sf::RenderWindow window;
    InputEngine input(window);
    input.SetMouse(10,10);
    REQUIRE(input.GetMouseX() == 10);
    REQUIRE(input.GetMouseY() == 10);
  }


}

