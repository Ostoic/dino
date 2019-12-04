#pragma once

#include "../data_store.hpp"
#include "../guid.hpp"

#include <string_view>

namespace dino::wow::chat
{
	using namespace std::literals;
	class message
	{
	public:
		enum class type : char
		{
			system,
			say,
			party,
			raid,
			guild,
			officer,
			yell,
			whisper,
			whisper_foreign,
			whisper_inform,
			emote,
			text_emote,
			monster_say,
			monster_party,
			monster_yell,
			monster_whisper,
			monster_emote,
			channel,
			channel_join,
			channel_leave,
			channel_list,
			channel_notice,
			channel_notice_user,
			afk,
			dnd,
			ignored,
			skill,
			loot,
			money,
			opening,
			tradeskills,
			pet_info,
			combat_misc_info,
			combat_xp_gain,
			combat_honor_gain,
			combat_faction_change,
			bg_system_neutral,
			bg_system_alliance,
			bg_system_horde,
			raid_leader,
			raid_warning,
			raid_boss_emote,
			raid_boss_whisper,
			filtered,
			battleground,
			battleground_leader,
			restricted,
			battlenet,
			achievement,
			guild_achievement,
			arena_points,
			party_leader,
		};

		static constexpr auto type_names = std::array{
			"system"sv,
			"say"sv,
			"party"sv,
			"raid"sv,
			"guild"sv,
			"officer"sv,
			"yell"sv,
			"whisper"sv,
			"whisper_foreign"sv,
			"whisper_inform"sv,
			"emote"sv,
			"text_emote"sv,
			"monster_say"sv,
			"monster_party"sv,
			"monster_yell"sv,
			"monster_whisper"sv,
			"monster_emote"sv,
			"channel"sv,
			"channel_join"sv,
			"channel_leave"sv,
			"channel_list"sv,
			"channel_notice"sv,
			"channel_notice_user"sv,
			"afk"sv,
			"dnd"sv,
			"ignored"sv,
			"skill"sv,
			"loot"sv,
			"money"sv,
			"opening"sv,
			"tradeskills"sv,
			"pet_info"sv,
			"combat_misc_info"sv,
			"combat_xp_gain"sv,
			"combat_honor_gain"sv,
			"combat_faction_change"sv,
			"bg_system_neutral"sv,
			"bg_system_alliance"sv,
			"bg_system_horde"sv,
			"raid_leader"sv,
			"raid_warning"sv,
			"raid_boss_emote"sv,
			"raid_boss_whisper"sv,
			"filtered"sv,
			"battleground"sv,
			"battleground_leader"sv,
			"restricted"sv,
			"battlenet"sv,
			"achievement"sv,
			"guild_achievement"sv,
			"arena_points"sv,
			"party_leader"sv,
		};

	public:
		explicit message(data_store store, bool is_gm_chat = false);

		message* operator->()
		{
			return this;
		}

		const message* operator->() const
		{
			return this;
		}

	public:
		void set_type(type type);
		void set_language(int language);
		void set_sender(guid sender);

		std::string text() const noexcept;
		std::string channel() const noexcept;
		//const std::string& chat_tag() const noexcept;
		type msg_type() const noexcept;
		int language() const noexcept;
		guid sender() const noexcept;
		guid receiver() const noexcept;
		bool is_gm_chat() const noexcept;

	private:
		mutable data_store store_;
		type msg_type_;
		bool is_gm_chat_;
	};

	void add_message(const std::string& message);

	template <class... Args>
	void dino(std::string format, Args&&... args)
	{
		std::string message = fmt::format(format, std::forward<Args>(args)...);
		add_message(message);
	}

	constexpr std::string_view to_string_view(const message::type type)
	{
		return message::type_names[static_cast<int>(type)];
	}
}
