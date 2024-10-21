package calc.service;

import dto.GraphData;
import dto.GraphResult;

public interface CalculationService {
    public String evaluateExpression(String expression, double x);

    GraphResult getGraphResult(String expression, GraphData graphData);
}
