#ifndef LEO_MECHANICS_H_
#define LEO_MECHANICS_H_

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/dictionary.hpp>

#include "character_2d.h"

using namespace godot;

namespace leo {

struct SpawnConfig {
    Ref<Node2D> spawn_scene;
    Vector2 offset;
};

class MechanicsBase : public Object {
public:
    const unsigned short kTransitionSpeed = 80;
    const unsigned short kTransitionDelay = 100;
    
    const float kVelocityFactor = 20.0f;
    const float kRotationalFactor = 0.1f;
    
    const unsigned short kBlockSize = 64;
    const Vector2 kHoldOffset = {40, 0};

protected:
    double delta_;
    float speed_;
    float rotational_speed_;
    
    Vector2 direction_;
    Ref<CharacterBase2D> character_;
    bool movement_allowed_ = true;
    bool rotation_allowed_ = true;
    
    Dictionary collections_; // TODO: what is this?!?
    Ref<Vector2> override_velocity_ = nullptr;
    Ref<float> override_rotation_ = nullptr;

    Ref<SpawnConfig> spawn_node_a_ = nullptr;
    Ref<SpawnConfig> spawn_node_b_ = nullptr;
    Ref<SpawnConfig> spawn_node_c_ = nullptr;
    Ref<SpawnConfig> spawn_node_d_ = nullptr;

    unsigned short screen_transition_progress_ = 0;

    virtual void _handle_damage();
    void _handle_motion();
    void _handle_rotation();
    void _handle_set_position();
    void _handle_spawn();

public:
    MechanicsBase(const Ref<CharacterBase2D>& character, float speed, float rotational_speed = 1.0f);
    void on_item_collection(Ref<Area2D> item);
    virtual void execute_death() = 0;
    
    void override_motion_toward(const Vector2& dest);
    void override_rotation_toward(float dest);

    Vector2 get_target_velocity(const Vector2& target_direction, bool use_delta = false) const;
    Vector2 calculate_motion(const Vector2& target_direction, bool use_delta = false) const;
    Vector2 calculate_direction() const;    // Retrieves normalized direction vector from velocity
    float calculate_rotation() const;
    
    void update_delta(double delta) { delta_ = delta; }
    void process();
};

}

#endif /* LEO_MECHANICS_H_ */