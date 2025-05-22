package main

import (
	"fmt"
	"github.com/charmbracelet/bubbletea"
	"os"
	"unicode/utf8"
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

func trimLastChar(s string) string {
	r, size := utf8.DecodeLastRuneInString(s)
	if r == utf8.RuneError && (size == 0 || size == 1) {
		size = 0
	}
	return s[:len(s)-size]
}

func (m model) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
	switch msg := msg.(type) {
	// A key press
	case tea.KeyMsg:
		// the key press
		switch msg.String() {

		// This should exit the program.
		case "ctrl+c":
			return m, tea.Quit

		// The "enter" key to send user msg to twitch chat
		case "enter":
			m.ChatMessages = append(m.ChatMessages, m.UserMsg)

			// Send UserMsg to twitch chat, then clear it on the screen
			m.UserMsg = ""
		case "backspace":
			m.UserMsg = trimLastChar(m.UserMsg)

		default:
			m.UserMsg += string(msg.Runes)
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
