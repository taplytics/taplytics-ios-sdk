//
//  LaunchPadManager.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"
#import "LPProperties.h"

typedef enum {
    LPDev,
    LPProduction,
    LPLocalHost,
    LPLocalTest
} LPServer;

@protocol LaunchPadDelegate <NSObject>

@optional
- (void)launchPadUpdated;

- (void)launchPadThemeChanged:(NSString*)themeName;

@end

@interface LaunchPadManager : NSObject

@property (nonatomic, weak) id<LaunchPadDelegate> delegate;
@property (nonatomic) BOOL isLoadingProperties;
@property (nonatomic) BOOL liveUpdate;
// Loaded LaunchPad Properties
@property (nonatomic, strong) LPProperties* lpProperties;
@property (nonatomic) LPServer lpServer;

// Get Singleton LaunchPadManager Object
+ (LaunchPadManager*)sharedManager;

// Start LaunchPad With API Key Methods
+ (void)startLaunchPadAPIKey:(NSString*)apiKey liveUpdate:(BOOL)liveUpdate;

+ (void)startLaunchPadAPIKey:(NSString*)appID server:(LPServer)server liveUpdate:(BOOL)liveUpdate;

// Update LaunchPad Properties in Background, only iOS7 and higher
#ifdef SYSTEM_IOS7_OR_GREATER
- (void)performBackgroundFetch:(void(^)(UIBackgroundFetchResult))completionBlock;
#endif

// Element Life Cycle Methods
- (void)elementInit:(id<LPElementProtocol>)element;

- (void)elementDealloc:(id<LPElementProtocol>)element;

- (void)element:(id<LPElementProtocol>)element setState:(NSString*)stateName;

// Change the LaunchPad Server
- (void)setLPServer:(LPServer)server;

- (void)checkLoadedElementsWithNewPropertiesChanges:(NSDictionary*)changes;

// Setting ViewController Appearance
- (void)setupViewController:(UIViewController*)vc forViewKey:(NSString*)viewKey;

@end
