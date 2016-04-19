//
//  Taplytics.h
//  Taplytics v2.10.18
//
//  Copyright (c) 2015 Taplytics Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TaplyticsOptions.h"
#import "TaplyticsVar.h"

typedef void(^TLCodeBlock)(void);

typedef void(^TLExperimentBlock)(NSDictionary *variables);

typedef void(^TLVariationBlock)(NSString* variationName, NSDictionary *variables);

typedef void(^TLRunningExperimentsAndVariationsBlock)(NSDictionary *experimentsAndVariations);

typedef void(^TLPropertiesLoadedBlock)(BOOL loaded);


@protocol TaplyticsDelegate <NSObject>

@optional
/** 
 Delegate method called when an experiment is changed, use this to call runCodeExperiment:withBaseline:variations: again
 in your code to test and visually see the different code experiments. Only necessary for code experiments, visual experiments
 will update themselves.
 @param experimentName The name of the experiment
 @param variationName The name of the experiment variation, nil if Baseline
 */
- (void)taplyticsExperimentChanged:(NSString*)experimentName variationName:(NSString*)variationName;

@end


@interface Taplytics : NSObject

#pragma mark - Starting Taplytics

/**
 Start the Taplytics SDK with your api key. the api key can be found in the 'project settings' page. 
 
 On the first launch of your app Taplytics will show your launch image for a maximum of two seconds, this gives Taplytics time 
 to download your experiment's configuration and display the experiment's changes to your users. In subsequent launches of your 
 app Taplytics will use the experiment's configuration from disk, and not show your launch image. If you do not want this behavior, use:
 [Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{@"delayLoad":@0}];
 
 Console Logging: Taplytics will only log to the console in development builds.
 @param apiKey your api key
 */
+ (void)startTaplyticsAPIKey:(NSString*)apiKey;

/**
 Start the Taplytics SDK with your api key. the api key can be found in the 'project settings' page.
 
 On the first launch of your app Taplytics will show your launch image for a maximum of two seconds, this gives Taplytics time
 to download your experiment's configuration and display the experiment's changes to your users. In subsequent launches of your
 app Taplytics use the experiment's configuration from disk, and not show your launch image. If you do not want this behavior, use:
 [Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{@"delayLoad":@0}];
 
 Console Logging: Taplytics will only log to the console in development builds.
 @param apiKey Your API key
 @param options Taplytics options dictionary, used for testing. Options include:
            - @{@"delayLoad":@2} allows Taplytics to show your app's launch image and load its configuration for a maximum number of seconds
                on app launch, the default for first launch is 2 seconds. This is useful when running a code experiments on the first screen 
                of your app, this will ensure that your users will get shown a variation on the first launch of your app. Set to @0 for no
                delay.
            - @{@"liveUpdate":@NO} Taplytics will auto-detect an app store build or a development build. But to force production mode use @NO,
                or @YES to force live update mode for testing.
            - @{@"shakeMenu":@NO} To disable the Taplytics development mode shake menu set @NO, only use if you have your own development shake menu.
            - @{@"disable":@[TaplyticsDisableTrackLocation]} To disable any tracking attributes set a @"disable" key with an array of values to disable from
                TaplyticsOptions.h
 */
+ (void)startTaplyticsAPIKey:(NSString*)apiKey options:(NSDictionary*)options;


/**
 Optionally set the taplytics delegate when you need to know when a experiment has changed. For example if you are testing 
 a code experiment on your root view and want to visually see the different variations.
 @param delegate The delegate for the receiver. The delegate must implement the TaplyticsDelegate protocol.
 */
+ (void)setTaplyticsDelegate:(id<TaplyticsDelegate>)delegate;

#pragma mark - Code Experiments

/**
 Run a code block that can be attached to any experiment through the Taplytics website. The code block will either be
 run or not run based on the configuration of the experiment through Taplytics.
 
 On the first launch of your app the execution will be delayed and will be called asynchronously on the main thread
 once the Taplytics configuration has been loaded, but before the launch image is hidden.
 
 The code block will only be run once, so in testing, when you want to switch between variations you will want to implement
 the TaplyticsDelegate to run your code block again to see the feature enabled. If you don't implement the TaplyticsDelegate
 you will only be able to see the code block run specifically when your device falls into the relevant segmentation.
 
 [Taplytics runCodeBlock:@"enableFeature" forBlock:^{
    // enable your feature here
 }];
 
 @param name unique name of the codeblock
 @param codeBlock the code block will be called depending on the rules setup by the experiment it is attached to. returns on main thread.
 */

