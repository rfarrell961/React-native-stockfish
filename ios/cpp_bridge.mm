#import "Stockfish.h"
#import "cpp_bridge.h"

void triggerReactEventFromCpp(const char* eventData) {
    // TO_DO: Fix
    // For now, use read
    return; 
    NSString *eventString = [NSString stringWithUTF8String:eventData];
    StockfishRN *instance = [StockfishRN sharedInstance];
    dispatch_async(dispatch_get_main_queue(), ^{
        [instance onEngineResponse:eventString];
    });
}