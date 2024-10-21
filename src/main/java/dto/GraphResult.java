package dto;

import java.util.List;

public class GraphResult {
    public List<Double> xValues;
    public List<Double> yValues;
    public String errorMessage;

    public GraphResult(List<Double> xValues, List<Double> yValues, String errorMessage) {
        this.xValues = xValues;
        this.yValues = yValues;
        this.errorMessage = errorMessage;
    }

    public GraphResult() {

    }
}
