package main

import (
	"fmt"
	"github.com/charmbracelet/bubbletea"
	"os"
)

type model struct {
	UserMsg      string
	ChatMessages []string
}

func (m model) Init() tea.Cmd {
	return nil
}

func (m model) View() string {

	// twitch chat screen
	s := ""
	for _, msg := range m.ChatMessages {
		s += fmt.Sprintf("%s\n", msg)
	}
	s += "--------------\n"
	// user chat input
	s += fmt.Sprintf("%s\n", m.UserMsg)
	return s
}

func initialModel() model {
	return model{
		ChatMessages: make([]string, 0, 100),
		UserMsg:      "initial state",
	}
}

func (m model) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
	switch msg := msg.(type) {
	// A key press
	case tea.KeyMsg:
		// the key press
		switch msg.String() {

		// These keys should exit the program.
		case "ctrl+c", "q":
			return m, tea.Quit

		// The "enter" key to send user msg to twitch chat
		case "enter":
			m.ChatMessages = append(m.ChatMessages, "hello world")

			// Send UserMsg to twitch chat, then clear it on the screen
			m.UserMsg = "sending "
		}
	}
	return m, nil
}
func main() {
	p := tea.NewProgram(initialModel())
	if _, err := p.Run(); err != nil {
		fmt.Printf("Alas, there's been an error: %v", err)
		os.Exit(1)
	}
}
