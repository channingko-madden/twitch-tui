/*
 * I think the Authorization code grant flow is ultimately what should be used to programatically
 * get oauth tokens, for the case if they expire during runtime.
 *
 * But for now, just pass in the outh token as a config variable and use the 
 * 'https://id.twitch.tv/oauth2/validate' endpoint to validate
 */

#include <string_view>

namespace tui {

class Twitch {
public:

    /* Validates oauth token and establishes websocket connection with Twitch */
    bool auth(std::string_view oauth) const;

    /* Connect to the chat of a Twitch channel */
    bool connect(std::string_view channelUserId);

    /* Add a callback for a new Twitch chat message */
    void addNewMsgCallback();


};

}
