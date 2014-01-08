//
//  TaplyticsManager.h
//  Taplytics
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TLElementProtocol.h"
#import "TLProperties.h"

typedef enum {
    TLDev,
    TLProduction,
    TLLocalHost,
    TLLocalTest
} TLServer;

@protocol TaplyticsDelegate <NSObject>

@optional
- (void)TaplyticsUpdated;

- (void)TaplyticsThemeChanged:(NSString*)themeName;

@end

@interface TaplyticsManager : NSObject

@property (nonatomic, weak) id<TaplyticsDelegate> delegate;
@property (nonatomic) BOOL isLoadingProperties;
@property (nonatomic) BOOL liveUpdate;
// Loaded Taplytics Properties
@property (nonatomic, strong) TLProperties* tlProperties;
@property (nonatomic) TLServer server;

// Get Singleton TaplyticsManager Object
+ (TaplyticsManager*)sharedManager;

// Start Taplytics With API Key Methods
+ (void)startTaplyticsAPIKey:(NSString*)apiKey liveUpdate:(BOOL)liveUpdate;

+ (void)startTaplyticsAPIKey:(NSString*)appID server:(TLServer)server liveUpdate:(BOOL)liveUpdate;

// Update Taplytics Properties in Background, only iOS7 and higher
- (void)performBackgroundFetch:(void(^)(UIBackgroundFetchResult))completionBlock;

// Element Life Cycle Methods
- (void)elementInit:(id<TLElementProtocol>)element;

- (void)elementDealloc:(id<TLElementProtocol>)element;

- (void)element:(id<TLElementProtocol>)element setState:(NSString*)stateName;

// Change the Taplytics Server
- (void)setTLServer:(TLServer)server;

- (void)checkLoadedElementsWithNewPropertiesChanges:(NSDictionary*)changes;

// Setting ViewController Appearance
- (void)setupViewController:(UIViewController*)vc forViewKey:(NSString*)viewKey;

- (void)highlightElementforKey:(NSString*)elementKey styleKey:(NSString*)styleKey duration:(NSNumber*)duration;

@end
