#import "Stockfish.h" 

@implementation StockfishRN
{
    bool hasListeners;
    stockfish::EngineBridge * _engineBridge;   
}

// Implement the singleton method
+ (instancetype)sharedInstance {
    static StockfishRN *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    return sharedInstance;
}


// Will be called when this module's first listener is added.
-(void)startObserving {
    NSLog(@"Start Observing");
    hasListeners = YES;
    // Set up any upstream listeners or background tasks as necessary
}

// Will be called when this module's last listener is removed, or on dealloc.
-(void)stopObserving {
    NSLog(@"STOP observing");
    hasListeners = NO;
    // Remove upstream listeners, stop unnecessary background tasks
}

-(void)onEngineResponse : (NSString*)response
{
  if (hasListeners) {// Only send events if anyone is listening
    [self sendEventWithName:@"EngineResponse" body:response];
  }
}

-(id)init {
    _engineBridge = new stockfish::EngineBridge();
    return self;
}

-(void)setMyCPP:(stockfish::EngineBridge*)newVal {
    @synchronized(self) {
        delete _engineBridge;  // it's OK to delete a NULL pointer
        _engineBridge = newVal;
    }
}

-(stockfish::EngineBridge*)engineBridge {
    return _engineBridge;
}

-(void)dealloc {
    puts("De-allocating EngineBridge.");
    delete _engineBridge;
}

// Implement supportedEvents method to specify event names
- (NSArray<NSString *> *)supportedEvents {
    return @[];//return @[@"EngineResponse"]; // List the event names that will be sent to JavaScript
}

RCT_EXPORT_MODULE()

// Example method
// See // https://reactnative.dev/docs/native-modules-ios
RCT_EXPORT_METHOD(init: (RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    _engineBridge->init();
}

RCT_EXPORT_METHOD(write:(NSString*)s
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"Writing");
    std::string value([s UTF8String]);
    _engineBridge->stockfish_write(value);
}

RCT_EXPORT_METHOD(read: (RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    std::string str = _engineBridge->stockfish_read();
    NSString* test = [NSString stringWithUTF8String:str.c_str()];
    resolve(test);
}

@end
