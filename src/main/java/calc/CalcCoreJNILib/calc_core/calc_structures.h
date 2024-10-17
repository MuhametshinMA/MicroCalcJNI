#ifndef __CPP3_SmartCalc_v2_0_1_CALC_CORE_CALC_STRUCTURES_H__
#define __CPP3_SmartCalc_v2_0_1_CALC_CORE_CALC_STRUCTURES_H__

#include <vector>

namespace s21 {

struct DebetResult {
  double totalInterest = 0;
  double totalTax = 0;
  double finalBalance = 0;
};

struct DebetData {
  double depositAmount = 0;
  int placementPeriod = 0;
  double interestRate = 0;
  double taxRate = 0;
  bool paymentFrequency = false;
  bool interestCapitalization = false;

 public:

  DebetData(double depositAmount, int placementPeriod, double interestRate,
            double taxRate, bool paymentFrequency, bool interestCapitalization)
      : depositAmount(depositAmount),
        placementPeriod(placementPeriod),
        interestRate(interestRate),
        taxRate(taxRate),
        paymentFrequency(paymentFrequency),
        interestCapitalization(interestCapitalization) {}
};

struct LoanDifferentiatedResult {
  std::vector<double> differentiatedPayment;
  double overpay = 0;
  double totalPay = 0;
};

struct LoanAnnuityResult {
  double monthlyPayment = 0;
  double overpayment = 0;
  double totalPayment = 0;
};

class GraphBounds {
 public:
  GraphBounds(double xBegin = 0, double xEnd = 0, double xStep = 0,
              double yBegin = 0, double yEnd = 0)
      : xBegin_(xBegin),
        xEnd_(xEnd),
        xStep_(xStep),
        yBegin_(yBegin),
        yEnd_(yEnd) {}

  double getXBegin() const { return xBegin_; }
  double getXEnd() const { return xEnd_; }
  double getXStep() const { return xStep_; }
  double getYBegin() const { return yBegin_; }
  double getYEnd() const { return yEnd_; }

 private:
  double xBegin_;
  double xEnd_;
  double xStep_;
  double yBegin_;
  double yEnd_;
};
}  // namespace s21

#endif  // __CPP3_SmartCalc_v2_0_1_CALC_CORE_CALC_STRUCTURES_H__