You can get started with using Taplytics on iOS in minutes. Just follow the steps below:

| # | Step |
| - | ----------------- |
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
    
#### Install Using Segment
1. Log in to your [Segment Account](https://segment.com?utm_source=partners&utm_medium=Docs&utm_campaign=taplytics.com) 
2. Navigate to the integration page for the project you want to install Taplytics.
3. Scroll through the integration list and turn on the integration for Taplytics.
    ![Image of URL Scheme](http://taplytics.com/assets/docs/install-sdk/segment-integration.png)
4. You will now be prompted to add your Taplytics API key. Log in to your [Taplytics Account](https://taplytics.com/login/) and navigate to settings. Once there copy your Taplytics iOS/Android SDK Key.
    ![Image of URL Scheme](http://taplytics.com/assets/docs/install-sdk/taplytics-sdkkey.png)
5. Head back to Segment and paste in your key. 
6. Press Save and Enable in the right-hand corner. 

---

### App Linking

Secondly, (though, optionally) you can implement app linking, which will allow you to pair your device to Taplytics via a link sent through email or text. This will enable your team to easily pair any build of your app to Taplytics.

1. First ensure that `application:openURL:` method is implemented in your `UIApplicationDelegate`

    ```objc
    - (BOOL)application:(UIApplication *)app openURL:(NSURL *)url sourceApplication:(NSString *)sourceApp annotation:(id)ann {
        return NO;
    }
    ```
    
2. [Get your Taplytics URL Scheme from Taplytics's Settings](https://taplytics.com/dashboard)

    ![Image of URL Scheme](http://taplytics.com/assets/docs/install-sdk/url-scheme.png)
    
    
3. Add Taplytics URL Type in XCode's Build Info panel, with Identifier: com.taplytics, add your Taplytics URL Scheme from above.

    ![Image Of XCode build info](http://taplytics.com/assets/docs/install-sdk/app-link.png)

---


## 2. User Attributes

Its possible to send user attributes to Taplytics for use in segmenting your users. It is required to set one of `user_id` or `email` to uniquely identify the user across multiple devices. The `customData` field allows you to send Taplytics your own custom data as a flat `NSDictionary` with `NSJSONSerialization` accepted values.

The possible fields are:

|Parameter  |Type         |
|---        |---          |
|email      |   NSString    |
|user_id    |   NSString    |
|firstname  |   NSString    |
|lastname   |   NSString    |
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

### Resetting Users

To reset a user after they have logged out of your app and the User Attributes are no longer valid, call `resetUser:`. Do not set any new user attributes until you receive the callback.

```objc
[Taplytics resetUser:^{
  // Finished User Reset
}];
```

---

## 3. Track Events

### Automatic Tracking

Some events and general information are automatically tracked by Taplytics and will appear on your dashboard. These are:

- App Active/Background/Terminated
- View Appeared/Dissapeared
- Time on View
- Location information and Authorized/Denied events
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
- [Localytics](https://www.localytics.com/)
- [Parse](https://www.parse.com/)
- [Apsalar](https://apsalar.com/)

#### Disabling Automatic Tracking

If you would like to disable any of this tracking pass in one of the constants below into a disabled array

|Constant  |Description         |
|---        |---          |
|TaplyticsOptionTrackLocation | location tracking |
|TaplyticsOptionTrackSocialSignIn | social sign in access alert tracking |
|TaplyticsOptionTrackiAdInstallation |  app install from iAd    |
|TaplyticsOptionTrackPhotoLibraryAccess |   photo library access alert tracking |
|TaplyticsOptionSourceGoogleAnalytics | Google Analytics event tracking |
|TaplyticsOptionSourceFlurry | Flurry Analytics event tracking |
|TaplyticsOptionSourceMixpanel | Mixpanel Analytics event tracking |
|TaplyticsOptionSourceIntercom | Intercom event tracking |
|TaplyticsOptionSourceParse | Parse Analytics event tracking |
|TaplyticsOptionSourceApsalar | Apsalar Analytics event tracking |
|TaplyticsOptionSourceAdobe | Adobe Analytics event tracking |
|TaplyticsOptionSourceLocalytics | Localytics Analytics event tracking |

For example:

```obc
[Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here" options:@{@"disable":@[TaplyticsOptionTrackLocation]}];
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

---

### Experiment Information Postbacks

If you choose to, the Taplytics SDK can also send the running Experiment/Variation information to a supported Analytics source. [Check out our docs](https://taplytics.com/docs/guides/third-party-integration-setup) for details.

