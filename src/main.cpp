#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

int main(void) {

    std::string echo;

    std::string content;
    ftxui::InputOption opt;
    opt.on_enter = [&]() {
        echo = content;
        content.clear();
    };
    ftxui::Component input = ftxui::Input(&content, opt);
    input |= ftxui::border;

    auto chatBox = ftxui::Renderer([&] {
        return ftxui::vbox({
            ftxui::paragraph(echo) | ftxui::border | ftxui::flex,
        });
    });

    auto container = ftxui::Container::Vertical({chatBox, input});

    auto screen = ftxui::ScreenInteractive::Fullscreen();
    screen.Loop(container);

    return 0;
}
