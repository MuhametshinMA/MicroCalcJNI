#include "calculator.h"

namespace s21 {

Calculator::Calculator(std::list<s21::Token> polish, double x)
    : polish_(std::move(polish)), x_(x) {
  operations = {
      {s21::TokenType::kX, [&]() { stack_.push_back(x_); }},
      {s21::TokenType::kNum, [&]() { stack_.push_back(polish_.front().getValue()); }},
      {s21::TokenType::kSum, [&]() {
          double num = stack_.back();
          stack_.pop_back();
          stack_.back() = num + stack_.back();
      }},
      {s21::TokenType::kSub, [&]() {
          double num = stack_.back();
          stack_.pop_back();
          stack_.back() = stack_.back() - num;
      }},
      {s21::TokenType::kMul, [&]() {
          double num = stack_.back();
          stack_.pop_back();
          stack_.back() = stack_.back() * num;
      }},
      {s21::TokenType::kDiv, [&]() {
          double num = stack_.back();
          stack_.pop_back();
          stack_.back() = stack_.back() / num;
      }},
      {s21::TokenType::kPow, [&]() {
          double num = stack_.back();
          stack_.pop_back();
          stack_.back() = std::pow(stack_.back(), num);
      }},
      {s21::TokenType::kMod, [&]() {
          double num = stack_.back();
          stack_.pop_back();
          stack_.back() = std::fmod(stack_.back(), num);
      }},
      {s21::TokenType::kCos, [&]() { stack_.back() = std::cos(stack_.back()); }},
      {s21::TokenType::kSin, [&]() { stack_.back() = std::sin(stack_.back()); }},
      {s21::TokenType::kTan, [&]() { stack_.back() = std::tan(stack_.back()); }},
      {s21::TokenType::kSqrt, [&]() { stack_.back() = std::sqrt(stack_.back()); }},
      {s21::TokenType::kLn, [&]() { stack_.back() = std::log(stack_.back()); }},
      {s21::TokenType::kLog, [&]() { stack_.back() = std::log10(stack_.back()); }},
      {s21::TokenType::kAcos, [&]() { stack_.back() = std::acos(stack_.back()); }},
      {s21::TokenType::kAsin, [&]() { stack_.back() = std::asin(stack_.back()); }},
      {s21::TokenType::kAtan, [&]() { stack_.back() = std::atan(stack_.back()); }},
      {s21::TokenType::kUsub, [&]() { stack_.back() = -stack_.back(); }},
      {s21::TokenType::kUsum, [&]() {}}
  };
}

std::string Calculator::Calculate() {
  while (!polish_.empty()) {
    operations[polish_.front().getType()]();
    polish_.pop_front();
  }

  return std::to_string(stack_.back());
}

}  // namespace s21
