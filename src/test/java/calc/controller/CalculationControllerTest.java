package calc.controller;

import static org.mockito.Mockito.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

import calc.service.impl.CalculationServiceImpl;
import calc.service.impl.RedisCalculationService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.MockitoAnnotations;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.test.web.servlet.MockMvc;

import java.util.Optional;

@WebMvcTest(CalculationController.class)
public class CalculationControllerTest {

    @Autowired
    private MockMvc mockMvc;

    @MockBean
    private CalculationServiceImpl calculationServiceImpl;

    @MockBean
    private RedisCalculationService redisCalculationService;

    @InjectMocks
    private CalculationController calculationController;

    @BeforeEach
    public void setup() {
        MockitoAnnotations.openMocks(this);
    }

    @Test
    public void showForm_ShouldReturnCalculationView() throws Exception {
        mockMvc.perform(get("/api/calculations"))
                .andExpect(status().isOk())
                .andExpect(view().name("calculation"));
    }

    @Test
    public void evaluateExpression_CachedResult_ReturnsCalculationViewWithResult() throws Exception {
        String expression = "2*x+3";
        double x = 2.0;
        String cachedResult = "7";

        when(redisCalculationService.getCacheResult(anyString())).thenReturn(Optional.of(cachedResult));

        mockMvc.perform(get("/api/calculations/evaluate")
                        .param("expression", expression)
                        .param("x", String.valueOf(x)))
                .andExpect(status().isOk())
                .andExpect(view().name("calculation"))
                .andExpect(model().attributeExists("result"));

        verify(redisCalculationService, times(1)).getCacheResult(anyString());
        verify(calculationServiceImpl, never()).evaluateExpression(anyString(), anyDouble());
    }

    @Test
    public void evaluateExpression_NonCachedResult_ReturnsCalculationViewWithCalculatedResult() throws Exception {
        String expression = "2*x+3";
        double x = 2.0;
        String calculatedResult = "7";

        when(redisCalculationService.getCacheResult(anyString())).thenReturn(Optional.empty());
        when(calculationServiceImpl.evaluateExpression(expression, x)).thenReturn(calculatedResult);

        mockMvc.perform(get("/api/calculations/evaluate")
                        .param("expression", expression)
                        .param("x", String.valueOf(x)))
                .andExpect(status().isOk())
                .andExpect(view().name("calculation"))
                .andExpect(model().attributeExists("result"));

        verify(redisCalculationService, times(1)).getCacheResult(anyString());
        verify(calculationServiceImpl, times(1)).evaluateExpression(expression, x);
        verify(redisCalculationService, times(1)).cacheResult(anyString(), eq(calculatedResult));
    }
}

