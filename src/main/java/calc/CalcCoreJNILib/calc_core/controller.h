#ifndef __CPP3_SmartCalc_v2_0_1_CALC_CORE_CONTROLLER_H__
#define __CPP3_SmartCalc_v2_0_1_CALC_CORE_CONTROLLER_H__

#include <iostream>
#include <string>
#include <variant>

#include "calc_model.h"
#include "calc_structures.h"

namespace s21 {

class Controller {
 public:
  Controller();
  ~Controller();

  std::string getExpressionResult(std::string expression, double x);

  std::pair<std::string, std::pair<std::vector<double>, std::vector<double>>>
  getGraphData(std::string expression, GraphBounds graphBounds);

  std::pair<std::string, LoanAnnuityResult> calculateAnnuityPayment(
      double loanAmount,
      double interestRate,
      int months
  );

  std::pair<std::string, LoanDifferentiatedResult>
  calculateDifferentiatedPayment(
      double loanAmount,
      double interestRate,
      int months
  );

  std::pair<std::string, DebetResult> calculateDebetBalance(
      DebetData debetData
  );

 private:
  s21::CalcModel *calcModel_;
};
}  // namespace s21

#endif  // __CPP3_SmartCalc_v2_0_1_CALC_CORE_CONTROLLER_H__
