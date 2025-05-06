#include "chat_buffer.hpp"

namespace tui {

ChatBuffer::ChatBuffer(unsigned int characterLimit) : mCharacterLimit(characterLimit) {
}

std::string ChatBuffer::get() const {
    std::string outString;
    outString.reserve(mCharacterCount);
    for (const auto& msg : mBuffer) {
        outString.append(msg);
    }
    
    return outString;
}


void ChatBuffer::add(const std::string& msg) {
    while (mCharacterCount + msg.size() > mCharacterLimit) {
        mCharacterCount -= mBuffer.front().size();
        mBuffer.pop_front();
    }

    mCharacterCount += msg.size();
    mBuffer.push_back(msg);
}

}