+ (void)runCodeBlock:(NSString*)name forBlock:(TLCodeBlock)codeBlock;

/**
 Run a code experiment defined by experimentName, one baseline or variation block will be run synchronously.
 On the first launch of your app the execution will be delayed and will be called asynchronously on the main thread
 once the Taplytics configuration has been loaded, but before the launch image is hidden.
 
 If no experiment has been defined or no configuration has been loaded the baseline block will be called. 
 Variation blocks are defined in a NSDictionary with a key of the variation name, and a value of TLExperimentBlock. For Example:
 
 [Taplytics runCodeExperiment:@"testExperiment" withBaseline:^(NSDictionary *variables) {
 
 } variations:@{@"variation1": ^(NSDictionary *variables) {
 
 }, @"variation2": ^(NSDictionary *variables) {
 
 }}];
 
 @param experimentName Name of the experiment to run
 @param baselineBlock Baseline block called if experiment is in baseline variation. Returns on incoming thread if synchronous, returns on main thread if asynchronous.
 @param variationNamesAndBlocks NSDictionary with keys of variation names and values of variation blocks. Returns on incoming thread if synchronous, returns on main thread if asynchronous.
 */
+ (void)runCodeExperiment:(NSString*)experimentName
             withBaseline:(TLExperimentBlock)baselineBlock
               variations:(NSDictionary*)variationNamesAndBlocks
                DEPRECATED_MSG_ATTRIBUTE("Use [Taplytics runCodeBlock:] instead, codeblocks now reusable between experiments");

/**
 Use this method when running code experiments in Swift, due to how blocks/closures are handled in Swift 
 passing blocks/closures in an NSDictioary is not supported well. This method will return to either the baselineBlock
 or the variationBlock with the variation's name. The blocks are called in the same manner as explained in 
 runCodeExperiment:withBaseline:variations:
 
 Using this method in Swift:
 Taplytics.runCodeExperiment("testExperiment",
    forBaseline: { variables in
        let myVar0: NSNumber? = variables?["var"] as? NSNumber
        println("Baseline, variable: \(myVar0)")
    },
    forVariation: { variationName, variables in
        let myVar0: NSNumber? = variables?["var"] as? NSNumber
        if variationName == "variation1" {
            println("variation 1, variable: \(myVar0)")
        }
        else if variationName == "variation2" {
            println("variation2, variable: \(myVar0)")
        }
    }
 )
 
 @param experimentName Name of the experiment to run
 @param baselineBlock Baseline block called if experiment is in baseline variation. Returns on incoming thread if synchronous, returns on main thread if asynchronous.
 @param variationBlock Variation block called when the experiment is running a variation. Returns on incoming thread if synchronous, returns on main thread if asynchronous.
 */
+ (void)runCodeExperiment:(NSString*)experimentName
              forBaseline:(TLExperimentBlock)baselineBlock
             forVariation:(TLVariationBlock)variationBlock
                DEPRECATED_MSG_ATTRIBUTE("Use [Taplytics runCodeBlock:] instead, codeblocks now reusable between experiments");

#pragma mark - Event Logging

/**
 Log an event to Taplytics, these events can be used as goals in your experiments.
 
 @param eventName the name of the event
 */
+ (void)logEvent:(NSString*)eventName;

/**
 Log an event to Taplytics with an optional number value and optional metadata, these events can be used as goals in your experiments.
 
 @param eventName the name of the event
 @param value an optional number value to quantify your event
 @param metaData an optional dictionary of metaData to attach to your event. Keep the values of this dictionary flat.
 @warning the metaData can only be values allowed by NSJSONSerialization.
 */
+ (void)logEvent:(NSString *)eventName value:(NSNumber*)value metaData:(NSDictionary*)metaData;

/**
 Log revenue to Taplytics with a revenue value, these events can be used as goals in your experiments.
 
 @param eventName the name of the revenue event
 @param value an optional number value to quantify your event
 */
+ (void)logRevenue:(NSString*)eventName revenue:(NSNumber*)value;

/**
 Log revenue to Taplytics with a revenue value and optional metadata, these events can be used as goals in your experiments.
 
 @param eventName the name of the revenue event
 @param value an optional number value to quantify your event
 @param metaData an optional dictionary of metaData to attach to your event. Keep the values of this dictionary flat.
 @warning the metaData can only be values allowed by NSJSONSerialization.
 */
+ (void)logRevenue:(NSString*)eventName revenue:(NSNumber*)value metaData:(NSDictionary*)metaData;

