package calc.service.impl.config;

import calc.CalcCoreJNILib.CalcCoreJNI;
import calc.service.impl.CalculationServiceImpl;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

@Configuration
@ComponentScan("calc.CalcCoreJNILib")
public class CalculationServiceTestConfig {

    @Bean
    public CalculationServiceImpl calculationService(@Autowired CalcCoreJNI calcCoreJNI) {
        return new CalculationServiceImpl(calcCoreJNI);
    }
}
