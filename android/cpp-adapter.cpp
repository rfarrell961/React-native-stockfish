#include <jni.h>
#include "react-native-stockfish.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_stockfish_StockfishModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
    return stockfish::multiply(a, b);
}
