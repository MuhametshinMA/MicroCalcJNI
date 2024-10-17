#include "CalcCoreJNI.h"
#include "controller.h"

using namespace s21;

// Пример реализации метода getExpressionResult
JNIEXPORT jstring JNICALL Java_calc_CalcCoreJNILib_CalcCoreJNI_getExpressionResult(JNIEnv *env, jobject obj, jstring expression, jdouble x) {

    const char *nativeExpression = env->GetStringUTFChars(expression, nullptr);
    std::string exprString(nativeExpression);
    Controller controller;
    std::string result = controller.getExpressionResult(exprString, x);
    return env->NewStringUTF(result.c_str());
}

// Реализация метода getGraphData
JNIEXPORT jobject JNICALL Java_calc_CalcCoreJNILib_CalcCoreJNI_getGraphResult(JNIEnv *env, jobject obj, jstring jExpression, jobject jGraphData) {
    // Преобразование jstring в std::string
    const char *expressionChars = env->GetStringUTFChars(jExpression, 0);
    std::string expression(expressionChars);
    env->ReleaseStringUTFChars(jExpression, expressionChars);

    // Извлечение данных из GraphData
    jclass graphDataClass = env->GetObjectClass(jGraphData);

    jfieldID xBeginField = env->GetFieldID(graphDataClass, "xBegin", "D");
    jfieldID xEndField = env->GetFieldID(graphDataClass, "xEnd", "D");
    jfieldID yBeginField = env->GetFieldID(graphDataClass, "yBegin", "D");
    jfieldID yEndField = env->GetFieldID(graphDataClass, "yEnd", "D");
    jfieldID stepField = env->GetFieldID(graphDataClass, "step", "D");

    double xBegin = env->GetDoubleField(jGraphData, xBeginField);
    double xEnd = env->GetDoubleField(jGraphData, xEndField);
    double yBegin = env->GetDoubleField(jGraphData, yBeginField);
    double yEnd = env->GetDoubleField(jGraphData, yEndField);
    double step = env->GetDoubleField(jGraphData, stepField);

    // Создание графических границ
    GraphBounds graphBounds = {xBegin, xEnd, step, yBegin, yEnd};

    Controller controller;
    // Получение данных графика
    auto result = controller.getGraphData(expression, graphBounds);
    const std::string& errorMessage = result.first;
    const auto& data = result.second;

    // Создание GraphResult
    jclass graphResultClass = env->FindClass("dto/GraphResult");
    if (env->ExceptionCheck()) {
        std::cout << "GraphResult is null" << std::endl;
        std::cerr << "Exception: " << env->ExceptionOccurred() << std::endl;
    }
    jmethodID graphResultConstructor = env->GetMethodID(graphResultClass, "<init>", "(Ljava/util/List;Ljava/util/List;Ljava/lang/String;)V");

    // Преобразование std::vector в Java List
    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID arrayListConstructor = env->GetMethodID(arrayListClass, "<init>", "()V");
    jmethodID arrayListAdd = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");

    jobject jXValues = env->NewObject(arrayListClass, arrayListConstructor);
    for (const auto& x : data.first) {
        env->CallBooleanMethod(jXValues, arrayListAdd, env->NewObject(env->FindClass("java/lang/Double"), env->GetMethodID(env->FindClass("java/lang/Double"), "<init>", "(D)V"), x));
    }

    jobject jYValues = env->NewObject(arrayListClass, arrayListConstructor);
    for (const auto& y : data.second) {
        env->CallBooleanMethod(jYValues, arrayListAdd, env->NewObject(env->FindClass("java/lang/Double"), env->GetMethodID(env->FindClass("java/lang/Double"), "<init>", "(D)V"), y));
    }

    jstring jErrorMessage = env->NewStringUTF(errorMessage.c_str());

    jobject jGraphResult = env->NewObject(graphResultClass, graphResultConstructor, jXValues, jYValues, jErrorMessage);

    return jGraphResult;
 }
