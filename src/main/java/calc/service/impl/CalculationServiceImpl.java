package calc.service.impl;

import calc.CalcCoreJNILib.CalcCoreJNI;
import calc.service.CalculationService;
import dto.GraphData;
import dto.GraphResult;
import org.springframework.stereotype.Service;

@Service
public class CalculationServiceImpl implements CalculationService {

    private final CalcCoreJNI calcCoreJNI;

    public CalculationServiceImpl(CalcCoreJNI calcCoreJNI) {
        this.calcCoreJNI = calcCoreJNI;
    }

    @Override
    public String evaluateExpression(String expression, double x) {
        return calcCoreJNI.getExpressionResult(expression, x);
    }

    @Override
    public GraphResult getGraphResult(String expression, GraphData graphBounds) {
        return calcCoreJNI.getGraphResult(expression, graphBounds);
    }
}
