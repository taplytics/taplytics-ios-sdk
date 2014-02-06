//
//  Taplytics.h
//  Taplytics
//
//  Copyright (c) 2014 Syrp Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TaplyticsManager.h"

typedef void(^TLExperimentBlock)(NSDictionary *variables);

@interface Taplytics : NSObject

/**
 Start the Taplytics SDK with your api key. the api key can be found in the 'project settings' page.
 @param apiKey your api key
 @param options Options dictionary, used for testing, can be nil
 */
+ (void)startTaplyticsAPIKey:(NSString*)apiKey;

+ (void)startTaplyticsAPIKey:(NSString*)apiKey options:(NSDictionary*)options;

/**
 Run code experiment with experiment defined by experimentName, one baseline block or variation block will be run synchronously.
 If no experiment has been defined the baseline block will be called. variation blocks are defined in a NSDictionary
 with a key of the variation name, and a value of TLExperimentBlock. For Example:
 
 [Taplytics runCodeExperiment:@"testExperiment" withBaseline:^(NSDictionary *variables) {
 
 } variations:@{@"variation1": ^(NSDictionary *variables) {
 
 }, @"variation2": ^(NSDictionary *variables) {
 
 }}];
 */
+ (void)runCodeExperiment:(NSString*)experimentName withBaseline:(TLExperimentBlock)baselineBlock variations:(NSDictionary*)variationNamesAndBlocks;

/**
 Report that an experiment goal has been achieved, optionally pass number value to track goal such as purchase revenue.
 */
+ (void)goalAchieved:(NSString*)goalName;

+ (void)goalAchieved:(NSString*)goalName value:(NSNumber*)value;

/**
 Updates Taplytics experiment properties in a background fetch, only avaliable in iOS 7
 @param completionBlock completion block called when fetch is complete
 */
#if __IPHONE_OS_VERSION_MIN_REQUIRED >= 70000
+ (void)performBackgroundFetch:(void(^)(UIBackgroundFetchResult))completionBlock;
#endif

/**
 DEPRECATED Start Taplytics Methods, please use startTaplyticsAPIKey:options:
 */
+ (void)startTaplyticsAPIKey:(NSString*)apiKey liveUpdate:(BOOL)liveUpdate __deprecated;

+ (void)startTaplyticsAPIKey:(NSString*)apiKey server:(TLServer)server __deprecated;

+ (void)startTaplyticsAPIKey:(NSString*)apiKey server:(TLServer)server liveUpdate:(BOOL)liveUpdate __deprecated;

@end