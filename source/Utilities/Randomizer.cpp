#include <Utilities/Randomizer.hpp>
#include <chrono>

namespace mnk {

std::default_random_engine Randomizer::mGenerator(std::chrono::system_clock::now().time_since_epoch().count());

int Randomizer::random(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(mGenerator);
}
float Randomizer::random(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(mGenerator);
}

}
