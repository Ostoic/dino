#pragma once

namespace dino::ai
{
	template <class Action>
	float utility(const Action& action);
}

namespace dino::ai
{
	template <class Action>
	float utility(const Action& action)
	{

	}

	// GOAP ideas:
	// goal: collect item "heart of the wild"
	// search item
	// collect hotw would have a goal of CollectDroppedItem resulting in adding "heart of the wild" to the inventory
	// one action: loot window open, loot contains desired item -> CollectDroppedItem -> inventory.append(item)
}