#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <SFML/Audio.hpp>

class AudioHandler {
public:
    sf::SoundBuffer clickBuf;
    sf::SoundBuffer mineBuf;
    sf::Sound clickSound;
    sf::Sound mineSound;
    AudioHandler();
    void playClick();
    void playMine();
    friend class GfxHandler;
};

#endif // AUDIOHANDLER_H
