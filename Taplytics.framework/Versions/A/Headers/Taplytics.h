//
//  Taplytics.h
//  Taplytics
//
//  Copyright (c) 2014 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TaplyticsManager.h"

typedef void(^TLExperimentBlock)(NSDictionary *variables);

@protocol TaplyticsDelegate <NSObject>

@optional
/** 
 Delegate method called when a experiment is changed, use this to call runCodeExperiment:withBaseline:variations: again
 in your code to test and visually see the different code experiments. Only neccisary for code experiments, visual experiments
 will update themselves.
 @param experimentName the name of the experiment
 @param variationName the name of the experiment varariation, nil if Baseline
 */
- (void)taplyticsExperimentChanged:(NSString*)experimentName variationName:(NSString*)variationName;

@end

@interface Taplytics : NSObject

/**
 Start the Taplytics SDK with your api key. the api key can be found in the 'project settings' page.
 @param apiKey your api key
 */
+ (void)startTaplyticsAPIKey:(NSString*)apiKey;

/**
 Start the Taplytics SDK with your api key. the api key can be found in the 'project settings' page.
 @param apiKey your api key
 @param options taplytics options dictionary, used for testing. Options inclue:
            - @{"liveUpdate":@NO} to force production mode, or @YES to force live update mode for testing.
            - @{"delayLoad":@2} allows Taplytics to show your launch image and load its configuration for a maximum number of seconds
                on app startup. This is useful when running experiments on the first screen of your app, so users will get shown a variation 
                on the first launch of your app.
 */
 
+ (void)startTaplyticsAPIKey:(NSString*)apiKey options:(NSDictionary*)options;

/**
 Updates Taplytics configuration in a background fetch, only avaliable in iOS 7. It is HIGHLY recomended to implement background fetch
 in your apps, to allow Taplytics to have an upto date configuration on app launch.
 @param completionBlock completion block called when fetch is complete
 */
+ (void)performBackgroundFetch:(void(^)(UIBackgroundFetchResult result))completionBlock NS_AVAILABLE_IOS(7_0);

/**
 Optionally set the taplytics delegate when you need to know when a experiment has changed. For example if you are testing 
 a code experiment on your root view and want to visually see the different variations.
 @param delegate
 */
+ (void)setTaplyticsDelegate:(id<TaplyticsDelegate>)delegate;

/**
 Run code experiment with experiment defined by experimentName, one baseline or variation block will be run synchronously.
 If the "delayLoad" option is set in the options dictionary of startTaplyticsAPIKey:options: the block will be called asynchronously
 once the Taplytics configuration has been loaded, but before the launch image is hidden.
 
 If no experiment has been defined or no configuration has been loaded the baseline block will be called. 
 Variation blocks are defined in a NSDictionary with a key of the variation name, and a value of TLExperimentBlock. For Example:
 
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
 DEPRECATED Start Taplytics Methods, please use startTaplyticsAPIKey:options:
 */
+ (void)startTaplyticsAPIKey:(NSString*)apiKey liveUpdate:(BOOL)liveUpdate __deprecated;

+ (void)startTaplyticsAPIKey:(NSString*)apiKey server:(TLServer)server __deprecated;

+ (void)startTaplyticsAPIKey:(NSString*)apiKey server:(TLServer)server liveUpdate:(BOOL)liveUpdate __deprecated;

@end