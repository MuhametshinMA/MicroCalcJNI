package calc.service.impl;

import calc.service.impl.config.CalculationServiceTestConfig;
import dto.GraphData;
import dto.GraphResult;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import org.mockito.MockitoAnnotations;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ContextConfiguration;

import java.util.Arrays;
import java.util.List;
import java.util.stream.IntStream;
import java.util.stream.Stream;

@SpringBootTest(classes = {CalculationServiceImpl.class})
@ContextConfiguration(classes = {CalculationServiceTestConfig.class})
public class CalculationServiceImplTest {

    @Autowired
    private CalculationServiceImpl calculationService;

    @BeforeEach
    void setUp() {
//        calculationService = new CalculationServiceImpl(new);
        MockitoAnnotations.openMocks(this);  // Это можно оставить, если у вас есть другие моки
    }

    public static Stream<Arguments> initStr() {

        List<String> listExp = Arrays.asList(
                "2+x", "3+x", "4+x",
                "cos x - tan log x/sin x",
                "-cos(log(sqrt 25) + sin x)",
                "tan log x/cos x - tan log x/sin x",
                "64*-(62^2)--x",
                "x mod1.33 ^ 4 + -5-(2^3)-sin1"
        );
        List<Double> listX = Arrays.asList(
                10.0, 15.0, 16.0, 0.33, 0.33, 0.33, 0.33, 0.33
        );
        List<String> listResult = Arrays.asList(
                "12.000000", "18.000000", "20.000000",
                "2.558486", "-0.520796", "1.060142",
                "-246015.670000", "-13.511471"
        );

        return IntStream.range(0, listExp.size())
                .mapToObj(i -> Arguments.of(listExp.get(i), listX.get(i), listResult.get(i)));
    }

    @ParameterizedTest
    @MethodSource("initStr")
    public void testEvaluateExpression(String str, Double x, String res) {

        String result = calculationService.evaluateExpression(str, x);

        Assertions.assertEquals(result, res);

    }

    public static Stream<Arguments> graphDataProvider() {
        String expression = "x^2";
        GraphData graphData = new GraphData(-10, 10, 1, -10, 100);
        GraphResult expectedGraphResult = new GraphResult();
        expectedGraphResult.xValues = Arrays.asList(-10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
        expectedGraphResult.yValues = Arrays.asList(100.0, 81.0, 64.0, 49.0, 36.0, 25.0, 16.0, 9.0, 4.0, 1.0, 0.0, 1.0, 4.0, 9.0, 16.0, 25.0, 36.0, 49.0, 64.0, 81.0);
        expectedGraphResult.errorMessage = "";

        return Stream.of(Arguments.of(expression, graphData, expectedGraphResult));
    }

    @ParameterizedTest
    @MethodSource("graphDataProvider")
    public void testGetGraphResult(String expression, GraphData graphData, GraphResult expectedGraphResult) {
        // Здесь вызовите метод getGraphResult
        GraphResult actualGraphResult = calculationService.getGraphResult(expression, graphData);

        // Поскольку у нас нет мока, здесь мы предполагаем, что метод возвращает ожидаемый результат
        // Здесь лучше всего проверять, что возвращаемый результат совпадает с ожидаемым
        Assertions.assertEquals(expectedGraphResult.xValues, actualGraphResult.xValues);
        Assertions.assertEquals(expectedGraphResult.yValues, actualGraphResult.yValues);
        Assertions.assertEquals(expectedGraphResult.errorMessage, actualGraphResult.errorMessage);
    }
}
