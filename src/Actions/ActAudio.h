#pragma once

#include "Action.h"
#include "Game.h"
#include <string>

class ActAudioPause : public Action
{
private:
	std::string id;

public:
	ActAudioPause(const std::string& id_) : id(id_) {}

	virtual bool execute(Game& game)
	{
		auto song = game.Resources().getSong(id);
		if (song != nullptr)
		{
			song->pause();
		}
		return true;
	}
};

class ActAudioPauseAll : public Action
{
public:
	virtual bool execute(Game& game)
	{
		game.Resources().pauseSongs();
		return true;
	}
};

class ActAudioPlay : public Action
{
private:
	std::string id;
	bool clear;
	bool loop{ false };
	bool hasLoop{ false };

public:
	ActAudioPlay(const std::string& id_, bool clear_)
		: id(id_), clear(clear_) {}

	void setLoop(bool loop_) noexcept
	{
		loop = loop_;
		hasLoop = true;
	}

	virtual bool execute(Game& game)
	{
		if (clear == true)
		{
			game.Resources().stopSongs();
		}
		auto song = game.Resources().getSong(id);
		if (song != nullptr)
		{
			if (hasLoop == true)
			{
				song->setLoop(loop);
#if (SFML_VERSION_MAJOR > 2 || (SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR >= 5))
				auto musicLoop = dynamic_cast<sf::MusicLoops*>(song.get());
				if (musicLoop != nullptr)
				{
					musicLoop->setLoop(loop);
					song->setLoop(true);
				}
#endif
			}
			song->setVolume((float)game.MusicVolume());
			if (song->getStatus() != sf::Music::Playing)
			{
				song->play();
			}
		}
		return true;
	}
};

class ActAudioResumeAll : public Action
{
private:
	bool restart;

public:
	ActAudioResumeAll(bool restart_) noexcept : restart(restart_) {}

	virtual bool execute(Game& game)
	{
		game.Resources().playPaused(restart);
		return true;
	}
};

class ActAudioSeek : public Action
{
private:
	std::string id;
	sf::Time time;

public:
	ActAudioSeek(const std::string& id_, const sf::Time& time_) : id(id_), time(time_) {}

	virtual bool execute(Game& game)
	{
		auto song = game.Resources().getSong(id);
		if (song != nullptr)
		{
			song->setPlayingOffset(time);
		}
		return true;
	}
};

class ActAudioSetVolume : public Action
{
private:
	std::string id;
	Variable volume;

public:
	ActAudioSetVolume(const std::string& id_, const Variable& volume_)
		: id(id_), volume(volume_) {}

	virtual bool execute(Game& game)
	{
		auto song = game.Resources().getSong(id);
		if (song != nullptr)
		{
			auto vol = game.getVarOrProp<int64_t, unsigned>(volume, game.MusicVolume());
			if (vol > 100)
			{
				vol = 100;
			}
			song->setVolume((float)vol);
		}
		return true;
	}
};

class ActAudioStop : public Action
{
private:
	std::string id;

public:
	ActAudioStop(const std::string& id_) : id(id_) {}

	virtual bool execute(Game& game)
	{
		auto song = game.Resources().getSong(id);
		if (song != nullptr)
		{
			song->stop();
		}
		return true;
	}
};

class ActAudioStopAll : public Action
{
public:
	virtual bool execute(Game& game)
	{
		game.Resources().stopSongs();
		return true;
	}
};
