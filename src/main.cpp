#include <iostream>
#include "easylogging++.h"

/* Include the mruby header */
#include <mruby.h>
#include <mruby/compile.h>
#include "app/app.h"

App gApp;

INITIALIZE_EASYLOGGINGPP


#include <SFML/Graphics.hpp>

int main()
{
    mrb_state *mrb = mrb_open();
    FILE* f;
    f = fopen("test.rb", "r");
    mrb_load_file(mrb, f);
    mrb_close(mrb);
    sf::Font a;
    sf::Text b;
    b.setString("dupa1");
    a.loadFromFile("data/core/fonts/OpenSans-Regular.ttf");
    gApp.Run();
    return 0;
}
