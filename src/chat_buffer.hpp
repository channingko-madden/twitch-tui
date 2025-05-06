#pragma once

/**
 * Basic idea is a new chat msg comes in, it's added to a "buffer" of chat messages
 *   Buffer is capped at X number of messages. 
 *   Also need to make sure total "size" of all messages does not exceed a limit
 *
 * Try circular buffer memory management 
 */

#include <list>
#include <string>

namespace tui {

class ChatBuffer {
   public:
    ChatBuffer() = default;
    ChatBuffer(unsigned int characterLimit);

    /**
     * @brief Return the chat string
     */
    std::string get() const;

    /**
     * @brief Add a new msg to the chat
     *
     * Existing message may be removed from the buffer to keep the 
     * buffer within the size limit
     */
    void add(const std::string& msg);

   private:
    std::list<std::string> mBuffer;           // FIFO buffer of individual msgs
    size_t mCharacterCount; // Amount of characters in buffer
    const unsigned int mCharacterLimit{100};
};

}  // namespace tui
