package calc.service;

import java.util.Optional;

public interface CacheService {
    Optional<String> getCacheResult(String key);

    void cacheResult(String key, String value);
}
