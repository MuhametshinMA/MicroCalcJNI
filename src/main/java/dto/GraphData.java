package dto;

public class GraphData {
    private final double xBegin;
    private final double xEnd;
    private final double step;
    private final double yBegin;
    private final double yEnd;


    public GraphData(double xBegin, double xEnd, double step, double yBegin, double yEnd) {
        this.xBegin = xBegin;
        this.xEnd = xEnd;
        this.step = step;
        this.yBegin = yBegin;
        this.yEnd = yEnd;
    }
}
