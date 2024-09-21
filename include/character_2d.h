#ifndef LEO_CHARACTER_2D_H_
#define LEO_CHARACTER_2D_H_

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "behavior.h"
#include "model/behavior_brain.h"

// Definition of PI -- TODO: move to constants or something?
#ifndef M_PI
#define M_PI atan(1) * 4
#endif /* M_PI */

using namespace godot;

namespace leo {

class CharacterBase2D : public CharacterBody2D {
protected:
    // TODO: implement mechanics class

    Ref<Behavior> behavior_;
    BehaviorBrain brain_;

    // TODO: implement onready shape and area child element retrieval
    // TODO: need to override _ready() function the right way
    virtual void _ready() override;
    virtual void _physics_process(double delta) override;

public:
    const float kSpeed = 1.0f;
    const float kRotationalSpeed = 1.0f;

    const BehaviorBrain& get_brain() const { return brain_; }
    BehaviorBrain& brain() { return brain_; }

    const Ref<Behavior>& get_behavior() const { return behavior_; }
};

}

#endif /* LEO_CHARACTER_2D_H_ */