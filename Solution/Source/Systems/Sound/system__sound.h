#pragma once

// not implemented
class SoundEngine
{
public:
    SoundEngine() = default;

    bool             init();
    void             cleanup();

    void             runMusic();
    void             pauseMusic();
    void             stopMusic();

    void             runSound();
    void             pauseSounds();

};