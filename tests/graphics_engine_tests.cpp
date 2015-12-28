#include "catch.hpp"
#include "engine/graphics_engine.h"
#include "SFML/Graphics.hpp"
#include "easylogging++.h"



TEST_CASE("graphics_engine_loading","[loading]"){

  SECTION("initialization"){
    sf::RenderWindow a(sf::VideoMode(640, 480, 32), "test",sf::Style::Close);
    GraphicsEngine engine(a);
  }

  SECTION("loading textures"){
    sf::RenderWindow a(sf::VideoMode(640, 480, 32), "test",sf::Style::Close);
    GraphicsEngine engine(a);
    engine.LoadTexturesDb("core");
    engine.LoadTexture("DUMMY");
    REQUIRE(engine.GetTextureCount() == 1);
  }


  SECTION("getting texture"){
    sf::RenderWindow a(sf::VideoMode(640, 480, 32), "test",sf::Style::Close);
    GraphicsEngine engine(a);
    engine.LoadTexturesDb("core");
    engine.LoadTexture("DUMMY");
    REQUIRE(engine.GetTexture("DUMMY").getSize().x > 0);
  }


}


TEST_CASE("graphics_engine_drawbles","[drawables]"){

  SECTION("add drawables"){
    sf::RenderWindow a(sf::VideoMode(640, 480, 32), "test",sf::Style::Close);
    GraphicsEngine engine(a);
    LOG(DEBUG) << "test-1";

    engine.LoadTexturesDb("core");
    engine.LoadTexture("DUMMY");
    engine.LoadVisuals("core");
    engine.AddDrawable("TEST1","DUMMY",2);
    engine.AddDrawable("TEST2","DUMMY",3);
    engine.AddDrawable("TEST3","DUMMY",3);
    REQUIRE(engine.GetDrawableCount() == 3);
  }


  SECTION("change property of drawables"){
    sf::RenderWindow a(sf::VideoMode(640, 480, 32), "test",sf::Style::Close);
    GraphicsEngine engine(a);
    engine.LoadTexturesDb("core");
    engine.LoadTexture("DUMMY");
    engine.LoadVisuals("core");
    engine.AddDrawable("TEST1","DUMMY",2);
    engine.AddDrawable("TEST2","DUMMY",3);
    engine.GetDrawable(0)->SetPosition(10,10);
    REQUIRE(engine.GetDrawable(0)->GetPositionX() == 10);
  }


}


