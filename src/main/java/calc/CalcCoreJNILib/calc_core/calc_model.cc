#include "calc_model.h"

namespace s21 {

std::string CalcModel::CalculateExpression(std::string expression, double x) {
  s21::Parser parser(expression);
  parser.parse();
  s21::Polish polish;
  std::list<s21::Token> polish_tokens = polish.toPolish(parser.getTokens());

  s21::Calculator calculator(polish_tokens, x);
  return calculator.Calculate();
}

std::pair<std::vector<double>, std::vector<double>> CalcModel::CalculateGraphData(
    std::string expression, GraphBounds graphBounds) {
  std::pair<std::vector<double>, std::vector<double>> graphData;

  s21::Parser parser(expression);
  parser.parse();
  s21::Polish polish;
  std::list<s21::Token> polish_tokens = polish.toPolish(parser.getTokens());

  if (graphBounds.getXStep() <= 0) {
    throw std::invalid_argument("ERROR: Calculator: xStep <= 0");
  }

  if (graphBounds.getXBegin() >= graphBounds.getXEnd()) {
    throw std::invalid_argument("ERROR: Calculator: xBegin >= xEnd");
  }

  if (graphBounds.getYBegin() >= graphBounds.getYEnd()) {
    throw std::invalid_argument("ERROR: Calculator: yBegin >= yEnd");
  }

  for (double x = graphBounds.getXBegin(); x < graphBounds.getXEnd();
       x += graphBounds.getXStep()) {
    s21::Calculator calculator(polish_tokens, x);

    graphData.first.push_back(x);
    graphData.second.push_back(std::stod(calculator.Calculate()));
  }

  return graphData;
}

LoanAnnuityResult CalcModel::calculateAnnuityPayment(double loanAmount,
                                                      double interestRate, int months) {
  if (months <= 0) {
    throw std::invalid_argument("ERROR: Calculator: years <= 0");
  }
  double interest = interestRate / 1200;
  double payment = loanAmount * interest * std::pow((1 + interest), months) /
                   (std::pow((1 + interest), months) - 1);

  double monthlyPayment = payment;
  double totalPay = payment * months;
  double overpay = totalPay - loanAmount;

  return {monthlyPayment, overpay, totalPay};
}

LoanDifferentiatedResult CalcModel::calculateDifferentiatedPayment(double loanAmount,
                                                                  double interestRate,
                                                                  int months) {
  if (months <= 0) {
    throw std::invalid_argument("Calculator: months <= 0");
  }
  double interest = interestRate / 100;
  double monthlyInterest = interest / 12;

  double totalPay = 0;
  std::vector<double> differentiatedPayment(months);

  for (int i = 0; i < months; i++) {
    differentiatedPayment[i] =
        loanAmount / months +
        (loanAmount - (loanAmount / months * i)) * monthlyInterest;
    totalPay += differentiatedPayment[i];
  }

  double overpay = totalPay - loanAmount;

  return {differentiatedPayment, overpay, totalPay};
}

DebetResult CalcModel::calculateDebet(DebetData debetData) {
  double balance = 0;
  int countDayInYear = 365;
  int countMonthInYear = 12;
  int countDayInMonth = 30;
  double nalogAmountLimit = 10000000;

  if (debetData.interestCapitalization) {
    if (debetData.paymentFrequency) {
      balance =
          debetData.depositAmount *
          std::pow((1 + debetData.interestRate / (100 * countDayInYear)),
                   debetData.placementPeriod * countDayInMonth);
    } else {
      balance =
          debetData.depositAmount *
          std::pow((1 + debetData.interestRate / (100 * countMonthInYear)),
                   debetData.placementPeriod);
    }
  } else {
    if (debetData.paymentFrequency) {
      balance = debetData.depositAmount * debetData.interestRate /
                (100 * countDayInYear) * debetData.placementPeriod *
                countDayInMonth;
    } else {
      balance = debetData.depositAmount * debetData.interestRate /
                (100 * countMonthInYear) * debetData.placementPeriod;
    }
    balance += debetData.depositAmount;
  }

  double diff = balance - debetData.depositAmount -
                debetData.taxRate / (100 * nalogAmountLimit);

  double total_tax = diff * debetData.taxRate / 100;
  double total_interest = balance - debetData.depositAmount;

  return {total_interest, total_tax, balance};
}

}  // namespace s21
