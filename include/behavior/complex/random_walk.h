#ifndef LEO_RANDOM_WALK_H_
#define LEO_RANDOM_WALK_H_

#include "behavior/behavior.h"

namespace leo {

namespace flags {

namespace randomwalk {

// Individual flags
const unsigned int ALLOW_ROTATION = 1;
const unsigned int SKIP_INITIAL_DIRECTION = 1 << 1;

// Composite flags
const unsigned int DEFAULT = ALLOW_ROTATION;

// Polling functions
bool is_allow_rotation(unsigned int state);
bool is_skip_initial_direction(unsigned int state);

}

}

// TODO: define RandomWalk class here...

}

#endif /* LEO_RANDOM_WALK_H_ */