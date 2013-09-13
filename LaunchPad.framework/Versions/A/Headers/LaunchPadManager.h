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
    LPLocalHost
} LPServer;

@protocol LaunchPadDelegate <NSObject>

- (void)launchPadUpdated;

- (void)launchPadThemeChanged:(NSString*)themeName;

@end

@interface LaunchPadManager : NSObject

@property (nonatomic, weak) id<LaunchPadDelegate> delegate;
@property (nonatomic) BOOL isLoadingProperties;
@property (nonatomic) BOOL isTesting;
// Loaded Side Step Properties
@property (nonatomic, strong) LPProperties* lpProperties;
@property (nonatomic) LPServer lpServer;

+ (LaunchPadManager*)sharedManager;

+ (void)startLaunchPadAPIKey:(NSString*)apiKey isTesting:(BOOL)isTesting;

+ (void)startLaunchPadAPIKey:(NSString*)appID server:(LPServer)server isTesting:(BOOL)isTesting;

- (void)elementInit:(id<LPElementProtocol>)element;

- (void)elementDealloc:(id<LPElementProtocol>)element;

- (void)element:(id<LPElementProtocol>)element setState:(NSString*)stateName;

- (void)setLPServer:(LPServer)server;

#pragma mark - Setting Element Values
- (BOOL)setValueInElement:(NSObject*)element lpElement:(id<LPElementProtocol>)lpElement fromValue:(id)value key:(NSString *)key;

- (void)setValuesInElement:(NSObject<LPElementProtocol>*)element propertiesDic:(NSDictionary*)propertiesDic;

@end
