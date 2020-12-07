//
//  Taplytics.h
//  Taplytics v3.3.0
//
//  Copyright © 2020 Taplytics. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TaplyticsOptions.h"
#import "TaplyticsVar.h"

typedef void(^TLCodeBlock)(void);

typedef void(^TLRunningExperimentsAndVariationsBlock)(NSDictionary* _Nonnull experimentsAndVariations);

typedef void(^TLRunningFeatureFlagsBlock)(NSDictionary* _Nonnull featureFlags);

typedef void(^TLSetUserAttributesBlock)(void);

typedef void(^TLStartPropertiesLoadedBlock)(BOOL loaded);

typedef void(^TLNewSessionBlock)(BOOL loaded);

typedef void(^TLPropertiesLoadedBlock)(BOOL loaded);

typedef void(^TLBackgroundFetchBlock)(UIBackgroundFetchResult result);

typedef void(^TLGetSessionInfoBlock)(NSDictionary* _Nonnull sessionInfo);

typedef void(^TLStartNewSessionBlock)(BOOL success);

typedef void(^TLResetUserBlock)(void);


@protocol TaplyticsDelegate <NSObject>

@optional
/** 
 Delegate method called when an experiment is changed, use this to call runCodeBlock:forBlock: again
 in your code to test and visually see the different code experiments. Only necessary for code blocks, visual experiments
 will update themselves.
 @param experimentName The name of the experiment
 @param variationName The name of the experiment variation, nil if Baseline
 */
- (void)taplyticsExperimentChanged:(nullable NSString*)experimentName variationName:(nullable NSString*)variationName;

/**
 This delegate method will be called every time the SDK starts a new session including; on the first launch, when startNewSession: is called, or when a new userId is set.
 Note that this method can callback multiple times.
 
 Threading: This delegate method will be called from the main thread.
 
 @param loaded will be true when properties have been loaded sucessfully or false when the "delayLoad" timeout has been reached.
 */
- (void)taplyticsNewSession:(BOOL)loaded;

@end


@interface Taplytics : NSObject

- (instancetype _Nonnull)init NS_SWIFT_UNAVAILABLE("Remove exposure of init");

#pragma mark - Starting Taplytics

/**
 Start the Taplytics SDK with your api key. the api key can be found in the 'project settings' page. 
 
 On the first launch of your app Taplytics will show your launch image for a maximum of two seconds, this gives Taplytics time 
 to download your experiment's configuration and display the experiment's changes to your users. In subsequent launches of your 
 app Taplytics will use the experiment's configuration from disk, and not show your launch image. If you do not want this behavior, use:
 [Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{@"delayLoad":@0}];
 
 Console Logging: Taplytics will only log to the console in development builds.
 
 Threading: This method should be called from the main thread, will dispatch_sync to the main thread if not.
 
 @param apiKey Your API key
 @param options Taplytics options dictionary, used for testing. Options include:
            - @{@"delayLoad":@4} allows Taplytics to show your app's launch image and load its configuration for a maximum number of seconds
                on app launch, the default for first launch is 4 seconds. This is useful when running code experiments on the first screen
                of your app, this will ensure that your users will get shown a variation on the first launch of your app. Set to @0 for no
                delay.
            - @{@"liveUpdate":@NO} Taplytics will auto-detect an app store build or a development build. But to force production mode use @NO,
                or @YES to force live update mode for testing.
            - @{@"shakeMenu":@NO} To disable the Taplytics development mode shake menu set @NO, only use if you have your own development shake menu.
            - @{@"disable":@[TaplyticsDisableTrackLocation]} To disable any tracking attributes set a @"disable" key with an array of values to disable from
                TaplyticsOptions.h
 @param callback This callback will be triggered once, with a "loaded" bool true when properties have been loaded successfully or false when the "delayLoad" timeout has been reached.
 
 */
+ (void)startTaplyticsAPIKey:(nonnull NSString*)apiKey options:(nullable NSDictionary*)options callback:(nullable TLStartPropertiesLoadedBlock)callback;

+ (void)startTaplyticsAPIKey:(nonnull NSString*)apiKey options:(nullable NSDictionary*)options;

+ (void)startTaplyticsAPIKey:(nonnull NSString*)apiKey callback:(nullable TLStartPropertiesLoadedBlock)callback;

+ (void)startTaplyticsAPIKey:(nonnull NSString*)apiKey;

/**
 Optionally set the taplytics delegate when you need to know when a experiment has changed. For example if you are testing 
 a code experiment on your root view and want to visually see the different variations.
 
 Threading: This method is thread-safe.
 
 @param delegate The delegate for the receiver. The delegate must implement the TaplyticsDelegate protocol.
 */
+ (void)setTaplyticsDelegate:(nullable id<TaplyticsDelegate>)delegate;

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
 
 Threading: This method is thread-safe.

 @param name unique name of the codeblock
 @param codeBlock the code block will be called depending on the rules setup by the experiment it is attached to. returns on main thread.
 */

+ (void)runCodeBlock:(nonnull NSString*)name forBlock:(nonnull TLCodeBlock)codeBlock;

