#include "character_2d.h"

namespace leo {

void CharacterBase2D::_ready() {
    // TODO: instantiate mechanics obj here
}

void CharacterBase2D::_physics_process(double delta) {
    // mechanics.update_delta(delta);
    if (behavior_ != nullptr) {
        behavior_->resume();
    }
    // mechanics.process();
}


}