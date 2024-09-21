#include "behavior/complex/random_walk.h"

namespace leo {

namespace flags {

namespace randomwalk {

bool is_allow_rotation(unsigned int state) {
    return flags::is_flag_enabled(state, ALLOW_ROTATION);
}

bool is_skip_initial_direction(unsigned int state) {
    return flags::is_flag_enabled(state, SKIP_INITIAL_DIRECTION);
}

}

}

// TODO: RandomWalk class implementation here...

}