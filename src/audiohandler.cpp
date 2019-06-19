#include "../headers/audiohandler.h"

AudioHandler::AudioHandler() {
    clickBuf.loadFromFile("assets/click.wav");
    mineBuf.loadFromFile("assets/mine.wav");
    clickSound.setBuffer(clickBuf);
    mineSound.setBuffer(mineBuf);
    clickSound.setVolume(30);
    mineSound.setVolume(30);
}

void AudioHandler::playClick() {
    clickSound.play();
}

void AudioHandler::playMine() {
    mineSound.play();
}
