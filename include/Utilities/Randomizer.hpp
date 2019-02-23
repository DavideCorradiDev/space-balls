#ifndef RANDOMIZER_HPP
#define RANDOMIZER_HPP

#include <random>

namespace mnk {

class Randomizer {
public:
    static int random(int min, int max);
    static float random(float min, float max);

public:
    Randomizer() = delete;

private:
    static std::default_random_engine mGenerator;
};

}

#endif // RANDOMIZER_HPP
