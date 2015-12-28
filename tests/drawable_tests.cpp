#include "catch.hpp"
#include "engine/data_structs/drawable.h"
#include "SFML/Graphics.hpp"


TEST_CASE("drawable_tests","[drawable]"){
  SECTION("initialze"){
    sf::Texture text;
    text.loadFromFile("data/textures/texture.png");
    //Drawable t(5,"TEST_DRAWABLE",text,5);

  }

  SECTION("check init"){
    sf::Texture text;
    text.loadFromFile("data/textures/texture.png");
    //Drawable t(5,"TEST_DRAWABLE",text,5);
    //REQUIRE(t.GetLayer() == 5);
  }

  SECTION("change property"){
    sf::Texture text;
    text.loadFromFile("data/textures/texture.png");
    //Drawable t(5,"TEST_DRAWABLE",text,5);
    //t.SetLayer(6);
    //REQUIRE(t.GetLayer() == 6);
  }


}

