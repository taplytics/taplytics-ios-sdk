You can get started with using Taplytics on iOS or tvOS in minutes. Just follow the steps below:

| # | Step |
| --- | --- |
| 1 | [Install & Initialize Taplytics](#1-install) |
| 2 | [Setting User Attributes](#2-user-attributes) (optional) |
| 3 | [Tracking Events](#3-track-events) (optional) |

## 1. Install

### SDK

First, you'll want to install our SDK inside your XCode project.

#### CocoaPods Installation
1. Install using CocoaPods
    - Create a `Podfile` using `pod init` and add Taplytics to your podfile:

        ```ruby
        # For iOS:
        pod 'Taplytics'
        # For tvOS:
        pod 'Taplytics_tvOS'
        ```

    - Run pod install:

        ```ruby
        pod install
        ```

    - Open your project's `.xcworkspace` file

2. Initialize the SDK by adding the correct import for the framework you are using and the following line of code with your API key to your `UIApplicationDelegate`. Make sure to call `startTaplyticsAPIKey:` before making `self.window` the key window, such as: `[self.window makeKeyAndVisible]` or `[self.window makeKeyWindow]`.

    <sub>**Objective-C**</sub>
    ```objc
    // iOS
    #import <Taplytics/Taplytics.h>
    // tvOS
    #import <Taplytics_tvOS/Taplytics.h>
    ...
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
        ...
        [Taplytics startTaplyticsAPIKey:@"API_KEY"];
        ...
        // make sure you call startTaplytics before any makeKeyWindow calls:
        // [self.window makeKeyAndVisible];
        // [self.window makeKeyWindow];
        ...
        return YES;
    }
    ```
    <sub>**Swift**</sub>
    ```swift
    // iOS
    import Taplytics
    // tvOS
    import Taplytics_tvOS
    ...
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
      ...
      Taplytics.startAPIKey("API_KEY")
      ...
      // make sure you call startTaplytics before any makeKeyWindow calls:
      // self.window.makeKeyAndVisible()
      // self.window.makeKeyWindow()
      ...
      return true
    }
    ```

    That's it! You can then call Taplytics in your `didFinishLaunchingWithOptions` method in your AppDelegate.


#### Manual Installation

1. [Download the SDK / clone into your app.](https://github.com/taplytics/taplytics-ios-sdk)
2. Load the Taplytics framework into your app.
3. Add the required frameworks
  - For iOS:

    ```
    CoreTelephony.framework
    SystemConfiguration.framework
    JavaScriptCore.framework
    ```

  - For tvOS:

    ```
    SystemConfiguration.framework
    JavaScriptCore.framework
    ```


4. Add the `-ObjC` Linker flag to your project settings.
5. Initialize the SDK by adding a line of code with your API key in your `UIApplicationDelegate`. Make sure to call `startTaplyticsAPIKey:` before making `self.window` the key window, such as: `[self.window makeKeyAndVisible]` or `[self.window makeKeyWindow]`.

    <sub>**Objective-C**</sub>
    ```objc
    // iOS
    #import <Taplytics/Taplytics.h>
    // tvOS
    #import <Taplytics_tvOS/Taplytics.h>
    ...
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
        ...
        [Taplytics startTaplyticsAPIKey:@"API_KEY"];
        ...
        // make sure you call startTaplytics before any makeKeyWindow calls:
        // [self.window makeKeyAndVisible];
        // [self.window makeKeyWindow];
        ...
        return YES;
    }
    ```

    <sub>**Swift**</sub>
    ```swift
    // For iOS
    import Taplytics
    // For tvOS
    import Taplytics_tvOS
    ...
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        ...
        Taplytics.startAPIKey("API_KEY")
        ...
        // make sure you call startTaplytics before any makeKeyWindow calls:
        // self.window.makeKeyAndVisible()
        // self.window.makeKeyWindow()
        ...
        return true
    }
    ```

#### Install Using Segment
The Taplytics SDK can also be installed via Segment. You can find install instructions [here](https://taplytics.com/docs/segment-integration).

---

### Advanced Pairing

##### Note: Advanced pairing is only supported by iOS, tvOS does not support advanced pairing!

You can implement Advanced Pairing, which will allow you to pair your device to Taplytics via a link sent by email or text. Advanced Pairing is an easy way for your team to pair any build of your app to Taplytics.

1. First ensure that `application:openURL:options:` method is implemented in your `UIApplicationDelegate`

    <sub>**Objective-C**</sub>
    ```objc
    - (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
        return NO;
    }
    ```

    <sub>**Swift**</sub>
    ```swift
    func application(_ app: UIApplication, open url: URL, options: [UIApplicationOpenURLOptionsKey : Any] = [:]) -> Bool {
        return false
    }
    ```

2. [Get your Taplytics URL Scheme from Taplytics' Settings](https://taplytics.com/dashboard)

    ![Image of URL Scheme](http://taplytics.com/assets/docs/install-sdk/url-scheme.png)


3. Add Taplytics URL Type in XCode's Build Info panel, with Identifier: com.taplytics, add your Taplytics URL Scheme from above.

    ![Image Of XCode build info](http://taplytics.com/assets/docs/install-sdk/app-link.png)

---


## 2. User Attributes

It's possible to segment your users based on custom user attributes. To set this up, you need to make either the `user_id` or `email` unique to identify the user across multiple devices. Below is a list of standard custom fields you can send to Taplytics. There is also a `customData` field that allows you to send any custom data you have as a flat `NSDictionary` with `NSJSONSerialization` accepted values. If logging is enabled, logs will show the user attributes every time they are set or updated.

The possible fields are:

|Parameter  |Type         |
|---        |---          |
|email      |   NSString    |
|user_id    |   NSString    |
|firstName  |   NSString    |
|lastName   |   NSString    |
|name       |   NSString    |
|age        |   NSNumber    |
|gender     |   NSString    |
|customData |   NSDictionary |

For example:

<sub>**Objective-C**</sub>
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

<sub>**Swift**</sub>
```swift
Taplytics.setUserAttributes([
    "user_id": "testUser",
    "name": "Test User",
    "email": "test@taplytics.com",
    "gender": "female",
    "age": 25,
    "avatarUrl": "https://pbs.twimg.com/profile_images/497895869270618112/1zbNvWlD.png",
    "customData": [
        "paidSubscriber": true,
        "purchases": 3,
        "totalRevenue": 42.42
    ]
])
```

_NOTE: The `customData` field is limited to 50kb of JSON string data._

### User Attributes on First Launch

User Attributes set before `startTaplyticsAPIKey:` is called, will be used for experiment segmentation on the first session of your app. Any attributes that are set after `startTaplyticsAPIKey:` is called will not be used for experiment segmentation until the next session of your app.

<sub>**Objective-C**</sub>
```objc
// These custom data values will be used for segmentation on the first session of the app.
[Taplytics setUserAttributes:@{@"customData": @{@"paid_user": @YES}}];

[Taplytics startTaplyticsAPIKey:@"API_KEY"];

// These custom data values will only take effect on the second session of the app.
[Taplytics setUserAttributes:@{@"customData": @{@"demo_account": @NO}}];
```

<sub>**Swift**</sub>
```swift
Taplytics.setUserAttributes(["customData": ["paid_user": true]])

Taplytics.startAPIKey("API_KEY")

Taplytics.setUserAttributes(["customData": ["demo_account": false]])
```

You can also use `setUserAttributes` with a block that can notify you when the call to the server has completed.

<sub>**Objective-C**</sub>
```objc
[Taplytics setUserAttributes:@{@"customData": @{@"demo_account": @NO}} withCallback:^(void) {
    // Finished setting user attributes!
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.setUserAttributes(["customData": ["paid_user": true]]) {
    // Finished setting user attributes!        
}
```

### Retrieving Session Info

Taplytics also offers a method to retrieve select information of what you know about a session at a given time. This method returns the user's Taplytics identifier (appUser_id) and current session id (session_id)

<sub>**Objective-C**</sub>
```objc
[Taplytics getSessionInfo:^(NSDictionary * _Nullable sessionInfo) {
    // Use the NSDictionary of sessionInfo
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.getSessionInfo { (sessionInfo) in
    // Use the NSDictionary of sessionInfo
}
```

### Resetting Users

Once a user logs out of your app, their User Attributes are no longer valid. You can reset their data by calling `resetUser:`, make sure you do not set any new user attributes until you receive the callback. If logging is enabled, logs will show if the user has been reset or if there was an error.

<sub>**Objective-C**</sub>
```objc
[Taplytics resetUser:^{
  // Finished User Reset
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.resetUser {
  // Finished User Reset
}
```

### User Opt-In / Opt-Out

Using the User Opt-In / Opt-Out APIs allows you to simplify the process to get user consent for analytics tracking and experimentation. Calling `optOutUserTracking` will disable all Taplytics analytics tracking and experiments, and calling `optInUserTracking` will re-enable all Taplytics analytics tracking and experiments. You can retrieve the current status using: `hasUserOptedOutTracking`.

<sub>**Objective-C**</sub>
```objc
[Taplytics optOutUserTracking];

[Taplytics optInUserTracking];

BOOL hasOptedOut = [Taplytics hasUserOptedOutTracking];
```

<sub>**Swift**</sub>
```swift
Taplytics.optOutUserTracking()
        
Taplytics.optInUserTracking()

let hasOptedOut = Taplytics.hasUserOptedOutTracking()
```

---

## 3. Track Events

### Automatic Tracking

The following events and general information are automatically tracked by Taplytics and will appear on your dashboard.

- App Active/Background/Terminated
- View Appeared/Disappeared
- Time on View
- Location information and Authorized/Denied events
- Social Sign-in Authorized/Denied
- Social Share Authorized/Denied
- Photo Library Authorized/Denied
- Push Notification Authorized/Denied (iOS only)
- Push Notification Seen/Opened (iOS only)

#### External Analytics Sources

If you already have Analytics events instrumented with another Analytics source Taplytics will also automatically pull in the events from the following sources:

- [Google Analytics](http://www.google.com/analytics/mobile/)
- [Flurry](https://developer.yahoo.com/analytics/)
- [Mixpanel](https://mixpanel.com/)
- [Intercom](https://www.intercom.io/)
- [Adobe](http://www.adobe.com/marketing-cloud.html)
- [Localytics](https://www.localytics.com/) (Only below Version 4)
- [Parse](https://www.parse.com/)
- [Apsalar](https://apsalar.com/)
- [Crashlytics Answers](http://try.crashlytics.com/answers/)
- [KISSMetrics](https://www.kissmetrics.com/products)
- [Heap](https://heapanalytics.com/)
- [Firebase](https://firebase.google.com/docs/analytics)

#### Disabling Automatic Tracking

You can disable automatic tracking for any of the below constants by adding them to the disable array.

|Constant  |Description         |
|---        |---          |
|TaplyticsDisableTrackLocation | location tracking via GPS |
|TaplyticsDisableTrackSocialSignIn | social sign in access alert tracking |
|TaplyticsDisableTrackiAdInstallation |  app install from iAd    |
|TaplyticsDisableTrackPhotoLibraryAccess |   photo library access alert tracking |
|TaplyticsDisableSourceGoogleAnalytics | Google Analytics event tracking |
|TaplyticsDisableSourceFlurry | Flurry Analytics event tracking |
|TaplyticsDisableSourceMixpanel | Mixpanel Analytics event tracking |
|TaplyticsDisableSourceIntercom | Intercom event tracking |
|TaplyticsDisableSourceParse | Parse Analytics event tracking |
|TaplyticsDisableSourceApsalar | Apsalar Analytics event tracking |
|TaplyticsDisableSourceAdobe | Adobe Analytics event tracking |
|TaplyticsDisableSourceLocalytics | Localytics Analytics event tracking |
|TaplyticsDisableSourceCrashlytics | Crashlytics Answers Analytics event tracking |
|TaplyticsDisableSourceKISSMetrics | KISSMetrics Analytics event tracking |
|TaplyticsDisableSourceHeap | Heap Analytics event tracking |
|TaplyticsDisableSourceFirebase | Firebase Analytics event tracking |
|TaplyticsDisableUITableViewSW | UITableView tracking |
|TaplyticsDisableUICollectionViewSW | UICollectionView tracking |
|TaplyticsDisableUIPageViewSW | UIPageView tracking |
|TaplyticsDisableUIActionSheetSW | UIActionSheet tracking |
|TaplyticsDisableUIAlertViewSW | UIAlertView tracking |
|TaplyticsDisableUITextFieldViewSW | UITextField tracking |

For example:

<sub>**Objective-C**</sub>
```objc
[Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{
    TaplyticsOptionDisable: @[TaplyticsOptionTrackLocation]
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.startAPIKey("API_KEY", options: [
    TaplyticsOptionDisable: [TaplyticsOptionTrackLocation]
])
```

#### Background Session Time

Taplytics automatically tracks sessions for you. The Taplytics SDK keeps track of the last activity timestamp in your app (app activity is considered a view change, button click, or Taplytics event logged), and when your app returns from background if the time since last activity is greater then 10 minutes we create a new session for you. If you would like the session background time something other then 10 minutes you can se it as a start option:

<sub>**Objective-C**</sub>
```objc
[Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{TaplyticsOptionSessionBackgroundTime: @10}];
```

<sub>**Swift**</sub>
```swift
Taplytics.startAPIKey("API_KEY", options: [TaplyticsOptionSessionBackgroundTime: 10])
```

---

### Taplytics Events

You can also track your own custom Analytics events to Taplytics using the `logEvent:` methods:

<sub>**Objective-C**</sub>
```objc
[Taplytics logEvent:@"CustomEvent"];

// With NSNumber value and metaData
[Taplytics logEvent:@"CustomEvent" value:@42 metaData:@{@"userSubscribed":@YES}];

// Log Revenue
[Taplytics logRevenue:@"Purchase" value:@10.25 metaData:@{@"Item":@"blueSweater"}];
```

<sub>**Swift**</sub>
```swift
Taplytics.logEvent("CustomEvent")

// With Number value and metaData
Taplytics.logEvent("CustomEvent", value: 42, metaData: ["userSubscribed": true])

// Log Revenue
Taplytics.logRevenue("Purchase", revenue: 10.15, metaData: ["Item": "blueSweater"])
```

_NOTE: event metaData is limited to 50kb of JSON string data._

---

### Firebase Events

Firebase has a limit of 500 distinct event names per project. As a way around this, you can pass in the start option `TaplyticsOptionCustomFirebaseFormat` and send the event names in the parameters instead with any additional metadata.

Note: If passing the event name in the parameters, you *must* track the event name using the key `eventName`.

<sub>**Objective-C**</sub>
```objc
// Normal way of logging events
[FIRAnalytics logEventWithName:@"CustomEvent" parameters:@{@"userSubscribed":@YES}];
[FIRAnalytics logEventWithName:@"AnotherCustomEvent" parameters:@{@"userSubscribed":@YES}];

// With start option enabled
[FIRAnalytics logEventWithName:@"tlEvents" parameters:@{@"eventName":@"CustomEvent", @"userSubscribed":@YES}];
[FIRAnalytics logEventWithName:@"tlEvents" parameters:@{@"eventName":@"AnotherCustomEvent", @"userSubscribed":@YES}];

```

<sub>**Swift**</sub>
```swift
// Normal way of logging events
Analytics.logEvent("CustomEvent", parameters: ["userSubscribed": true])
Analytics.logEvent("AnotherCustomEvent", parameters: ["userSubscribed": true])

// With start option enabled
Analytics.logEvent("tlEvents", parameters: ["eventName": "CustomEvent", "userSubscribed": true])
Analytics.logEvent("tlEvents", parameters: ["eventName": "AnotherCustomEvent", "userSubscribed": true])
```

_NOTE: event metaData is limited to 50kb of JSON string data._

---

### Experiment Information Postbacks

If you choose to, the Taplytics SDK can also send the running Experiment/Variation information to a supported Analytics source. [Check out our docs](https://taplytics.com/docs/guides/third-party-integration-setup) for details.

---

### Start Options

Start options allow you to control how certain SDK features function, and enable or disable features.

|Start Option |Type |Description |
|---        |---	        |---          |
|TaplyticsOptionDelayLoad|NSNumber|Controls the maximum time the SDK will show your launch image for. [More details](https://github.com/taplytics/taplytics-ios-sdk/blob/master/EXPERIMENTS.md#delay-load). |
|TaplyticsOptionShowLaunchImage|NSNumber(Boolean)|Controls whether or not the SDK will hold the launch image during DelayLoad. **Note: Disabling this feature may result in users seeing visual changes, or code variables using default values for first session**|
|TaplyticsOptionLaunchImageType|NSString|If you are using a xib as a launch image set the value as `@"xib"`. This will stop the caught exception that occurs for xib based launch images. |
|TaplyticsOptionShowShakeMenu|NSNumber(Boolean)|To disable the shake menu from showing up in development mode, set to `@NO` |
|TaplyticsOptionTestExperiments|NSNumber(Boolean)|To test specific experiments, pass in the experiment name/variation name as the key/values of a NSDictionary. [More details](https://github.com/taplytics/taplytics-ios-sdk/blob/master/EXPERIMENTS.md#testing-specific-experiments). |
|TaplyticsOptionDisableBorders|NSNumber(Boolean)|To disable all Taplytics borders in development mode, set to `@YES` |
|TaplyticsOptionAsyncLoading|NSNumber(Boolean)|Forces loading of taplytics properties from disk as async task, breaks some synchronous variable behaviour, see section below for details. |
|TaplyticsOptionLogging|NSNumber(Boolean)|Provides more verbose logging from Taplytics to help with debugging. |
|TaplyticsOptionCustomFirebaseFormat|NSNumber(Boolean)|Allows you to pass Firebase event names in the parameters as a workaround Firebase's 500 event limit. [More details](#Firebase-Events). |

Example:

<sub>**Objective-C**</sub>
```objc
[Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{
	TaplyticsOptionDelayLoad: @6,
	TaplyticsOptionLaunchImageType: @"xib",
	TaplyticsOptionShowShakeMenu: @NO,
	TaplyticsOptionDisableBorders: @YES,
	TaplyticsOptionTestExperiments: @{
		  @"Experiment 1": @"Variation 1",
   		@"Experiment 2": @"baseline"
	}
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.startAPIKey("API_KEY", options: [
    TaplyticsOptionDelayLoad: 6,
    TaplyticsOptionLaunchImageType: "xib",
    TaplyticsOptionShowShakeMenu: false,
    TaplyticsOptionDisableBorders: true,
    TaplyticsOptionTestExperiments: [
        "Experiment 1": "Variation 1",
        "Experiment 2": "baseline"
    ]
])
```

#### Async Loading

**Note:** `propertiesLoadedCallback` **as of** `3.0.0` **is deprecated**


Enabling the start option `TaplyticsOptionAsyncLoading ` will make the initial loading of taplytics properties from disk run on an async thread. However, this will break the behaviour of synchronous variables where they used the value loaded from disk, with `TaplyticsOptionAsyncLoading` enabled and synchronous variables are initialized before properties are loaded from disk they will use the default value. To ensure properties are loaded when initializing synchronous variables use `[Taplytics propertiesLoadedCallback:]`. **Note: propertiesLoadedCallback must be placed _after_ startTaplytics**.

Existing behaviour example:

<sub>**Objective-C**</sub>
```objc
[Taplytics startTaplyticsAPIKey:@"API_KEY"];

// Existing behaviour would have loaded value from disk and the variable's value would be loaded from disk.
self.var = [TaplyticsVar taplyticsSyncVarWithName:@"syncVar" defaultValue:@1];
NSLog(@"Variable Value: %@", _var.value);
```

<sub>**Swift**</sub>
```swift
Taplytics.startAPIKey("API_KEY")

// Existing behaviour would have loaded value from disk and the variable's value would be loaded from disk.
self.tlVar = TaplyticsVar.sync(name: "syncVar", defaultValue: 1 as NSNumber)
print("Variable Value: \(tlVar.value)")
```

Async Loading example:

<sub>**Objective-C**</sub>
```objc
[Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{TaplyticsOptionAsyncLoading: @YES}];

// Here var.value would not be loaded from disk and would have the default value of @1
self.var = [TaplyticsVar taplyticsSyncVarWithName:@"syncVar" defaultValue:@1];
NSLog(@"Variable Value: %@", _var.value);

// Using the propertiesLoadedCallback:
__weak AppDelegate* weakSelf = self;
[Taplytics propertiesLoadedCallback:^(BOOL loaded) {
	// Now the variable will have the correct value loaded from disk/server
	weakSelf.var = [TaplyticsVar taplyticsSyncVarWithName:@"syncVar" defaultValue:@1];
	NSLog(@"Variable Value: %@", weakSelf.var.value);
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.startAPIKey("API_KEY", options: [TaplyticsOptionAsyncLoading: true])

// Here var.value would not be loaded from disk and would have the default value of @1
self.tlVar = TaplyticsVar.sync(name: "syncVar", defaultValue: 1 as NSNumber)
print("Variable Value: \(tlVar.value)")

// Using the propertiesLoadedCallback:
Taplytics.propertiesLoadedCallback { (loaded) in
    guard loaded, let label = self.label else {
        return
    }

    self.tlVar = TaplyticsVar.sync(name: "syncVar", defaultValue: 1 as NSNumber)
    if let tlVariable = self.tlVar, let stringValue = tlVariable.value as? String {
        print("Variable Value: \(stringValue)")
    }
}
```
