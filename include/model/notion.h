#ifndef LEO_NOTION_H_
#define LEO_NOTION_H_

#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/dictionary.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/reg_ex.hpp"
#include "godot_cpp/core/object.hpp"

#include "model/behavior_brain.h"

using namespace godot;

namespace leo {

// TODO: do we need to extend godot::Object instead?
class Notion : public Object {
private:
    String name_;
    Dictionary params_;
    bool forgotten_ = false;

public:
    Notion(const String& name, const Dictionary& params = Dictionary());
    Notion(String&& name, Dictionary&& params = Dictionary());

    void forget() { forgotten_ = true; }
    
    const String& get_name() const { return name_; }
    const Dictionary& get_params() const { return params_; }
    bool is_forgotten() const { return forgotten_; }
};

class NotionMapping : public Object {
private:
    Ref<RegEx> pattern_;
    String value_;

public:
    NotionMapping(const String& pattern, const String& value);
    NotionMapping(String&& pattern, String&& value);
    ~NotionMapping() {}

    const Ref<const RegEx> get_pattern() const { return pattern_; }
    const String& get_value() const { return value_; }

};

class NotionMappings {
private:
    Array mappings_;  // TODO: internal array -- convert to std::vector

public:
    NotionMappings(Array& notion_mapping_list);
    NotionMappingResult get_mappings_match(BehaviorBrain& brain);  // Modifies notions in brain - non-const
};

// TODO: determine whether this should be a class : Object instead
struct NotionMappingResult {
    Ref<Notion> match = nullptr;
    Ref<Variant> value = nullptr;

    bool is_valid() const { return match != nullptr; } 
};

}

#endif /* LEO_NOTION_H_ */