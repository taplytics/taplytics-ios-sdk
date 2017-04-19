You can get started with using Taplytics on iOS in minutes. Just follow the steps below:

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
    - Add a `Podfile` to the root of your project directory with the following:

        ```ruby
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
...
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    ...
    [Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here"];
    ...
}
```

#### Manual Installation

1. [Download the SDK / clone into your app.](https://github.com/taplytics/taplytics-ios-sdk)
2. Load the Taplytics framework into your app.
3. Add the required frameworks:
    
    ```
    CoreTelephony.framework
    SystemConfiguration.framework
    JavaScriptCore.framework
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
    
#### Install Using Segment
The Taplytics SDK can also be installed via Segment. You can find install instructions [here](https://taplytics.com/docs/segment-integration)


---

### Advanced Pairing

Secondly, (though, optionally) you can implement Advanced Pairing, which will allow you to pair your device to Taplytics via a link sent by email or text. Advanced Pairing is an easy way for your team to pair any build of your app to Taplytics. 

1. First ensure that `application:openURL:options:` method is implemented in your `UIApplicationDelegate`

    ```objc
    - (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
        return NO;
    }
    ```
    
2. [Get your Taplytics URL Scheme from Taplytics' Settings](https://taplytics.com/dashboard)

    ![Image of URL Scheme](http://taplytics.com/assets/docs/install-sdk/url-scheme.png)
    
    
3. Add Taplytics URL Type in XCode's Build Info panel, with Identifier: com.taplytics, add your Taplytics URL Scheme from above.

    ![Image Of XCode build info](http://taplytics.com/assets/docs/install-sdk/app-link.png)

---


## 2. User Attributes

It's possible to segment your users based on custom user attributes. To set this up, you need to make either the `user_id` or `email` unique to identify the user across multiple devices. Below is a list of standard custom fields you can send to Taplytics. There is also a `customData` field that allows you to send any custom data you have as a flat `NSDictionary` with `NSJSONSerialization` accepted values.

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

_NOTE: The `customData` field is limited to 50kb of JSON string data._

### User Attributes on First Launch

User Attributes set before `startTaplyticsAPIKey:` is called, will be used for experiment segmentation on the first session of your app. Any attributes that are set after `startTaplyticsAPIKey:` is called will not be used for experiment segmentation until the next session of your app.

```objc
// These custom data values will be used for segmentation on the first session of the app.
[Taplytics setUserAttributes:@{
    @"customData": @{
        @"paid_user": @YES
    }
}];
    
[Taplytics startTaplyticsAPIKey:@"API_KEY"];

// These custom data values will only take effect on the second session of the app.
[Taplytics setUserAttributes:@{
    @"customData": @{
        @"demo_account": @NO
    }
}];
```

### Retrieving Session Info

Taplytics also offers a method to retrieve select information of what you know about a session at a given time. This method returns the user's Taplytics identifier (appUser_id) and current session id (session_id)

```objc
[Taplytics getSessionInfo:^(NSDictionary * _Nullable sessionInfo) {
    //Use your NSDictionary of sessionInfo
}];
```

### Resetting Users

Once a user logs out of your app, their User Attributes are no longer valid. You can reset their data by calling `resetUser:`, make sure you do not set any new user attributes until you receive the callback.


```objc
[Taplytics resetUser:^{
  // Finished User Reset
}];
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
- Push Notification Authorized/Denied
- Push Notification Seen/Opened

#### External Analytics Sources

If you already have Analytics events instrumented with another Analytics source Taplytics will also automatically pull in the events from the following sources:

- [Google Analytics](http://www.google.com/analytics/mobile/)
- [Flurry](https://developer.yahoo.com/analytics/)
- [Mixpanel](https://mixpanel.com/)
- [Intercom](https://www.intercom.io/)
- [Adobe](http://www.adobe.com/marketing-cloud.html)
- [Localytics](https://www.localytics.com/) (Version 2 and under only)
- [Parse](https://www.parse.com/)
- [Apsalar](https://apsalar.com/)
- [Crashlytics Answers](http://try.crashlytics.com/answers/)
- [KISSMetrics](https://www.kissmetrics.com/products)
- [Heap](https://heapanalytics.com/)

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
|TaplyticsDisableUITableViewSW | UITableView tracking |
|TaplyticsDisableUICollectionViewSW | UICollectionView tracking |
|TaplyticsDisableUIPageViewSW | UIPageView tracking |
|TaplyticsDisableUIActionSheetSW | UIActionSheet tracking |
|TaplyticsDisableUIAlertViewSW | UIAlertView tracking |
|TaplyticsDisableUITextFieldViewSW | UITextField tracking |

For example:

```objc
[Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here" options:@{TaplyticsOptionDisable:@[TaplyticsOptionTrackLocation]}];
```

#### Background Session Time

Taplytics automatically tracks sessions for you. The Taplytics SDK keeps track of the last activity timestamp in your app (app activity is considered a view change, button click, or Taplytics event logged), and when your app returns from background if the time since last activity is greater then 10 minutes we create a new session for you. If you would like the session background time something other then 10 minutes you can se it as a start option: 

```objc
[Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here" options:@{TaplyticsOptionSessionBackgroundTime:@10}];
```

---

### Taplytics Events

You can also track your own custom Analytics events to Taplytics using the `logEvent:` methods:

```objc
[Taplytics logEvent:@"CustomEvent"];

// With NSNumber value and metaData
[Taplytics logEvent:@"CustomEvent" value:@42 metaData:@{@"userSubscribed":@YES}];

// Log Revenue
[Taplytics logRevenue:@"Purchase" value:@10.25 metaData:@{@"Item":@"blueSweater"}];
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
|TaplyticsOptionShowLaunchImage|NSNumber(Boolean)|Controls whether or not the SDK will hold the launch image during DelayLoad.|
|TaplyticsOptionLaunchImageType|NSString|If you are using a xib as a launch image set the value as `@"xib"`. This will stop the caught exception that occurs for xib based launch images. |
|TaplyticsOptionShowShakeMenu|NSNumber(Boolean)|To disable the shake menu from showing up in development mode, set to `@NO` |
|TaplyticsOptionTestExperiments|NSNumber(Boolean)|To test specific experiments, pass in the experiment name/variation name as the key/values of a NSDictionary. [More details](https://github.com/taplytics/taplytics-ios-sdk/blob/master/EXPERIMENTS.md#testing-specific-experiments). |
|TaplyticsOptionDisableBorders|NSNumber(Boolean)|To disable all Taplytics borders in development mode, set to `@YES` |
|TaplyticsOptionAsyncLoading|NSNumber(Boolean)|Forces loading of taplytics properties from disk as async task, breaks some synchronous variable behaviour, see section below for details. |

Example: 

```objc
[Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here" options:@{
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

#### Async Loading
Enabling the start option `TaplyticsOptionAsyncLoading ` will make the initial loading of taplytics properties from disk run on an async thread. However, this will break the behaviour of synchronous variables where they used the value loaded from disk, with `TaplyticsOptionAsyncLoading` enabled and synchronous variables are initialized before properties are loaded from disk they will use the default value. To ensure properties are loaded when initializing synchronous variables use `[Taplytics propertiesLoadedCallback:]`. **propertiesLoadedCallback must be placed _after_ startTaplytics**

Existing behaviour example:

```objc
[Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here"];

// Existing behaviour would have loaded value from disk and the variable's value would be loaded from disk.
self.var = [TaplyticsVar taplyticsSyncVarWithName:@"syncVar" defaultValue:@1];
NSLog(@"Variable Value: %@", _var.value);
```

Async Loading example:

```objc
[Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here" options:@{
	TaplyticsOptionAsyncLoading: @YES
}];

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