#pragma mark - Event Logging

/**
 Log an event to Taplytics, these events can be used as goals in your experiments.
 
 Threading: This method is thread-safe.

 @param eventName the name of the event
 */
+ (void)logEvent:(nonnull NSString*)eventName;

/**
 Log an event to Taplytics with an optional number value and optional metadata, these events can be used as goals in your experiments.
 
 Threading: This method is thread-safe.

 @param eventName the name of the event
 @param value an optional number value to quantify your event
 @param metaData an optional dictionary of metaData to attach to your event. Keep the values of this dictionary flat.
 @warning the metaData can only be values allowed by NSJSONSerialization.
 */
+ (void)logEvent:(nonnull NSString *)eventName value:(nullable NSNumber*)value metaData:(nullable NSDictionary*)metaData;

/**
 Log revenue to Taplytics with a revenue value, these events can be used as goals in your experiments.
 
 Threading: This method is thread-safe.

 @param eventName the name of the revenue event
 @param value an optional number value to quantify your event
 */
+ (void)logRevenue:(nonnull NSString*)eventName revenue:(nonnull NSNumber*)value;

/**
 Log revenue to Taplytics with a revenue value and optional metadata, these events can be used as goals in your experiments.
 
 Threading: This method is thread-safe.

 @param eventName the name of the revenue event
 @param value an optional number value to quantify your event
 @param metaData an optional dictionary of metaData to attach to your event. Keep the values of this dictionary flat.
 @warning the metaData can only be values allowed by NSJSONSerialization.
 */
+ (void)logRevenue:(nonnull NSString*)eventName revenue:(nonnull NSNumber*)value metaData:(nullable NSDictionary*)metaData;

# pragma mark - Feature Flags

/**
 Determine if a Feature Flag is enabled for this user's device, the method will return true if the Feature Flag is enabled. Feature Flags can be set up through the Taplytics dashboard, pass in the key for the Feature Flag as set up in the Taplytics Dashboard.
 
 Threading: This method is thread-safe.

 @return if feature flag for key is enabled
 
 @param key of feature flag to check
 */
+ (BOOL)featureFlagEnabled:(nullable NSString*)key;

/**
 Determine if a Feature Flag is enabled for this user's device, the method will return true if the Feature Flag is enabled. Feature Flags can be set up through the Taplytics dashboard, pass in the key for the Feature Flag as set up in the Taplytics Dashboard.
 
 Threading: This method is thread-safe.

 @return if feature flag for key is enabled
 
 @param key of feature flag to check
 @param defaultValue the default value of the feature flag. If there is no connection or the feature flag does not load then default value will be returned
 */
+ (BOOL)featureFlagEnabled:(nullable NSString*)key defaultValue:(BOOL)defaultValue;

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
 
 Threading: This method should be called from the main thread, will dispatch_sync to main thread if not.

 @param attributes is a dictionary of user attributes that can be used to segment your users against.
 @warning Attributes can only be values allowed by NSJSONSerialization.
*/
+ (void)setUserAttributes:(nullable NSDictionary*)attributes;

/**
 Similar to setUserAttributes but with an added callback parameter.

 Threading: This method should be called from the main thread, will dispatch_sync to main thread if not.

 @param attributes is a dictionary of user attributes that can be used to segment your users against.
 @param callback called when setUserAttributes is completely done.
 @warning Attributes can only be values allowed by NSJSONSerialization.
 */
+ (void)setUserAttributes:(nullable NSDictionary*)attributes withCallback:(nullable TLSetUserAttributesBlock)callback;

/**
 This method will reset the User to a new empty user, this method is intended to be used when your user logs out of an account. 
 This method will also disable sending push notifications to this device for the previous user. 
 Call registerPushNotifications again to register push notifications for the new user.
 
 Threading: This method should be called from the main thread, will dispatch_sync to main thread if not.

 @param callback called when Taplytics has completed resetting your user.
 */
+ (void)resetUser:(nullable TLResetUserBlock)callback;

/**
 This method will return the current session info for the user.
 
 Threading: This method is thread-safe.

 @param callback NSDictionary of user session info returned when Taplytics has loaded properties from our servers.
 This NSDictionary contains two keys: appUser_id and session_id
 */
+ (void)getSessionInfo:(nonnull TLGetSessionInfoBlock)callback;

/**
 End the current user session and create a new session. Calls taplytics to retrieve new experiment data if any.
 
 Threading: This method is thread-safe, callback will return on main thread.

 @param callback called when the new session has begun.
 */
+ (void)startNewSession:(nullable TLStartNewSessionBlock)callback;

#pragma mark - User Tracking

/**
 Calling this method will disable all user tracking.
 
 Threading: This method should be called from the main thread, will dispatch_async to main thread if not.
 */
+ (void)optOutUserTracking;

/**
 Calling this method will re-enable user tracking.
 
 Threading: This method should be called from the main thread, will dispatch_async to main thread if not.
 */
+ (void)optInUserTracking;

/**
 @return if the user has opted out of user tracking.
 
 Threading: This method is thread-safe.
 */
