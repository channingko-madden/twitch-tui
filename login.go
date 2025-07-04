package main

import (
	"github.com/charmbracelet/bubbles/textinput"
	"github.com/charmbracelet/bubbletea"
)

type loginModel struct {
	inputs []textinput.Model
}

func initLoginModel() loginModel {

	m := loginModel{
		inputs: make([]textinput.Model, 3),
	}

	var t textinput.Model
	for i := range m.inputs {
		t = textinput.New()
		t.CharLimit = 32

		switch i {
		// BroadcasterUserId
		case 0:
			t.Placeholder = "Broadcaster User Id"
			t.Focus()
		// UserId
		case 1:
			t.Placeholder = "User Id"
		// OAuth
		case 2:
			t.Placeholder = "OAuth Token"
		default:
			panic("Whoops should only be 3 inputs!")
		}

		m.inputs[i] = t

	}

	return m

}

func (m loginModel) Init() tea.Cmd {
	return nil
}

func (m loginModel) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
	switch msg := msg.(type) {
	case tea.KeyMsg:
		switch msg.Type {
		case tea.KeyCtrlC, tea.KeyEsc:
			return m, tea.Quit

		case tea.KeyEnter:
			// which input component is focused?
			for i, v := range m.inputs {
				if v.Focused() {
					v.Update(msg)
					if i != len(m.inputs)-1 {
						m.inputs[i+1].Focus()
					}
					break
				}
			}
		}
	}

	return m, nil
}

func (m loginModel) View() string {
	view := ""
	for i, v := range m.inputs {
		view += v.View()
		if i != len(m.inputs)-1 {
			view += "\n\n"
		}
	}
	return view
}
