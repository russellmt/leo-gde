#include "model/notion.h"

namespace leo {

/**
 * 	func get_mappings_match(brain):
		var found_result = []
		for mapping in mappings:
			var notion_match = brain.find_notion_match(mapping.pattern)
			if notion_match:
				found_result[0] = notion_match
				found_result[1] = mapping.value
				break
		
		return found_result
 */

Notion::Notion(const String& name, const Dictionary& params):
        name_(name),
        params_(params) {}

Notion::Notion(String&& name, Dictionary&& params = Dictionary()):
        name_(std::move(name)),
        params_(std::move(params)) {}

NotionMapping::NotionMapping(const String& pattern, const String& value):
        pattern_(RegEx::create_from_string(pattern)),
        value_(value) {}

NotionMapping::NotionMapping(String&& pattern, String&& value):
        pattern_(RegEx::create_from_string(std::move(pattern))),
        value_(std::move(value)) {}

NotionMappings::NotionMappings(godot::Array& notion_mapping_list):
        mappings_(notion_mapping_list) {}

NotionMappingResult NotionMappings::get_mappings_match(BehaviorBrain& brain) {
    Ref<Notion> notion_match = nullptr;
    Ref<Variant> value = nullptr;
    
    for (const auto& mapping : mappings_) {
        auto* notion_match = brain.find_notion_match(mapping.get_pattern());
        
        if (notion_match != nullptr) {
            value = &mapping.get_value();
            break; 
        }
    }
    return {notion_match, value};
}

}