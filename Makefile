CC = g++
CFLAGS = -fPIC
LIBS = -L$(JNI_DIR) -lcalc_core
JNI_INCLUDES = -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/darwin"
JNI_DIR = ./src/main/java/calc/CalcCoreJNILib
LIB_DIR = $(JNI_DIR)/calc_core
LIB_NAME = $(JNI_DIR)/libcalc_core.dylib
LIB_JNI = ./src/main/resources/libcalc_core_jni.dylib
JNI_CC = $(JNI_DIR)/CalcCoreJNI.cc

CPPFLAGS = -I ${JAVA_HOME}/include -I ${JAVA_HOME}/include/darwin

all: java_lib

lib:
	$(CC) -shared $(CFLAGS) -o $(LIB_NAME) $(LIB_DIR)/*.cc

java_lib: lib
	g++ -shared -o $(LIB_JNI) $(JNI_CC) $(LIBS) $(JNI_INCLUDES)

clean:
	$(RM) main *.so $(JNI_DIR)/*.dylib $(JNI_DIR)/*.class $(JNI_DIR)/*.log $(JNI_DIR)/dto/*.class *.class
