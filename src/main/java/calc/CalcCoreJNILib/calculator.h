#ifndef __CPP3_SmartCalc_v2_0_1_CALC_BACK_CALCULATOR_H__
#define __CPP3_SmartCalc_v2_0_1_CALC_BACK_CALCULATOR_H__

#include <cmath>
#include <functional>
#include <list>
#include <map>
#include <string>
#include "token.h"

namespace s21 {

class Calculator {
 public:

  Calculator(std::list<s21::Token> polish, double x);
  ~Calculator() = default;

  std::string Calculate();

 private:

  std::list<s21::Token> polish_;
  double x_;
  std::list<double> stack_;
  std::map<s21::TokenType, std::function<void()>> operations;
};

}  // namespace s21

#endif  // __CPP3_SmartCalc_v2_0_1_CALC_BACK_CALCULATOR_H__
