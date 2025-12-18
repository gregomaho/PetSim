#include "Environment.h"

Environment::Environment() : rng(std::random_device{}()) {}

Environment::Weather Environment::getWeather() const {
    return weather;
}

void Environment::setWeather(Weather w) {
    weather = w;
}

std::string Environment::weatherString() const {
    switch (weather) {
        case Weather::Sunny: return "Sunny";
        case Weather::Rainy: return "Rainy";
        case Weather::Windy: return "Windy";
    }
    return "Unknown";
}

void Environment::maybeChangeWeather(int tickCount) {
    if (tickCount % 4 != 0) return;
    std::uniform_int_distribution<int> d(0, 2);
    weather = static_cast<Weather>(d(rng));
}

Environment::EventType Environment::randomEvent() {
    std::uniform_int_distribution<int> d(1, 100);
    int roll = d(rng);

    if (roll <= 35) return EventType::None;
    if (roll <= 50) return EventType::FoundToy;
    if (roll <= 62) return EventType::MinorSickness;
    if (roll <= 74) return EventType::Rainstorm;
    if (roll <= 86) return EventType::SunnyDay;
    if (roll <= 93) return EventType::BirdSong;
    return EventType::DragonTantrum;
}

std::string Environment::eventString(EventType e) const {
    switch (e) {
        case EventType::None: return "No special event happened.";
        case EventType::FoundToy: return "A pet found a toy!";
        case EventType::MinorSickness: return "Someone is feeling a little sick.";
        case EventType::Rainstorm: return "A rainstorm made the ecosystem gloomy.";
        case EventType::SunnyDay: return "A sunny day lifted everyone's mood.";
        case EventType::BirdSong: return "The bird started singing and cheered others up.";
        case EventType::DragonTantrum: return "The dragon had a tantrum and stressed everyone out.";
    }
    return "Unknown event.";
}
