package calc.controller;

import calc.service.CacheService;
import calc.service.CalculationService;
import lombok.AllArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.Optional;

@Slf4j
@Controller
@RequestMapping("/api/calculations")
@AllArgsConstructor
public class CalculationController {

    @Autowired
    private final CalculationService calculationService;

    @Autowired
    private final CacheService cacheService;

    @GetMapping()
    public String showForm(Model model) {

        log.info("Show form calculation.");

        return "calculation"; // Имя шаблона
    }

    @GetMapping("/evaluate")
    public String evaluateExpression(@RequestParam String expression, @RequestParam double x, Model model) {
        String cacheKey = generateKey(expression, x);
        String resultExp;

        try {
            Optional<String> result = cacheService.getCacheResult(cacheKey);

            if (result.isPresent()) {
                resultExp = result.get(); // Если результат найден в кэше
            } else {
                // Если результат не найден в кэше, вычисляем
                resultExp = calculationService.evaluateExpression(expression, x);
                cacheService.cacheResult(cacheKey, resultExp); // Сохраняем результат в кэше
            }
        } catch (Exception e) {
            log.error("Cache service is unavailable, calculating result without cache", e);
            // Если кэш-сервис недоступен, вычисляем результат напрямую
            resultExp = calculationService.evaluateExpression(expression, x);
        }

        model.addAttribute("result", resultExp); // Добавляем результат в модель
        model.addAttribute("expression", expression); // Сохраняем введенное выражение
        model.addAttribute("x", x); // Сохраняем значение x
        log.info("Evaluated expression {} with value {}, result is {}", expression, x, resultExp);
        return "calculation"; // Возвращаем тот же шаблон
    }

    private String generateKey(String expression, double x) {
        return String.format("%s-%f", expression, x);
    }
}
