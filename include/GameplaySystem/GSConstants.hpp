#ifndef GSCONSTANTS_HPP
#define GSCONSTANTS_HPP

namespace mnk {

namespace GSConstants {

const unsigned int STARTING_LEVEL = 0;
const unsigned int NUM_OF_LEVELS = 10;
const unsigned int STARTING_LIVES = 3;
const unsigned int MAX_LIVES = 8;
const unsigned int SCORE_SMALL_BALL = 20;
const unsigned int SCORE_MEDIUM_BALL = 8;
const unsigned int SCORE_BIG_BALL = 4;
const unsigned int SCORE_SMART_UFO = 50;
const unsigned int SCORE_DUMB_UFO = 25;
const unsigned int SCORE_TO_NEW_LIFE = 1000;
const unsigned int SPAWN_CELL_SIZE = 100;
const std::size_t NUM_OF_SCORE_ENTRIES = 10;
const std::size_t NUM_OF_CHARS_OF_SCORE_ENTRIES = 6;
const float STARTING_PAUSE_DURATION_SEC = 1.0f;
const float SHIP_TURN_SPEED = 180.0f;
const float SHIP_ACCELERATION = 180.0f;
const float SHIP_RELOAD_TIME = 0.4f;
const float SHIP_BULLET_SPEED = 600.0f;
const float SHIP_CONTACT_RADIUS = 16.0f;
const float SHIP_INVULNERABILITY_TIME_SEC = 2.0f;
const unsigned int MENU_BALLS_BIG = 4;
const unsigned int MENU_BALLS_MEDIUM = 4;
const unsigned int MENU_BALLS_SMALL = 4;

}

}

#endif // GSCONSTANTS_HPP
