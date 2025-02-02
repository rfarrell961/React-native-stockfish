#ifndef CPP_BRIDGE_H
#define CPP_BRIDGE_H

#ifdef __cplusplus
extern "C" {
#endif

// Declare the function to be used in C++ code
void triggerReactEventFromCpp(const char* eventData);

#ifdef __cplusplus
}
#endif

#endif // CPP_BRIDGE_H

