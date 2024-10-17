#ifndef __CPP3_SmartCalc_v2_0_1_CALC_CORE_PARSER_H__
#define __CPP3_SmartCalc_v2_0_1_CALC_CORE_PARSER_H__

#include <list>
#include <memory>
#include <regex>
#include <string>
#include <unordered_map>
#include "Token.h"  // Include the Token class header

namespace s21 {

class Parser {
 public:

  Parser(std::string expression);

  ~Parser();

  void parse();

  std::list<Token>& getTokens();

 private:
  std::string expression_;
  std::unique_ptr<std::list<Token>> tokens_;

  size_t countSpaces();
  void changeCommaOnDot();
  void checkSizeOfExpression();
  void checkBrackets(std::smatch match, int& count);
  void checkCorrectCharOfExpression();
  void splitToLexemes();
  void checkCorrectFirstBackLexemes();
  void checkCorrectSequenseLexemes(std::smatch match);

  TokenType getTypeLexem(std::string lexem,
                         std::map<std::string, TokenType>& token_map);
};

}  // namespace s21

#endif  // __CPP3_SmartCalc_v2_0_1_CALC_CORE_PARSER_H__
