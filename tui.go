package main

import tea "github.com/charmbracelet/bubbletea"

type sessionState int

const (
	loginView sessionState = iota
	chatView
)

type MainModel struct {
	state sessionState
	login tea.Model
	chat  tea.Model
}

func (m MainModel) View() string {
	switch m.state {
	case chatView:
		return m.chat.View()
	default:
		return m.login.View()
	}
}