+ (BOOL)hasUserOptedOutTracking;

#pragma mark - Push Notifications

/**
 Register for push notification access, this method will show the iOS permissions alert asking for access to send push notifications.
 This method will register for Badge, Sound, and Alert notification types
 
 Threading: This method should be called from the main thread, will dispatch_sync to main thread if not.
 */
+ (void)registerPushNotifications;

/**
 Register for push notification access, this method will show the iOS alert asking for access to send push notifications.
 
 Threading: This method should be called from the main thread, will dispatch_sync to main thread if not.

 @param types accepts UIUserNotificationType
 @param categories accepts a NSSet of UIUserNotificationCategory settings
 */
+ (void)registerPushNotificationsWithTypes:(NSInteger)types categories:(nullable NSSet*)categories;

/**
 Registers for location access, this method will show the iOS permissions alert asking for location access.
 Location permissions are required for location based push notifications. We request kCLAuthorizationStatusAuthorizedAlways access
 so that we can monitor regions for your location based push notifications.
 
 Threading: This method should be called from the main thread, will dispatch_async to main thread if not.
 */
+ (void)registerLocationAccess;

/**
 @return if the the user is registered with Taplytics and iOS for push notifications.
 
 Threading: This method is thread-safe.
 */
+ (BOOL)isUserRegisteredForPushNotifications;

#pragma mark - Utility Functions

/**
 Show the experiment / variation menu. Useful for QA testing when shaking the device is not possible.
 
 Threading: This method should be called from the main thread, will dispatch_sync to main thread if not.
 */

+ (void)showMenu;

/**
 Threading: This method is thread-safe.

 @return if Taplytics is currently loading properties from our servers
 */
+ (BOOL)isLoadingPropertiesFromServer;

/**
 This callback will be called every time the SDK starts a new session, including on the first launch, when startNewSession: is called, or when a new userId is set.
 Note that this method can callback multiple times.
 
 Threading: This method is thread-safe. Callback will either be fired from current thread or main thread.

 @param block loaded callback block
 */
+ (void)newSessionCallback:(nonnull TLNewSessionBlock)callback;

/**
 This block will be called asynchronously when the SDK has loaded properties from the server, or return synchronously if properties have already been loaded.
 
 Threading: This method is thread-safe. Callback will either be fired from current thread or main thread.

 @param block loaded callback block
 */
+ (void)propertiesLoadedCallback:(nonnull TLPropertiesLoadedBlock)block __deprecated_msg("use newSessionCallback:");

/**
 Get a NSDictionary of all running experiments and their current variation. This block will return async on the main thread once the experiment
 configuration has loaded from our servers, or synchronously if the configuration has already loaded. Example of a NSDictionary that is returned:
 
 NSDictionary* experimentsAndVariations = @{
 @"Experiment 1": @"baseline",
 @"Experiment 2": @"Variation 1"
 };
 
 Threading: This method is thread-safe. Callback will either be fired from current thread or main thread.

 @param block This block will be called back with a NSDictionary with key value of experiment name and value of it's variation name. Returns on main thread.
 */
+ (void)getRunningExperimentsAndVariations:(nonnull TLRunningExperimentsAndVariationsBlock)block;

/**
 Get a NSDictionary of all running feature flags and their associated key. This block will return async on the main thread once the feature flag
 configuration has loaded from our servers, or synchronously if the configuration has already loaded. Example of a NSDictionary that is returned:
 
 NSDictionary* experimentsAndVariations = @{
 @"Feature Flag 1's Name": @"Feature Flag 1's Key",
 @"Feature Flag 2's Name": @"Feature Flag 2's Key"
 };
 
 Threading: This method is thread-safe. Callback will either be fired from current thread or main thread.

 @param block This block will be called back with a NSDictionary with key value of feature flag name and feature flag key. Returns on main thread.
 */
+ (void)getRunningFeatureFlags:(nonnull TLRunningFeatureFlagsBlock)block;

/**
 Updates Taplytics configuration in a background fetch. It is HIGHLY recommended to implement background fetch
 in 'application:performFetchWithCompletionHandler:' in your UIApplicationDelegate, to allow Taplytics to update its configuration regularly.
 For Example:
 
 - (void)application:(UIApplication *)app performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completeBlock {
 [Taplytics performBackgroundFetch:completeBlock];
 }
 
 Threading: This method should be called from the main thread, will dispatch_async to main thread if not.

 @param completionBlock Completion block called when fetch is complete, returns on main thread.
 */
+ (void)performBackgroundFetch:(nonnull TLBackgroundFetchBlock)completionBlock;


/**
 Shows the launch image while Taplytics updates its configuration in the background.
 This should ONLY be used in the case where the starting of Taplytics is delayed behind some network call.
 Taplytics will not automatically show the launch image in cases where Taplytics isn't immediately initialzed in 'application:didFinishLaunchingWithOptions:'
 
 Threading: This method is thread-safe.
 */
+ (void)showAsyncLaunchImageForMaxTime:(nonnull NSNumber*) maxTime;

@end

