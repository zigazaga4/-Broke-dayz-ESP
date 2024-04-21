#pragma once

namespace offsets
{
	constexpr auto anim_system = 0xE24A18;

	namespace world {
		constexpr auto world = 0x414CF70;
		constexpr auto near_entity_table = 0x0F48;
		constexpr auto near_entity_table_size = near_entity_table + 0x8;

		constexpr auto far_entity_table = 0x1090;
		constexpr auto far_entity_table_size = far_entity_table + 0x8;

		constexpr auto slow_entity_table = 0x2010;
		constexpr auto slow_entity_table_size = slow_entity_table + 0x8;
		constexpr auto slow_entity_table_count = slow_entity_table_size + 0x8;

		constexpr auto bullet_table = 0xE00;
		constexpr auto bullet_table_size = bullet_table + 0x8;

		constexpr auto item_table = 0x2060;
		constexpr auto item_table_size = item_table + 0x8;

		constexpr auto camera = 0x1B8;
		constexpr auto base_entity = 0x28E0;
	}

	namespace network_manager
	{
		constexpr auto networkManager = 0xEF9140;
		constexpr auto network_client = 0x50;
	}

	namespace network_client
	{
		constexpr auto scoreboard = 0x18;
		constexpr auto scoreboard_count = 0x24;
	}

	namespace scoreboard
	{
		constexpr auto player_identities = 0x0;
	}

	namespace player_identity
	{
		constexpr auto network_id = 0x30;
		constexpr auto player_name = 0xF0;
	}

	namespace camera
	{
		constexpr auto inverted_view_right = 0x8;
		constexpr auto inverted_view_up = 0x14;
		constexpr auto inverted_view_forward = 0x20;
		constexpr auto inverted_view_translation = 0x2C;
		constexpr auto viewportsize = 0x58;
		constexpr auto get_projection_d1 = 0xD0;
		constexpr auto get_projection_d2 = 0xDC;
		constexpr auto cameraon = 0x2B30;
	}

	namespace entity
	{
		constexpr auto visual_state = 0x1D0;
		constexpr auto inventory = 0x678;
		constexpr auto network_id = 0x6FC;
		constexpr auto entity_type = 0x180;
		constexpr auto is_dead = 0xE2;
		constexpr auto player_skeleton = 0x830;
		constexpr auto zombie_skeleton = 0x698;
	}

	namespace skeleton
	{
		constexpr auto anim_class = 0x98;
	}

	namespace anim_class
	{
		constexpr auto matrixes = 0xBF0;
	}

	namespace entity_type
	{
		constexpr auto config_name = 0xA8;
		constexpr auto clean_name = 0x4E8;
		constexpr auto model_name = 0x88;
	}

	namespace visual_state
	{
		constexpr auto matrix = 0x1D0;
		constexpr auto position = 0x2C;
	}

	namespace inventory
	{
		constexpr auto item_in_hands = 0x1B0;
	}
}