#pragma mark - User Attributes

/**
 Settings User Attributes allows for submitting mutiple user attributes with custom values. 
 This allows you to set attributes such as a user_id, email, name, age, gender, ect. You can also set a dictionary
 of custom data for the user. The avaliable key-values are shown below:
 
    [Taplytics setUserAttributes: @{
        @"user_id": @"testUser",
        @"name": @"Test User",
        @"email": @"test@taplytics.com",
        @"gender": @"female",
        @"age": @25,
        @"avatarUrl": @"https://pbs.twimg.com/profile_images/497895869270618112/1zbNvWlD.png",
        @"customData": @{
            @"paidSubscriber": @YES,
            @"purchases": @3,
            @"totalRevenue": @42.42
        }
    }];
 
 @param attributes is a dictionary of user attributes that can be used to segment your users against.
 @warning Attributes can only be values allowed by NSJSONSerialization.
*/
+ (void)setUserAttributes:(NSDictionary*)attributes;

/**
 This method will reset the User to a new empty user, this method is intended to be used when your user logs out of an account. 
 This method will also disable sending push notifications to this device for the previous user. 
 Call registerPushNotifications again to register push notifications for the new user.
 @param callback called when Taplytics has completed resetting your user.
 */
+ (void)resetUser:(void(^)(void))callback;

/**
 This method will return the current user attributes for the user.
 @param callback NSDictionary of user attributes returned when Taplytics has loaded properties from our servers.
 */
+ (void)getUserAttributes:(void(^)(NSDictionary* userAttributes))callback;

#pragma mark - Push Notifications

/**
 Register for push notification access, this method will show the iOS permissions alert asking for access to send push notifications.
 This method will register for Badge, Sound, and Alert notification types
 */
+ (void)registerPushNotifications;

/**
 Register for push notification access, this method will show the iOS permissions alert asking for access to send push notifications.
 @param types accepts both UIUserNotificationType (iOS 8) or UIRemoteNotificationType
 */
+ (void)registerPushNotificationsWithTypes:(NSInteger)types;

/**
 Registers for location access, this method will show the iOS permissions alert asking for location access. 
 Location permissions are required for location based push notifications. We request kCLAuthorizationStatusAuthorizedAlways access
 so that we can monitor regions for your location based push notifications.
 */
+ (void)registerLocationAccess;

/**
 Register for push notification access, this method will show the iOS alert asking for access to send push notifications.
 @param types accepts both UIUserNotificationType (iOS 8) or UIRemoteNotificationType
 @param categories accepts a NSSet of UIUserNotificationCategory settings
 */
+ (void)registerPushNotificationsWithTypes:(NSInteger)types categories:(NSSet*)categories;

/**
 @return if the the user is registered with Taplytics and iOS for push notifications.
 */
+ (BOOL)isUserRegisteredForPushNotifications;

#pragma mark - Utility Functions

/**
 @return if Taplytics is currently loading properties from our servers
 */
+ (BOOL)isLoadingPropertiesFromServer;

/**
 This block will be called asynchronously when the SDK has loaded properties from the server, or return synchronously if properties have already been loaded.
 
 @param block loaded callback block
 */
+ (void)propertiesLoadedCallback:(TLPropertiesLoadedBlock)block;


/**
 Get a NSDictionary of all running experiments and their current variation. This block will return async on the main thread once the experiment
 configuration has loaded from our servers, or synchronously if the configuration has already loaded. Example of a NSDictionary that is returned:
 
 NSDictionary* experimentsAndVariations = @{
 @"Experiment 1": @"baseline",
 @"Experiment 2": @"Variation 1"
 };
 
 @param block This block will be called back with a NSDictionary with key value of experiment name and value of it's variation name. Returns on main thread.
 */
+ (void)getRunningExperimentsAndVariations:(TLRunningExperimentsAndVariationsBlock)block;

/**
 Updates Taplytics configuration in a background fetch. It is HIGHLY recommended to implement background fetch
 in 'application:performFetchWithCompletionHandler:' in your UIApplicationDelegate, to allow Taplytics to update its configuration regularly.
 For Example:
 
 - (void)application:(UIApplication *)app performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completeBlock {
 [Taplytics performBackgroundFetch:completeBlock];
 }
 
 @param completionBlock Completion block called when fetch is complete, returns on main thread.
 */
+ (void)performBackgroundFetch:(void(^)(UIBackgroundFetchResult result))completionBlock;

@end

