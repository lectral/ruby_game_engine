#include "catch.hpp"
#include "engine/sound_engine.h"
#include "easylogging++.h"


INITIALIZE_EASYLOGGINGPP


#define DUMMY_MUSIC_NAME "MUSIC_DUMMY"
#define DUMMY_SOUND_NAME "SOUND_DUMMY"

TEST_CASE( "sound_engine_music", "[music]" ) {

//     SECTION( "initialization" ) {
//         SoundEngine sound_engine;
//     }

//     SECTION( "change music and sound volume" ) {
//         SoundEngine sound_engine;
//         sound_engine.SetMusicVolume(30);
//         sound_engine.SetSoundVolume(10);
//         REQUIRE( sound_engine.GetMusicVolume() == 30 );
//         REQUIRE( sound_engine.GetSoundVolume() == 10 );
//     }

//     SECTION( "loads sound file "){
//         SoundEngine sound_engine;
//         sound_engine.LoadMusicFiles("core");
//         REQUIRE(sound_engine.GetLoadedMusicFiles().empty() != true);
//     }

//     SECTION( "adds music to queue"){
//         SoundEngine sound_engine;
//         sound_engine.LoadMusicFiles("core");
//         sound_engine.AddMusicToQueue(DUMMY_MUSIC_NAME);
//         REQUIRE(sound_engine.GetMusicQueue().front().GetName() ==  DUMMY_MUSIC_NAME);
//     }
    
//     SECTION( "plays music"){
//         SoundEngine sound_engine;
//         sound_engine.LoadMusicFiles("core");
//         sound_engine.AddMusicToQueue(DUMMY_MUSIC_NAME);
//         sound_engine.PlayMusic();
//         REQUIRE(sound_engine.IsMusicPaused() ==  false);
//     }


//     SECTION("plays music continusly"){
//         SoundEngine sound_engine;
//         sound_engine.LoadMusicFiles("core");
//         sound_engine.AddMusicToQueue(DUMMY_MUSIC_NAME);
//         sound_engine.AddMusicToQueue(DUMMY_MUSIC_NAME);
//         REQUIRE(sound_engine.IsQueueEmpty() == false);
//         while(true){
//             sound_engine.Update();
//             if(sound_engine.IsQueueEmpty()){
//                 break;
//             }
//         }

//         REQUIRE(sound_engine.IsQueueEmpty() == true);
//     }


//     SECTION("plays music continusly"){
//         SoundEngine sound_engine;
//         sound_engine.LoadMusicFiles("core");
//         sound_engine.AddMusicToQueue(DUMMY_MUSIC_NAME);
//         sound_engine.AddMusicToQueue(DUMMY_MUSIC_NAME);
//         REQUIRE(sound_engine.IsQueueEmpty() == false);
//         while(true){
//             sound_engine.Update();
//             if(sound_engine.IsQueueEmpty()){
//                 break;
//             }
//         }

//         REQUIRE(sound_engine.IsQueueEmpty() == true);
//     }

//     SECTION("add not existing file"){
//         SoundEngine sound_engine;
//         REQUIRE_THROWS(sound_engine.AddMusicToQueue(DUMMY_MUSIC_NAME));
//         //sound_engine.PlayMusic();
//     }
// }


// TEST_CASE( "sound_engine_sounds", "[sounds]" ) {
//     SECTION("loads ssounds") {
//         SoundEngine sound_engine;
//         sound_engine.LoadSoundFiles("core");
//         REQUIRE(sound_engine.GetLoadedSoundFiles().empty() == false);
//     }

//     SECTION("plays sounds") {
//         SoundEngine sound_engine;
//         sound_engine.LoadSoundFiles("core");
//         sound_engine.PlaySound(DUMMY_SOUND_NAME);
//         sf::sleep(sf::seconds(2));
//     }


}