package calc.controller;

import calc.service.impl.CalculationServiceImpl;
import dto.GraphData;
import dto.GraphResult;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.ui.Model;

import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

class CalculationGraphTest {

    @InjectMocks
    private CalculationGraph calculationGraph;

    @Mock
    private CalculationServiceImpl calculationServiceImpl;

    @Mock
    private Model model;

    @BeforeEach
    void setUp() {
        MockitoAnnotations.openMocks(this);
    }

    @Test
    void showGraphForm_ShouldInitializeModelAttributes() {
        String viewName = calculationGraph.showGraphForm(model);

        verify(model).addAttribute("expression", "");
        verify(model).addAttribute("errorMessage", "");
        assertEquals("graph", viewName);
    }

    @Test
    void getGraph_ShouldAddGraphDataToModel() {
        // Arrange
        String expression = "x^2";
        double xBegin = -10;
        double xEnd = 10;
        double step = 1;
        double yBegin = -10;
        double yEnd = 10;

        GraphResult graphResult = new GraphResult();
        graphResult.xValues = Arrays.asList(-10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0);
        graphResult.yValues =  Arrays.asList(100.0, 81.0, 64.0, 49.0, 36.0, 25.0, 16.0, 9.0, 4.0, 1.0, 0.0, 1.0, 4.0, 9.0, 16.0, 25.0, 36.0, 49.0, 64.0, 81.0, 100.0);
        graphResult.errorMessage = "";

        when(calculationServiceImpl.getGraphResult(eq(expression), any(GraphData.class))).thenReturn(graphResult);

        // Act
        String viewName = calculationGraph.getGraph(expression, xBegin, xEnd, step, yBegin, yEnd, model);

        // Assert
        verify(model).addAttribute("xValues", graphResult.xValues);
        verify(model).addAttribute("yValues", graphResult.yValues);
        verify(model).addAttribute("errorMessage", graphResult.errorMessage);
        verify(model).addAttribute("expression", expression);
        assertEquals("graph", viewName);
    }
}
