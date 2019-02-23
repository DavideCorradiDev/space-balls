#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include <Utilities/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>
#include <map>
#include <string>

namespace mnk {

enum class MusicId {
    MainMenu,
    Game,
};

class MusicPlayer : public NonCopyable {
public:
    MusicPlayer();

    void play(MusicId music);
    void stop();
    void pause();
    void play();
    void setVolume(float volume);
    void load(MusicId id, const std::string& filename);

private:
    sf::Music mMusic;
    std::map<MusicId, std::string> mFilenames;
    float mVolume;
};

}

#endif // MUSICPLAYER_HPP
