#include "catch.hpp"
#include "engine/graphics/graphics_engine.h"
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


TEST_CASE("graphics_engine_visuals","visual"){

  SECTION("adding visuals"){
    sf::RenderWindow a(sf::VideoMode(640, 480, 32), "test",sf::Style::Close);
    GraphicsEngine engine(a);
    engine.LoadTexturesDb("core");
    engine.LoadTexture("DUMMY");
    engine.LoadVisuals("core");
    engine.AddVisual("TEST1","DUMMY");
    engine.AddVisual("TEST2","DUMMY");
    engine.AddVisual("TEST3","DUMMY");
    REQUIRE(engine.GetVisualCount() == 3);
  }

}


