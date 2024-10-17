#ifndef __CPP3_SmartCalc_v2_0_1_CALC_BACK_TOKEN_H__
#define __CPP3_SmartCalc_v2_0_1_CALC_BACK_TOKEN_H__

#include <unordered_map>
#include <map>
#include <string>

namespace s21 {
/// @brief Token group
enum class TokenGroup { kNum, kBinar, kUnar, kOBracket, kCBracket, kErr };

/// @brief Token type
typedef enum TokenType {
  kX,
  kNum,
  kSum,
  kSub,
  kMul,
  kDiv,
  kPow,
  kMod,
  kCos,
  kTan,
  kSin,
  kSqrt,
  kLn,
  kLog,
  kAcos,
  kAsin,
  kAtan,
  kUsub,
  kUsum,
  kOpenBracket,
  kCloseBracket,
  kTypeErr
} TokenType;

/// @brief Token priority
typedef enum TokenPriority {
  kVeryLow,  // kNum, kX, '(' - kOpen-bracket
  kLow,      // kSum, kSub
  kMiddle,   // kMul, kDiv, kMod
  kHigh,     // kPow, kCos, kSin, kSqrt, kLn, kLog, kAcos, kAsin, kAtan
  kHigher,   // kUnar (kUsum, kUsub),
  kErr
} TokenPriority;

/// @brief class of token
class Token {
 public:
  Token(TokenType type, double value = 0);
  void setValue(double value);
  double getValue();
  TokenType getType();
  std::string typeToString();
  static std::map<std::string, TokenType> getTokenStringMap();
  TokenGroup getTokenGroup();
  TokenPriority getTokenPriority();

 private:
  TokenType type_;
  TokenPriority priority_;
  double value_;
  /// @brief map of string to token type
  inline static const std::map<std::string, TokenType> mapTokenType_{
      {"cos", TokenType::kCos},       {"sin", TokenType::kSin},
      {"tan", TokenType::kTan},       {"acos", TokenType::kAcos},
      {"asin", TokenType::kAsin},     {"atan", TokenType::kAtan},
      {"sqrt", TokenType::kSqrt},     {"ln", TokenType::kLn},
      {"log", TokenType::kLog},       {"x", TokenType::kX},
      {"+", TokenType::kSum},         {"-", TokenType::kSub},
      {"*", TokenType::kMul},         {"/", TokenType::kDiv},
      {"^", TokenType::kPow},         {"mod", TokenType::kMod},
      {"(", TokenType::kOpenBracket}, {")", TokenType::kCloseBracket},
      {"num", TokenType::kNum},       {"u-", TokenType::kUsub},
      {"u+", TokenType::kUsum},       {"err", TokenType::kTypeErr}};
};
}  // namespace s21

#endif  // __CPP3_SmartCalc_v2_0_1_CALC_BACK_TOKEN_H__
