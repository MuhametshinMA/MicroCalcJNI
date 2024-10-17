#include "Token.h"

namespace s21 {

Token::Token(TokenType type, double value)
    : type_(type), priority_(getTokenPriority()), value_(value) {}

void Token::setValue(double value) {
    value_ = value;
}

double Token::getValue() {
    return value_;
}

TokenType Token::getType() {
    return type_;
}

std::string Token::typeToString() {
    for (const auto& it : mapTokenType_) {
        if (it.second == type_) {
            return it.first;
        }
    }
    return "not found";
}

std::map<std::string, TokenType> Token::getTokenStringMap() {
    return mapTokenType_;
}

TokenGroup Token::getTokenGroup() {
    const std::unordered_map<TokenType, TokenGroup> mapTokenGroup = {
        {TokenType::kX, TokenGroup::kNum},
        {TokenType::kNum, TokenGroup::kNum},
        {TokenType::kSum, TokenGroup::kBinar},
        {TokenType::kSub, TokenGroup::kBinar},
        {TokenType::kMul, TokenGroup::kBinar},
        {TokenType::kDiv, TokenGroup::kBinar},
        {TokenType::kPow, TokenGroup::kBinar},
        {TokenType::kMod, TokenGroup::kBinar},
        {TokenType::kCos, TokenGroup::kUnar},
        {TokenType::kTan, TokenGroup::kUnar},
        {TokenType::kSin, TokenGroup::kUnar},
        {TokenType::kSqrt, TokenGroup::kUnar},
        {TokenType::kLn, TokenGroup::kUnar},
        {TokenType::kLog, TokenGroup::kUnar},
        {TokenType::kAcos, TokenGroup::kUnar},
        {TokenType::kAsin, TokenGroup::kUnar},
        {TokenType::kAtan, TokenGroup::kUnar},
        {TokenType::kUsub, TokenGroup::kUnar},
        {TokenType::kUsum, TokenGroup::kUnar},
        {TokenType::kOpenBracket, TokenGroup::kOBracket},
        {TokenType::kCloseBracket, TokenGroup::kCBracket},
        {TokenType::kTypeErr, TokenGroup::kErr}};

    auto it = mapTokenGroup.find(type_);
    if (it != mapTokenGroup.end()) {
        return it->second;
    }
    return TokenGroup::kErr;
}

TokenPriority Token::getTokenPriority() {
    static std::map<TokenType, TokenPriority> priorityMap = {
        {TokenType::kX, TokenPriority::kVeryLow},
        {TokenType::kNum, TokenPriority::kVeryLow},
        {TokenType::kSum, TokenPriority::kLow},
        {TokenType::kSub, TokenPriority::kLow},
        {TokenType::kMul, TokenPriority::kMiddle},
        {TokenType::kDiv, TokenPriority::kMiddle},
        {TokenType::kPow, TokenPriority::kHigh},
        {TokenType::kMod, TokenPriority::kMiddle},
        {TokenType::kCos, TokenPriority::kHigh},
        {TokenType::kTan, TokenPriority::kHigh},
        {TokenType::kSin, TokenPriority::kHigh},
        {TokenType::kSqrt, TokenPriority::kHigh},
        {TokenType::kLn, TokenPriority::kHigh},
        {TokenType::kLog, TokenPriority::kHigh},
        {TokenType::kAcos, TokenPriority::kHigh},
        {TokenType::kAsin, TokenPriority::kHigh},
        {TokenType::kAtan, TokenPriority::kHigh},
        {TokenType::kUsub, TokenPriority::kHigher},
        {TokenType::kUsum, TokenPriority::kHigher},
        {TokenType::kOpenBracket, TokenPriority::kVeryLow},
        {TokenType::kTypeErr, TokenPriority::kErr}};

    auto it = priorityMap.find(type_);
    if (it != priorityMap.end()) {
        return it->second;
    }
    return TokenPriority::kErr;
}

}  // namespace s21
