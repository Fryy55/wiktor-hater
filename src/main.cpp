#include <dpp/dpp.h>
#include <fstream>
#include "secrets.hpp"

using namespace dpp;


int main() {
	cluster bot(BOT_TOKEN, i_default_intents | i_message_content);
	std::ofstream O("C:/Users/User/Desktop/debug_hater.txt", std::ofstream::out | std::ofstream::trunc);
	O.close();

	bot.on_log([](log_t const& log) {
		using namespace std::chrono;

		std::ofstream O("C:/Users/User/Desktop/debug_hater.txt", std::ofstream::app);

		char const* severity;
		switch (log.severity) {
			case loglevel::ll_debug:
				severity = "DEBUG: ";
				break;
			case loglevel::ll_info:
				severity = "INFO: ";
				break;
			case loglevel::ll_warning:
				severity = "WARNING: ";
				break;
			case loglevel::ll_error:
				severity = "ERROR: ";
				break;
			case loglevel::ll_critical:
				severity = "CRITICAL: ";
				break;
			default:
				return;
		}

		auto now_tt = system_clock::to_time_t(system_clock::now());
		tm now_tm;
		localtime_s(&now_tm, &now_tt);

		auto fmt = "%a %b %d %I:%M:%S %p %Y";

		O << '[' << std::put_time(&now_tm, fmt) << "] " << severity << log.message << '\n';
		O.close();
		std::cout << '[' << std::put_time(&now_tm, fmt) << "] " << severity << log.message << '\n';

		return;
	});

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

	bot.on_slashcommand([&bot](slashcommand_t const& event) {
		if (event.command.get_command_name() == "hate-wik")
			event.reply(message().add_file("kill.jpg", utility::read_file("C:\\Users\\User\\Pictures\\Camera Roll\\kill.jpg")));
	});

	bot.on_message_create([&bot](message_create_t const& event) {
		if (event.msg.author.username == "wdwiktor") {
			bot.message_add_reaction(event.msg, "❌");
			return;
		}


		bool mentionedWik = false;
		for (auto ping : event.msg.mentions)
			if (mentionedWik = ping.first.username == "wdwiktor")
				break;

		if (
			event.msg.author.format_username() != "wiktor hater#7539"
			&&
			(
				lowercase<char>(event.msg.content).find("wik") != event.msg.content.npos
				||
				mentionedWik
			)
		)
			event.reply(std::string("wiktor mentioned ") + (mentionedWik ? "(literally) " : "") + " :thumbsdown:");
	});

	bot.start(st_wait);

	O.close();
	return 0;
}