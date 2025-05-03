#pragma once

// Need to create a class that manages the chat being printed to the dislay.

/**
 * Basic idea is a new chat msg comes in, it's added to a "buffer" of chat messages
 *   Buffer is capped at X number of messages. 
 *   Also need to make sure total "size" of all messages does not exceed a limit
 *     Maybe need a class to manage this?
 * The ftxui::paragraph is re-rendered
 *   The ftxui::Input for the user to type a message should not be re-rendered if possible?
 */

namespace tui {
}
