#ifndef __CPP3_SmartCalc_v2_0_1_CALC_CORE_CALC_MODEL_H__
#define __CPP3_SmartCalc_v2_0_1_CALC_CORE_CALC_MODEL_H__

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>
#include "calc_structures.h"
#include "calculator.h"
#include "parser.h"
#include "polish.h"

namespace s21 {

class CalcModel {
 public:
  CalcModel() {}

  std::string CalculateExpression(std::string expression, double x = 0);

  std::pair<std::vector<double>, std::vector<double>> CalculateGraphData(
      std::string expression, GraphBounds graphBounds);

  LoanAnnuityResult calculateAnnuityPayment(double loanAmount,
                                            double interestRate, int months);

  LoanDifferentiatedResult calculateDifferentiatedPayment(double loanAmount,
                                                          double interestRate,
                                                          int months);

  DebetResult calculateDebet(DebetData debetData);
};

}  // namespace s21

#endif  // __CPP3_SmartCalc_v2_0_1_CALC_CORE_CALC_MODEL_H__
