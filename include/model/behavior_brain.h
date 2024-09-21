#ifndef LEO_BEHAVIOR_BRAIN_H_
#define LEO_BEHAVIOR_BRAIN_H_

#include "model/notion.h"

#include <vector>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/reg_ex.hpp>

using namespace godot;

namespace leo {

class BehaviorBrain {
private:
    Vector2 will_change_direction_;
    float will_move_ = 0.0f;
    float will_rotate_ = 0.0f;
    
    bool allow_x_ = true;
    bool allow_y_ = true;
    bool will_set_position_ = false;
    Vector2 will_use_vector_;
    
    bool will_spawn_a_ = false;
    bool will_spawn_b_ = false;
    bool will_spawn_c_ = false;
    bool will_spawn_d_ = false;
     
    bool will_transform_screen_ = false;

    std::vector<Notion> notions_;
    short notion_iterator_ = -1;
    bool _iterator_condition(unsigned int idx) const;

public:
    BehaviorBrain(bool use_notion_lifo = false);

    void append_notion(String&& name, Dictionary&& params);
    bool replace_notion(String&& name, Dictionary&& params);
    
    void clear_all_notions();
    void clear_forgotten_notions();
    
    const Ref<const Notion> peek_notion(const String& name) const;
    const Ref<const Notion> peek_notion_match(const String& name) const;
    
    Ref<Notion> consume_notion(const String& name, bool clear = true);
    Ref<Notion> consume_notion_match(Ref<RegEx> pattern, bool clear = true);
    
    void enable_notion_lifo() { notion_iterator_ = -1; }
    void enable_notion_fifo() { notion_iterator_ = 1; }

    Vector2& will_change_direction() { return will_change_direction_; }
    float& will_move() { return will_move_; }
    float& will_rotate() { return will_rotate_; }
    bool& allow_x() { return allow_x_; }
    bool& allow_y() { return allow_y_; }
    bool& will_set_position() { return will_set_position_; }
    Vector2& will_use_vector() { return will_use_vector_; }
    bool& will_spawn_a() { return will_spawn_a_; }
    bool& will_spawn_b() { return will_spawn_b_; }
    bool& will_spawn_c() { return will_spawn_c_; }
    bool& will_spawn_d() { return will_spawn_d_; }
    bool& will_transform_screen() { return will_transform_screen_; }

    const Vector2& get_will_change_direction() const { return will_change_direction_; }
    float get_will_move() const { return will_move_; }
    float get_will_rotate() const { return will_rotate_; }
    bool get_allow_x() const { return allow_x_; }
    bool get_allow_y() const { return allow_y_; }
    bool get_will_set_position() const { return will_set_position_; }
    const Vector2& get_will_use_vector() const { return will_use_vector_; }
    bool get_will_spawn_a() const { return will_spawn_a_; }
    bool get_will_spawn_b() const { return will_spawn_b_; }
    bool get_will_spawn_c() const { return will_spawn_c_; }
    bool get_will_spawn_d() const { return will_spawn_d_; }
    bool get_will_transform_screen() const { return will_transform_screen_; }
};

}

#endif /* LEO_BEHAVIOR_BRAIN_H_ */