#include <ResourceSystem/MusicPlayer.hpp>
#include <cassert>

namespace mnk {

MusicPlayer::MusicPlayer() :
    mMusic(),
    mFilenames(),
    mVolume(100.f) {}

void MusicPlayer::play(MusicId music) {
    if(mMusic.openFromFile(mFilenames[music])) {
        mMusic.setVolume(mVolume);
        mMusic.setLoop(true);
        mMusic.play();
    }
}

void MusicPlayer::stop() {
    mMusic.stop();
}

void MusicPlayer::pause() {
    mMusic.pause();
}

void MusicPlayer::play() {
    mMusic.play();
}

void MusicPlayer::setVolume(float volume) {
    mVolume = volume;
}

void MusicPlayer::load(MusicId id, const std::string& filename) {
    assert(mFilenames.find(id) == mFilenames.end());
    mFilenames.insert(std::make_pair(id, filename));
}

}
