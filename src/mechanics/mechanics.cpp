#include "mechanics/mechanics.h"

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace leo {

MechanicsBase::MechanicsBase(const Ref<CharacterBase2D>& character, float speed, float rotational_speed):
        character_(character),
        speed_(speed),
        rotational_speed_(rotational_speed) {}

void MechanicsBase::on_item_collection(Ref<Area2D> item) {
    // TODO: implement collection logic
}

void MechanicsBase::_handle_damage() {
    auto one_hit_kills = character_->get_tree()->get_nodes_in_group("OneHitKill");
    for (unsigned short i = 0; i < one_hit_kills.size(); i++) {
        Ref<Area2D> area = one_hit_kills[i];  // TODO: do we need a raw ref instead for count below?
        if (area->get_overlapping_bodies().count(character_) > 0) {
            execute_death();
        }
    }
}

void MechanicsBase::override_motion_toward(const Vector2& dest) {
    override_velocity_ = Ref<Vector2>((dest - character_->get_position()) / delta_);
}

void MechanicsBase::override_rotation_toward(float dest) {
    double override1 = fmod(dest - character_->get_rotation(), 2 * M_PI);
    double override2 = fmod(character_->get_rotation() - dest, 2 * M_PI);
    override_rotation_ = Ref<float>((override1 <= override2) ? override1 : override2);
    /** TODO: add print like original GDScript if needed */
}

Vector2 MechanicsBase::get_target_velocity(const Vector2& target_direction, bool use_delta) const {
    Vector2 vel = target_direction * speed_ * character_->get_brain().get_will_move() * kVelocityFactor;
    if (use_delta) {
        vel *= delta_;
    }
    return vel;
}

Vector2 MechanicsBase::calculate_motion(const Vector2& target_direction, bool use_delta) const {
	if (!movement_allowed_) return Vector2(0, 0);
	Vector2 vel = override_velocity_.is_valid() ? 
			*override_velocity_ :
			get_target_velocity(target_direction, use_delta);

    if (!character_->get_brain().get_allow_x()) {
        vel.x = 0;
    }
    if (!character_->get_brain().get_allow_y()) {
        vel.y = 0;
    }
    return vel;
}

float MechanicsBase::calculate_rotation() const {
	if (!rotation_allowed_) return 0.0f;
	return override_rotation_.is_valid() ? 
			*override_rotation_ : 
			rotational_speed_ * character_->get_brain().get_will_rotate();
}

Vector2 MechanicsBase::calculate_direction() const {
	return character_->get_velocity().normalized();
}

void MechanicsBase::_handle_motion() {
	direction_ = character_->get_brain().get_will_change_direction();
	character_->set_velocity(calculate_motion(direction_));
	character_->brain().will_move() = 0;
}

void MechanicsBase::_handle_rotation() {
	float rot = calculate_rotation();
	if (abs(rot) > 0.02f) character_->rotate(rot);
	character_->brain().will_rotate() = 0.0f;
}

void MechanicsBase::_handle_set_position() {
	if (character_->get_brain().get_will_set_position()) {
		character_->set_position(character_->get_brain().get_will_use_vector());
		character_->brain().will_use_vector() = Vector2(0, 0);
		character_->brain().will_set_position() = false;
	}
}

void MechanicsBase::_handle_spawn() {
	if (character_->get_brain().get_will_spawn_a()) {
		auto node = spawn_node_a_->spawn_scene.instantiate();  // TODO: verify this returns Ref<Node>
		node->set_position(node->get_position() + character_->get_position() + spawn_node_a_->offset);
		character_->get_parent()->add_child(node);
	}
	character_->brain().will_spawn_a() = false;
}

void MechanicsBase::process() {
	_handle_rotation();
	_handle_motion();
	_handle_damage();
	_handle_set_position();
	_handle_spawn();
	character_->move_and_slide();

	override_velocity_ = nullptr;
	override_rotation_ = nullptr;
}

}