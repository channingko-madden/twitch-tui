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

#include "chat_buffer.hpp"

int main(void) {

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
