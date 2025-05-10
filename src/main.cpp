/**
 * Class that manages the chat being printed to the dislay.
 * The ftxui::paragraph is re-rendered when a new message comes in
 *   The ftxui::Input for the user to type a message should not be re-rendered if possible?
 */

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <toml++/toml.hpp>

#include <iostream>
#include <optional>

#include "chat_buffer.hpp"

int main(void) {


    // read in config
    toml::table tbl;
    try
    {
        tbl = toml::parse_file("config.toml");
    }
    catch (const toml::parse_error& err)
    {
        std::cerr << "Parsing confit.toml failed:\n" << err << "\n";
        return 1;
    }

    if (!tbl.contains("twitch")) {
        std::cerr << "twitch table is missing from config.toml" << "\n";
        return 1;
    }

    const std::optional<std::string> oauth = tbl["twitch"]["oauth"].value<std::string>();

    if (oauth == std::nullopt) {
        std::cerr << "twitch table is missing the oauth key in config.toml" << "\n";
        return 1;
    }


    tui::ChatBuffer chatBuffer(2000);

    std::string content;
    ftxui::InputOption opt;
    opt.on_enter = [&]() {
        chatBuffer.add(content);
        content.clear();
    };
    ftxui::Component input = ftxui::Input(&content, opt);
    input |= ftxui::border;

    auto chatBox = ftxui::Renderer([&] {
        return ftxui::vbox({
            ftxui::paragraph(chatBuffer.get()) | ftxui::border | ftxui::flex,
        });
    });

    auto container = ftxui::Container::Vertical({chatBox, input});

    auto screen = ftxui::ScreenInteractive::Fullscreen();
    screen.Loop(container);

    return 0;
}
