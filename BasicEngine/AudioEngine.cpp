#include "AudioEngine.h"

#include "Errors.h"

namespace BasicEngine {

	void SoundEffect::play(int loops)
	{
		if (Mix_PlayChannel(-1, _chunk, loops) == -1)
		{
			if (Mix_PlayChannel(0, _chunk, loops) == -1)
				fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
		}
	}

	void Music::play(int loops)
	{
		if (Mix_PlayMusic(_music,loops) == -1)
		{
			fatalError("Mix_PlayMusic error: " + std::string(Mix_GetError()));
		}
	}

	void Music::pause()
	{
		Mix_PausedMusic();
	}

	void Music::stop()
	{
		Mix_HaltMusic();
	}

	void Music::resume()
	{
		Mix_ResumeMusic();
	}



	AudioEngine::AudioEngine()
	{

	}

	AudioEngine::~AudioEngine()
	{
		destroy();
	}

	void AudioEngine::init()
	{
		if (_isInitialized)
			fatalError("Tried to init AudioEngine twice");

		//Parametar can be a bitwise combination of MIX_INIT_FAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1)
		{
			fatalError("Mix_Init error: " + std::string(Mix_GetError()));
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		{
			fatalError("Mix_OpenAudio error: " + std::string(Mix_GetError()));
		}

		_isInitialized = true;
	}
	void AudioEngine::destroy()
	{
		if (_isInitialized)
		{
			_isInitialized = false;

			//Free the _effectMap memory
			for (auto& a : _effectMap)
			{
				Mix_FreeChunk(a.second);
			}
			//Free the _musicMap memory
			for (auto& a : _musicMap)
			{
				Mix_FreeMusic(a.second);
			}
			_effectMap.clear();
			_musicMap.clear();

			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath)
	{
		//Try to find the audio in the cache
		auto it = _effectMap.find(filePath);
		SoundEffect effect;
		
		if (it == _effectMap.end())
		{
			//Didnt find the audio
			Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
			//Check for errors
			if (chunk == nullptr)
			{
				fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
			}
			_effectMap[filePath] = chunk;
			effect._chunk = chunk;
		}
		else
		{
			//Its already cached
			effect._chunk = it->second;
		}

		return effect;
	}

	Music AudioEngine::loadMusic(const std::string& filePath)
	{
		//Try to find the audio in the cache
		auto it = _musicMap.find(filePath);
		Music music;

		if (it == _musicMap.end())
		{
			//Didnt find the audio
			Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
			//Check for errors
			if (mixMusic == nullptr)
			{
				fatalError("Mix_LoadMUS error: " + std::string(Mix_GetError()));
			}
			_musicMap[filePath] = mixMusic;
			music._music = mixMusic;
		}
		else
		{
			//Its already cached
			music._music = it->second;
		}

		return music;
	}
}

