#pragma once

namespace GameEnums
{
	enum class ItemType
	{
		ITEM_EMPTY,
		ITEM_ARMOR,
		ITEM_WEAPON,
		ITEM_RING,
		ITEM_POTION,
		ITEM_SOLDOUT
	};

	enum class Location
	{
		LOCATION_SHOP = 1,
		LOCATION_MAP,
		LOCATION_INVENTORY
	};

	enum class Job
	{
		WARRIOR,
		WHITEMAGE,
		BLACKMAGE
	};

	enum class Skill
	{
		SWING,
		CURE,
		FIRE,
		THORNS
	};

	enum class Effect
	{
		ATK,
		DEF,
		CRT,
		HP,
		MP
	};
}