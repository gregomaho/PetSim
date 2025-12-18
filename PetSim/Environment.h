#pragma once
#include <string>
#include <random>

class Environment {
public:
    enum class Weather { Sunny, Rainy, Windy };
    enum class EventType { None, FoundToy, MinorSickness, Rainstorm, SunnyDay, BirdSong, DragonTantrum };

    Environment();

    Weather getWeather() const;
    void setWeather(Weather w);
    std::string weatherString() const;

    void maybeChangeWeather(int tickCount);
    EventType randomEvent();
    std::string eventString(EventType e) const;

private:
    Weather weather{Weather::Sunny};
    std::mt19937 rng;
};


