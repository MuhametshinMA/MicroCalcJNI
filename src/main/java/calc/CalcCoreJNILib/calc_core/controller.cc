#include "controller.h"

namespace s21 {

Controller::Controller() {
  calcModel_ = new s21::CalcModel();
}

Controller::~Controller() {
  delete calcModel_;
}

std::string Controller::getExpressionResult(std::string expression, double x) {
  try {
    return calcModel_->CalculateExpression(expression, x);
  } catch (const std::invalid_argument &e) {
    return e.what();
  }
}

std::pair<std::string, std::pair<std::vector<double>, std::vector<double>>>
Controller::getGraphData(std::string expression, GraphBounds graphBounds) {
  std::pair<std::vector<double>, std::vector<double>> graphdata;
  try {
    graphdata = calcModel_->CalculateGraphData(expression, graphBounds);
    return std::make_pair("", graphdata);
  } catch (const std::invalid_argument &e) {
    return std::make_pair(e.what(), graphdata);
  }
}

std::pair<std::string, LoanAnnuityResult> Controller::calculateAnnuityPayment(
    double loanAmount, double interestRate, int months) {
  LoanAnnuityResult result;
  try {
    result = calcModel_->calculateAnnuityPayment(loanAmount, interestRate, months);
    return std::make_pair("", result);
  } catch (const std::invalid_argument &e) {
    return std::make_pair(e.what(), result);
  }
}

std::pair<std::string, LoanDifferentiatedResult>
Controller::calculateDifferentiatedPayment(double loanAmount, double interestRate,
                                            int months) {
  LoanDifferentiatedResult result;
  try {
    result = calcModel_->calculateDifferentiatedPayment(loanAmount, interestRate, months);
    return std::make_pair("", result);
  } catch (const std::invalid_argument &e) {
    return std::make_pair(e.what(), result);
  }
}

std::pair<std::string, DebetResult> Controller::calculateDebetBalance(DebetData debetData) {
  DebetResult result;
  try {
    result = calcModel_->calculateDebet(debetData);
    return std::make_pair("", result);
  } catch (const std::invalid_argument &e) {
    return std::make_pair(e.what(), result);
  }
}

}  // namespace s21
