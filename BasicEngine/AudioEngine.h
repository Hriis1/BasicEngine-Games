#pragma once

#include <sdl_mixer/SDL_mixer.h>
#include <string>
#include <map>

namespace BasicEngine {

	class SoundEffect
	{
		//Makes AudioEngine able to access private variables
		friend class AudioEngine;

	private:
		Mix_Chunk* _chunk = nullptr;
	public:
		//loops specifies how many times the sound should loop, -1 will make it loop forever
		void play(int loops = 0);
	};

	class Music
	{
		//Makes AudioEngine able to access private variables
		friend class AudioEngine;

	private:
		Mix_Music* _music = nullptr;
	public:
		//loops specifies how many times the music should play, -1 will make it loop forever
		void play(int loops = 1);

		//Theese apply to the global currently playing music since there can only be 1 music playing
		static void pause();
		static void stop();
		static void resume();
	};

	class AudioEngine
	{
	private:
		bool _isInitialized = false;

		std::map<std::string, Mix_Chunk*> _effectMap;
		std::map<std::string, Mix_Music*> _musicMap;
	public:
		AudioEngine();
		~AudioEngine();

		void init();
		void destroy();

		SoundEffect loadSoundEffect(const std::string& filePath);

		Music loadMusic(const std::string& filePath);
	};
}

