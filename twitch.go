package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"net/url"

	"github.com/gorilla/websocket"
)

func auth(oauth_token string) error {

	url := url.URL{Host: "https://id.twitch.tv:1935", Path: "oauth2/validate"}

	q := url.Query()
	q.Set("Authorization", fmt.Sprintf("OAuth %s", oauth_token))

	url.RawQuery = q.Encode()

	resp, err := http.Get(url.String())

	if err != nil {
		return nil
	}

	if resp.StatusCode != 200 {
		return fmt.Errorf("Token is not valid. /oauth2/validate returned status code %d", resp.StatusCode)
	}

	return nil
}

func startWebSocketClient() {

	log.Printf("connecting to Twitch eventsub")
	c, _, err := websocket.DefaultDialer.Dial("wss://eventsub.wss.twitch.tv/ws", nil)
	if err != nil {
		log.Fatal("dial:", err)
	}
	defer c.Close()

	done := make(chan struct{})

	go func() {
		defer close(done)
		for {
			msg_type, message, err := c.ReadMessage()
			if err != nil {
				log.Println("read:", err)
				return
			}
			log.Printf("recv: %s", message)

			msg := string(message)

		}
	}()
}

type Condition struct {
	BroadcasterUserId string `json:"broadcaster_user_id"`
	UserId            string `json:"user_id"`
}

type Transport struct {
	Method    string `json:"method"`
	SessionId string `json:"session_id"`
}

type EventSubRequest struct {
	Type    string    `json:"type"`
	Version string    `json:"version"`
	Cond    Condition `json:"condition"`
	Trans   Transport `json:"transport"`
}

type WelcomeMessage struct {
}

func registerEventSubListener() error {

	data := EventSubRequest{Type: "channel.chat.message",
		Version: "1",
		Cond: Condition{
			BroadcasterUserId: "ninja",
			UserId:            "test",
		},
		Trans: Transport{
			Method:    "websocket",
			SessionId: "session id",
		},
	}

	jsonData, err := json.Marshal(data)

	if err != nil {
		log.Printf("Error json marshalling: %s", err)
		return err
	}

	request, err := http.NewRequest("POST", "https://api.twitch.tv/helix/eventsub/subscriptions", bytes.NewBuffer(jsonData))

	if err != nil {
		log.Printf("Error creating HTTP POST request: %s", err)
		return err
	}

	request.Header.Set("Content-Type", "application/json; charset=UTF-8")

	client := http.Client{}
	response, err := client.Do(request)

	if err != nil {
		log.Printf("Error sending HTTP POST request: %s", err)
		return err
	}
	defer response.Body.Close()

	if response.StatusCode != 202 {
		body, _ := io.ReadAll(response.Body)
		return fmt.Errorf("Error subscribing to channel.chat.message. %s", body)
	}

	return nil

}
