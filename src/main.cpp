#include <dpp/dpp.h>

#include <bismuth/classes/logger.hpp>
#include <aurora/aurora.hpp>

#include "secrets.hpp"

using namespace dpp;
using namespace aurora;


int main() {
	cluster bot(secrets::BOT_TOKEN, i_default_intents | i_message_content);

	log::set12hTimeEnabled(true);
	log::setFileLogLevel(log::LogLevel::Debug);
	TargetManager::get()->logToDir(std::format("{}/Desktop/logs/hater", std::getenv("HOME")), "Hater");
	ThreadManager::get()->addThread("Main");
	bot.on_log(bismuth::logger());

	bot.on_ready([&bot](ready_t const& event) {
		if (run_once<struct CmdRegister>()) {
			std::vector<slashcommand> commands {
				{ "hate-wik", "hates the wiktor with an image!", bot.me.id },
			};
			for (slashcommand command : commands)
				command.set_interaction_contexts({itc_guild});

			bot.global_bulk_command_create(commands);
		}

		bot.set_presence(presence(ps_online, at_watching, "wiktor's downfall!"));
	});

	bot.on_slashcommand([](slashcommand_t const& event) {
		if (event.command.get_command_name() == "hate-wik")
			event.reply(message().add_file("kill.jpg", utility::read_file("/home/fryy_55/Pictures/Camera Roll/kill.jpg")));
	});

	bot.on_message_create([&bot](message_create_t const& event) {
		if (event.msg.author.username == "wdwiktor") {
			bot.message_add_reaction(event.msg, "❌", [event](confirmation_callback_t const& callback) {
				if (callback.is_error())
					event.reply("unblock me bozo :middle_finger:", true);

				return;
			});
			return;
		}


		bool mentionedWik = false;
		for (auto const& ping : event.msg.mentions)
			if (ping.first.username == "wdwiktor") {
				mentionedWik = true;
				break;
			}

		if (
			event.msg.author.format_username() != "wiktor hater#7539"
			&&
			(
				lowercase<char>(event.msg.content).find("wik") != event.msg.content.npos
				||
				mentionedWik
			)
		) event.reply(std::string("wiktor mentioned ") + (mentionedWik ? "(literally) " : "") + " :thumbsdown:");
	});

	bot.start(st_wait);

	return 0;
}