#ifndef LEO_BEHAVIOR_H_
#define LEO_BEHAVIOR_H_

#include <godot_cpp/classes/reg_ex.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/ref.hpp>

#include "character_2d.h"
#include "model/behavior_brain.h"

namespace leo {

namespace flags {

const unsigned int NO_FLAGS = 0;

bool is_flag_enabled(unsigned int state, unsigned int flag);

}

class Behavior : public Object {
private:
    static unsigned int s_count_;
    unsigned int id_;
    bool completed_ = false;
    Ref<CharacterBase2D> character_;  // TODO: this shouldn't only be limited to 2D
    Ref<RegEx> interrupt_notion_ = nullptr;

protected:
    virtual void _action() = 0;

public:
    Behavior(Ref<CharacterBase2D> character);
    Behavior(Ref<CharacterBase2D> character, const String& interrupt_notion);
    Behavior(Ref<CharacterBase2D> character, String&& interrupt_notion);

    virtual void restart() { reset(); } // Used to completely start over behavior from the beginning
    virtual void reset() { completed_ = false; }  // Used to start over a current phase of behavior
    
    virtual int get_behavior_counter() const { return 1; }
    virtual int get_behavior_index() const { return 0; }

    void interrupt() { completed_ = true; }
    void resume();
};

}

#endif /* LEO_BEHAVIOR_H_ */