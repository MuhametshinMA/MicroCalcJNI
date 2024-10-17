package calc.service.impl;

import calc.service.CacheService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Service;

import java.util.Optional;

@Service
public class RedisCalculationService implements CacheService {

    @Autowired
    private RedisTemplate<String, String> redisTemplate;

    public RedisTemplate<String, String> getRedisTemplate() {
        return redisTemplate;
    }

    public void cacheResult(String key, String result) {
        redisTemplate.opsForValue().set(key, result);
    }

    public Optional<String> getCacheResult(String key) {
        return Optional.ofNullable(redisTemplate.opsForValue().get(key));
    }
}
