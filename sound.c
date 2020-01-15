#include "main.h"

void Init_Sound() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != -1) {
        Music_Background = Mix_LoadMUS("Sounds/Background.mp3");
        Sound_Play = Mix_LoadWAV("Sounds/Play.wav");
        Sound_Food = Mix_LoadWAV("Sounds/Food.wav");
        Sound_Switch = Mix_LoadWAV("Sounds/Switch.wav");
        Sound_Dead = Mix_LoadWAV("Sounds/Dead.wav");
        //        if (!Mix_PlayingMusic())
        Mix_PlayMusic(Music_Background, -1);
    }
    //    Mix_PlayChannel(-1, Sound_Play, 0);
}
