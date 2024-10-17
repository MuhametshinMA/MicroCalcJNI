#include "Polish.h"

namespace s21 {

std::list<s21::Token> Polish::toPolish(std::list<s21::Token> tokens) {
  std::list<s21::Token> polish_tokens;
  std::list<s21::Token> stack;

  while (!tokens.empty()) {
    if (tokens.front().typeToString() == "num" ||
        tokens.front().typeToString() == "x") {
      polish_tokens.push_back(tokens.front());
      tokens.pop_front();
    } else if (stack.empty() || tokens.front().typeToString() == "(") {
      stack.push_back(tokens.front());
      tokens.pop_front();
    } else if (tokens.front().getType() == s21::TokenType::kCloseBracket) {
      while (stack.back().getType() != s21::TokenType::kOpenBracket) {
        polish_tokens.push_back(stack.back());
        stack.pop_back();
      }
      stack.pop_back();
      tokens.pop_front();
    } else {
      if (stack.back().getTokenPriority() <
          tokens.front().getTokenPriority()) {
        stack.push_back(tokens.front());
        tokens.pop_front();
      } else if (stack.back().getTokenPriority() >=
                 tokens.front().getTokenPriority()) {
        if (polish_tokens.empty()) {
          stack.push_back(tokens.front());
          tokens.pop_front();
        } else {
          if (tokens.front().getTokenGroup() == s21::TokenGroup::kUnar &&
              stack.back().getTokenGroup() == s21::TokenGroup::kUnar) {
            stack.push_back(tokens.front());
            tokens.pop_front();
          } else {
            while (stack.back().getTokenPriority() >=
                   tokens.front().getTokenPriority()) {
              polish_tokens.push_back(stack.back());
              stack.pop_back();
            }
            stack.push_back(tokens.front());
            tokens.pop_front();
          }
        }
      }
    }
  }

  while (!stack.empty()) {
    polish_tokens.push_back(stack.back());
    stack.pop_back();
  }

  return polish_tokens;
}

}  // namespace s21
