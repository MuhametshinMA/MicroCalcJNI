package calc.CalcCoreJNILib;

import dto.GraphData;
import dto.GraphResult;
import org.springframework.stereotype.Component;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.URL;

@Component
public class CalcCoreJNI {

    // Load the native library
    static {
        try {
            // Путь к библиотеке в корне ресурсов
            String libPath = "/libcalc_core_jni.dylib";
            URL resourceUrl = CalcCoreJNI.class.getResource(libPath);

            if (resourceUrl == null) {
                throw new RuntimeException("Library not found: " + libPath);
            }

            // Создаем временный файл для загрузки библиотеки
            File tempFile = File.createTempFile("libcalc_core_jni", ".dylib");
            tempFile.deleteOnExit(); // Удаляем файл при выходе

            // Копируем библиотеку из ресурсов во временный файл
            try (InputStream in = resourceUrl.openStream();
                 FileOutputStream out = new FileOutputStream(tempFile)) {
                byte[] buffer = new byte[1024];
                int bytesRead;
                while ((bytesRead = in.read(buffer)) != -1) {
                    out.write(buffer, 0, bytesRead);
                }
            }

            // Загружаем библиотеку из временного файла
            System.load(tempFile.getAbsolutePath());

        } catch (Exception e) {
            e.printStackTrace();
            throw new RuntimeException("Failed to load native library");
        }
    }

    // Native methods declaration
    public native String getExpressionResult(String expression, double x);

    public native GraphResult getGraphResult(String expression, GraphData graphBounds);
}
