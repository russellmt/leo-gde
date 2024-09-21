#include "model/behavior_brain.h"

#include <utility>

namespace leo {

BehaviorBrain::BehaviorBrain(bool use_notion_lifo) {
	if (use_notion_lifo) {
		notion_iterator_ = -1;
	}
}

void BehaviorBrain::append_notion(String&& name, Dictionary&& params) {
    notions_.push_back(
		Notion(
			std::move(name),
			std::move(params)
		)
	);
}

bool BehaviorBrain::_iterator_condition(unsigned int idx) const {
	if (notion_iterator_ > 0) {
		return idx < notions_.size();
	}
	return idx >= 0;
}

bool BehaviorBrain::replace_notion(String&& name, Dictionary&& params) {
	int replace_idx = -1;
	// TODO: maybe make this generator a private method as well?
	unsigned int i = (notion_iterator_ > 0) ? 0 : notions_.size() - 1;
	
	for (; _iterator_condition(i); i += notion_iterator_) {
		auto& notion = notions_[i];
		// TODO: verify whether `==` actually works with strings
		if (notion.get_name() == name) {
			replace_idx = i;
			break;
		}
	}
	
	// NOTE: this doesn't replace at the same index -- is that needed?
	if (replace_idx >= 0) {
		notions_.erase(notions_.begin() + i);
		append_notion(std::move(name), std::move(params));
		return true;
	}
	return false;
}

void BehaviorBrain::clear_all_notions() {
	notions_.clear();
}

void BehaviorBrain::clear_forgotten_notions() {
	for (auto it = notions_.begin(); it != notions_.end();) {
        if (it->is_forgotten()) {
            it = notions_.erase(it);
		} else {
			++it;
		}
    }
}

const Ref<const Notion> BehaviorBrain::peek_notion(const String& name, bool clear) const {
	int found_idx = -1;
	// TODO: figure out how to use godot::Ref -- can it be set to nullptr?
}




    /** 

func find_notion(name: String, clear: bool) -> Notion:
	var found_idx = -1
	var found_notion = null
	for notion in notion_itr:
		if notion.name == name:
			found_notion = notion
			found_idx = notion_itr.current
			break
	
	if found_idx >= 0 and clear:
		notions.remove_at(found_idx)
	
	return found_notion

func find_notion_match(pattern: RegEx, clear: bool) -> Notion:
	var found_idx = -1
	var found_notion = null
	
	# TODO: TEMP - manual iterator process until we figure out why for loop doesn't work
	notion_itr._iter_init()
	while notion_itr.should_continue():
		var notion = notion_itr._iter_get()
		if pattern.search(notion.name):
			found_notion = notion
			found_idx = notion_itr.current
			break
		notion_itr._iter_next()
	
	if found_idx >= 0 and clear:
		notions.remove_at(found_idx)
	
	return found_notion

func enable_notion_lifo():
	notion_itr.reverse = true

func enable_notion_fifo():
	notion_itr.reverse = false
     */



}