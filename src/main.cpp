#include <dpp/dpp.h>
#include "secrets.hpp"

using namespace dpp;


int main() {
	cluster bot(BOT_TOKEN);
	bot.on_log(utility::cout_logger());

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

	bot.on_slashcommand([&bot](slashcommand_t const& event) -> task<void> {
		if (event.command.get_command_name() == "hate-wik")
			event.reply(message().add_file("kill.jpg", "C:\\Users\\User\\Pictures\\Camera Roll\\kill.jpg"));
	});

	bot.start(dpp::st_wait);

	return 0;
}