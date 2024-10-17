package calc.controller;

import calc.service.impl.CalculationServiceImpl;
import dto.GraphData;
import dto.GraphResult;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Slf4j
@Controller
@RequestMapping("/api/graph")
public class CalculationGraph {

    private final CalculationServiceImpl calculationServiceImpl;

    public CalculationGraph(CalculationServiceImpl calculationServiceImpl) {
        this.calculationServiceImpl = calculationServiceImpl;
    }

    @RequestMapping("/graph")
    public String showGraphForm(Model model) {
        // Инициализируем пустые значения
        model.addAttribute("expression", "");
        model.addAttribute("errorMessage", "");

        log.info("Show form graph");
        return "graph"; // Имя шаблона
    }

    @PostMapping("/graph")
    public String getGraph(@RequestParam String expression,
                           @RequestParam double xBegin,
                           @RequestParam double xEnd,
                           @RequestParam double step,
                           @RequestParam double yBegin,
                           @RequestParam double yEnd,
                           Model model) {

        // Создаем объект GraphData с параметрами
        GraphData graphData = new GraphData(xBegin, xEnd, step, yBegin, yEnd);

        // Получаем результат графика с использованием вашего метода
        GraphResult graphResult = calculationServiceImpl.getGraphResult(expression, graphData);

        // Добавляем данные в модель для отображения на странице
        model.addAttribute("xValues", graphResult.xValues);
        model.addAttribute("yValues", graphResult.yValues);
        model.addAttribute("errorMessage", graphResult.errorMessage);
        model.addAttribute("expression", expression);

        log.info("Draw graph by expression {}", expression);
        return "graph"; // Имя шаблона для отображения графика
    }
}
