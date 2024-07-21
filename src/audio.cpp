#include "audio.h"
#include <iostream>

sf::Music music;

void initAudio() {
    if (!music.openFromFile("assets/music2.ogg")) {
        std::cerr << "Error loading music file!" << std::endl;
        exit(1);
    }
    music.setLoop(false);
    music.play();
}
