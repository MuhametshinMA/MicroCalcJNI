#include "Parser.h"

namespace s21 {

Parser::Parser(std::string expression)
    : expression_(expression),
      tokens_(std::make_unique<std::list<Token>>()) {}

Parser::~Parser() {}

void Parser::parse() {
  checkSizeOfExpression();
  changeCommaOnDot();
  checkCorrectCharOfExpression();
  splitToLexemes();
  checkCorrectFirstBackLexemes();
}

std::list<Token>& Parser::getTokens() {
  return *tokens_;
}

size_t Parser::countSpaces() {
  int count = 0;
  for (auto it = expression_.begin(); it != expression_.end(); ++it) {
    if (*it == ' ') {
      count++;
    }
  }
  return count;
}

void Parser::changeCommaOnDot() {
  std::replace(expression_.begin(), expression_.end(), ',', '.');
}

void Parser::checkSizeOfExpression() {
  if (expression_.size() > 255) {
    throw std::invalid_argument(
        "Parser::checkSizeOfExpression: expression too long");
  }
}

void Parser::checkBrackets(std::smatch match, int& count) {
  if (match[0].str() == "(") {
    count++;
  } else if (match[0].str() == ")") {
    count--;
  }
}

void Parser::checkCorrectSequenseLexemes(std::smatch match) {
  std::regex regex_num(R"(\d+(?:\.\d+)?(?:[Ee][-+]?\d+)|\d+(?:\.\d+)?)");

  std::map<std::string, TokenType> token_map = Token::getTokenStringMap();

  if (std::regex_match(match[0].str(), regex_num)) {
    tokens_->push_back(Token(token_map["num"], std::stod(match[0].str())));
  } else {
    tokens_->push_back(Token(getTypeLexem(match[0].str(), token_map), 0));
  }

  bool matching_matrix[5][5] = {
      {0, 1, 1, 1, 0},
      {1, 0, 0, 0, 1},
      {0, 1, 1, 1, 0},
      {0, 1, 1, 1, 0},
      {1, 0, 0, 0, 1}};

  if (tokens_->size() > 1) {
    auto it_prev = std::prev(tokens_->end(), 2);
    if (!matching_matrix[static_cast<int>(tokens_->back().getTokenGroup())]
                        [static_cast<int>((*it_prev).getTokenGroup())]) {
      throw std::invalid_argument(
          "Parser::checkCorrectSequenseLexemes: illegal sequense");
    }
  }
}

void Parser::checkCorrectCharOfExpression() {
  if (!std::regex_match(
          expression_,
          std::regex(R"([dragons climax peEtq\d\+\-\*\/\^\(\)\.]+)"))) {
    throw std::invalid_argument(
        "Parser::checkCorrectCharOfExpression: Invalid expression");
  }
}

void Parser::splitToLexemes() {
  std::regex regex_all_lexem(
      R"(mod|cos|sin|tan|acos|asin|atan|sqrt|ln|log|x|\d+(?:\.\d+)?(?:[Ee][-+]?\d+)|\d+(?:\.\d+)?|\+|\-|\*|\(|\)|\^|\/)");

  std::string::const_iterator iter = expression_.begin();
  std::string::const_iterator end = expression_.end();
  std::smatch match;

  int count_brakets = 0;
  size_t count_lexemes_chars = 0;

  while (std::regex_search(iter, end, match, regex_all_lexem)) {
    count_lexemes_chars += match[0].str().length();

    checkBrackets(match, count_brakets);
    if (count_brakets == -1) {
      throw std::invalid_argument("Parser::splitToLexemes: illegal expression");
    }

    checkCorrectSequenseLexemes(match);
    iter = match.suffix().first;
  }

  if ((expression_.size() - countSpaces()) != count_lexemes_chars) {
    throw std::invalid_argument("Parser::splitToLexemes: illegal expression");
  }

  if (count_brakets != 0) {
    throw std::invalid_argument("Parser::splitToLexemes: illegal expression");
  }
}

void Parser::checkCorrectFirstBackLexemes() {
  if (!(std::regex_match(
            (*tokens_->begin()).typeToString(),
            std::regex(
                R"(num|\(|cos|sin|tan|acos|asin|atan|sqrt|ln|log|x|u\-|u\+)")) &&
        std::regex_match((*--tokens_->end()).typeToString(),
                         std::regex(R"(num|\)|x)")))) {
    throw std::invalid_argument(
        "Parser::checkCorrectFirstBackLexemes: illegal expression");
  }
}

TokenType Parser::getTypeLexem(std::string lexem,
                                std::map<std::string, TokenType>& token_map) {
  std::regex is_binar_regex(R"(\+|\-|\*|\/|\^|mod)");
  std::regex is_unar_regex(R"(cos|sin|tan|sqrt|ln|log|acos|asin|atan)");

  if (lexem == "(") {
    return kOpenBracket;
  } else if (lexem == "x") {
    return kX;
  } else if (std::regex_match(lexem, is_unar_regex)) {
    return token_map[lexem];
  } else if (std::regex_match(lexem, is_binar_regex)) {
    if (tokens_->size() == 0) {
      return (lexem == "-") ? kUsub : kUsum;
    } else {
      std::string prev_lexem = std::prev(tokens_->end(), 1)->typeToString();
      if (lexem == "-" && (std::regex_match(prev_lexem, is_unar_regex) ||
                           std::regex_match(prev_lexem, is_binar_regex) ||
                           prev_lexem == "(")) {
        return kUsub;
      } else if (lexem == "+" &&
                 (std::regex_match(prev_lexem, is_unar_regex) ||
                  std::regex_match(prev_lexem, is_binar_regex) ||
                  prev_lexem == "(")) {
        return kUsum;
      } else {
        return token_map[lexem];
      }
    }
  }

  return kCloseBracket;
}

}  // namespace s21
