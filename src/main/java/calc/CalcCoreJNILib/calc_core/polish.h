#ifndef __CPP3_SmartCalc_v2_0_1_CALC_CORE_POLISH_H__
#define __CPP3_SmartCalc_v2_0_1_CALC_CORE_POLISH_H__

#include <list>
#include "Token.h"  // Include the Token class header

namespace s21 {

class Polish {
 public:
  Polish() {}
  std::list<s21::Token> toPolish(std::list<s21::Token> tokens);
};

}  // namespace s21

#endif  // __CPP3_SmartCalc_v2_0_1_CALC_CORE_POLISH_H__
