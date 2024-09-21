#include "behavior/behavior.h"

namespace leo {

namespace flags {

bool is_flag_enabled(unsigned int state, unsigned int flag) {
    return (state & flag == flag);
}

}

unsigned int Behavior::s_count_ = 0;

Behavior::Behavior(Ref<CharacterBase2D> character):
        character_(character),
        id_(s_count_++) {}

Behavior::Behavior(Ref<CharacterBase2D> character, const String& interrupt_notion):
        character_(character),
        id_(s_count_++),
        interrupt_notion_(RegEx::create_from_string(interrupt_notion)) {}

Behavior::Behavior(Ref<CharacterBase2D> character, String&& interrupt_notion):
        character_(character),
        id_(s_count_++),
        interrupt_notion_(RegEx::create_from_string(std::move(interrupt_notion))) {}

void Behavior::resume() {
    auto match = character_->brain().consume_notion_match(interrupt_notion_);
    if (match != nullptr) {
        interrupt();
        return;
    }
    if (!completed_) {
        _action();
    }
}

}