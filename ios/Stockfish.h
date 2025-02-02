#ifdef __cplusplus
#import "react-native-stockfish.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNStockfishSpec.h"
#import <React/RCTEventEmitter.h>

@interface StockfishRN : RCTEventEmitter <NativeStockfishSpec>

#else
#import <React/RCTBridgeModule.h>
#import <React/RCTEventEmitter.h>

@interface StockfishRN : RCTEventEmitter <RCTBridgeModule>

#endif

+ (instancetype)sharedInstance;
// Declare the method that will be triggered from C++
- (void)onEngineResponse:(NSString *)eventData;

@end
