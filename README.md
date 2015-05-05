# Taplytics iOS SDK

_Description: Taplytics is a native mobile A/B testing platform that allows you to create new tests and push them live without any code updates! Supports iOS 6-8_

## Project Setup

_How do I, as a developer, start using Taplytics?_ 

1. Sign up for a free account at Taplytics.com.
2. Install the SDK.
3. Create an experiment and push it live to your users!

## Resources
- [Taplytics SDK CocoaDocs Class Reference](http://cocoadocs.org/docsets/Taplytics)
- [Taplytics Docs](https://taplytics.com/docs)

## Installation Instructions 
#### CocoaPods Installation
1. Install using CocoaPods
    - Add a `Podfile` to the root of your project directory with the following:

        ```ruby
        platform :ios, '7.0'
        pod 'Taplytics'
        ```

    - Run pod install:
    
        ```
        pod install
        ```
    
    - Open your project's .xcworkspace file
    
2. Initialize the SDK by adding an import and the following line of code with your API key to your `UIApplicationDelegate`.

    
    ```objc
    #import <Taplytics/Taplytics.h>


    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
        ...
        [Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here"];
        ...
    }
    ```

#### Manual Installation

1. Download the SDK / clone into your app.
2. Load the Taplytics framework into your app.
3. Add the required frameworks:
    
    ```
    CFNetwork.framework
    Security.framework
    CoreTelephony.framework
    SystemConfiguration.framework
    MobileCoreServices.framework
    JavaScriptCore.framework
    libicucore.dylib
    ```
    
4. Add the `-ObjC` Linker flag to your project settings.
5. Initialize the SDK by adding a line of code with your API key in your `UIApplicationDelegate`.
    
    ```objc
    #import <Taplytics/Taplytics.h>
    ...
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
        ...
        [Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here"];
        ...
    }
    ```
    
#### App Linking

Optionally app linking allows you to pair your device to Taplytics via a link sent through email or text. This will enable your team to easily pair any build of your app to Taplytics.

1. First ensure that `application:openURL:` method is implemented in your `UIApplicationDelegate`

    ```objc
    - (BOOL)application:(UIApplication *)app openURL:(NSURL *)url sourceApplication:(NSString *)sourceApp annotation:(id)ann {
        return NO;
    }
    ```
    
2. [Get your Taplytics URL Scheme from your Project's Settings](https://taplytics.com/dashboard)

    ![Image of URL Scheme](http://taplytics.com/assets/docs/install-sdk/url-scheme.png)
    
3. Add Taplytics URL Type in XCode's Build Info panel, with Identifier: com.taplytics, add your Taplytics URL Scheme from above.

    ![Image Of XCode build info](http://taplytics.com/assets/docs/install-sdk/app-link.png)

## Code Experiment Instructions

Taplytics not only lets you run visual experiments with no code needed, the SDK also offers a code-based solution to running experiments in your app.

Code Experiments let you run different variations of your app with simple blocks. You can also set different variable values for each variation to be returned in the code blocks.

#### Objective-C Experiments

For example, an experiment named "Code Experiment #1" with a baseline return block, and two variation blocks. Within each block we can get a `numberValue` variable from the `variables` NSDictionary that can have a different value set for each variation.
    
```objc
[Taplytics runCodeExperiment:@"Code Experiment #1" withBaseline:^(NSDictionary *variables) {
    NSNumber* numberValue = variables[@"numberValue"];
    // Insert baseline experiment code here
} variations:@{@"Variation 1": ^(NSDictionary *variables) {
    NSNumber* numberValue = variables[@"numberValue"];
    // Insert Variation 1 variation code here
}, @"Variation 2": ^(NSDictionary *variables) {
    NSNumber* numberValue = variables[@"numberValue"];
    // Insert Variation 2 variation code here
}}];
```

#### Swift Experiments

Due to how blocks/closures are handled in Swift, passing blocks/closures in an NSDictioary as we do in `runCodeExperiment:withBaseline:variations:` is not well supported. The `runCodeExperiment:forBaseline:forVariation:` method handles the same functionality for Swift code.

For example the same code experiment in Objective-C from above, using Swift:

```swift
Taplytics.runCodeExperiment("Code Experiment #1",
    forBaseline: { variables in
        let numberValue: NSNumber? = variables?["numberValue"] as? NSNumber
        // Insert baseline experiment code here
    },
    forVariation: { variationName, variables in
        let numberValue: NSNumber? = variables?["numberValue"] as? NSNumber
        if variationName == "Variation 1" {
            // Insert Variation 1 variation code here
        }
        else if variationName == "Variation 2" {
            // Insert Variation 2 variation code here
        }
    }
)
```
    
#### Testing Codeblocks

Implementing the TaplyticsDelegate is not necessary to properly run code-based experiments. But with code experiments you will only see the changes when the runCodeExperiment block is actually excecuted, so when you switch between variations you might not see changes until the view has been reloaded. If you would like to see these changes when you change variations, you will have to implement the TaplyticsDelegate.

1. Add the TaplyticsDelegate to your Class

    ```objc
    #import <Taplytics/Taplytics.h>
    @interface SampleViewController : ViewController <TaplyticsDelegate>
    ```
2. Add the `taplyticsExperimentChanged:experimentName:variationName:` method to your Class. Then call your code experiment again from that method. This delegate method will be called everytime the current variation is selected on the website or device's shake menu.

    ```objc
    - (void)viewDidLoad {
        [super viewDidLoad];
        [self runMyCodeExperiment];
    }
    
    - (void)runMyCodeExperiment {
        [Taplytics runCodeExperiment:@"My Code Experiment" withBaseline:^(NSDictionary *variables) {
            //  Code for baseline
        } variations:@{@"variation 1": ^(NSDictionary *variables) {
            // Code for variation 1
        }}];
    }
    
    // TaplyticsDelegate
    - (void)taplyticsExperimentChanged:(NSString*)experimentName variationName:(NSString*)variationName {
        [self runMyCodeExperiment];
    }
    ```
    
## Analytics Events

#### Taplytics Events

Some events are automatically tracked by Taplytics and will appear on your dashboard. These events are:

- App Active/Background/Terminated
- View Appeared/Dissapeared
- Time on View
- Location Authorized/Denied
- Social Sign-in Authorized/Denied
- Social Share Authorized/Denied
- Photo Library Authorized/Denied
- Push Notification Authorized/Denied
- Push Notification Seen/Opened

You can track your own custom Analytics events to Taplytics using the `logEvent:` methods:

```objc
[Taplytics logEvent:@"CustomEvent"];
// With NSNumber value and metaData
[Taplytics logEvent:@"CustomEvent" value:@42 metaData:@{@"userSubscribed":@YES}];
// Log Revenue
[Taplytics logRevenue:@"Purchase" value:@10.25 metaData:@{@"Item":@"blueSweater"}];
```

#### Analytics Sources

If you already have Analytics events instrumented with another Analytics source Taplytics will automatically pull in the events from the following sources:

- [Google Analytics](http://www.google.com/analytics/mobile/)
- [Flurry](https://developer.yahoo.com/analytics/)
- [Mixpanel](https://mixpanel.com/)
- [Intercom](https://www.intercom.io/)
- [Adobe](http://www.adobe.com/marketing-cloud.html)
- [Localytics](https://www.localytics.com/)
- [Parse](https://www.parse.com/)
- [Apsalar](https://apsalar.com/)

## User Attributes

Its possible to send user attributes to Taplytics for use in segmenting your users. It is required to set one of `user_id` or `email` to uniquely identify the user across multiple devices. The `customData` field allows you to send Taplytics your own custom data as a flat `NSDictionary` with `NSJSONSerialization` accepted values.

The possible fields are:

|Parameter  |Type         |
|---	    |---          |
|email	    |	NSString    |
|user_id    |	NSString    |
|firstname  |	NSString    |
|lastname   |	NSString    |
|name	    |	NSString    |
|age	    |	NSNumber    |
|gender	    |	NSString    |
|customData |	NSDictionary |

For example:

```objc
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
```

To reset a user after they have logged out of your app and the User Attributes are no longer valid, call `resetUser:`. Do not set any new user attributes until you receive the callback.

```objc
[Taplytics resetUser:^{
  // Finished User Reset
}];
```

## Push Notification Instructions

1. In order for iOS and Taplytics to know that your app accepts Push Notifications, you have to implement the following methods on your  `UIApplicationDelegate`.

    ```objc
    // Implement these methods for Taplytics Push Notifications
    - (void)application:(UIApplication *)application
    didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings {
    }
     
    - (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    }
     
    - (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
    }
     
    - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
    }
     
    - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
    fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
    completionHandler(UIBackgroundFetchResultNoData);
    }
    ```
    
2. You'll also have to register for push notifications. When you do so, iOS will ask your users for permission and enable the ability to receive notifications to that device.

    If you are not already registering for push notifications all you have to do is call registerPushNotifications: on Taplytics, and we take care of all the rest!

    Please note that calling this function will  show the permission dialog  to the user.
    
    ```objc
    /* Example usage */
    [Taplytics registerPushNotifications];
    ```
    
#### Resetting User After Logout

1. If you're using our User Attributes feature, you can easily disconnect a user from the device when they log out. This will prevent our system from sending pushes to that device if you attempt to send a targetted push notification to the user who used to be logged in on it. You can do this by calling our `resetUser:` function:

    ```objc
    [Taplytics resetUser:^{
      // Finished User Reset
    }];
    ```
    
## Questions or Need Help

_The Taplytics team is available 24/7 to answer any questions you have. Just email support@taplytics.com or visit http://taplytics.com/docs for more detailed installation and usage information._
