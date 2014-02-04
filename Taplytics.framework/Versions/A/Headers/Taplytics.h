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