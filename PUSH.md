Setting up Push Notifications using Taplytics is simple. Follow the steps below to get started.

| # | Step |
| --- | --- |
| 1 | [Setup](#1-setup) |
| 2 | [Receiving Push Notifications](#2-receiving-push-notifications) |
| 3 | [Resetting Users](#3-resetting-users) |

## 1. Setup

### Implement functions
For iOS and Taplytics to know that your app accepts Push Notifications, you must implement the following methods on your  `UIApplicationDelegate`.

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

### Register for Push Notifications

You'll also need to register for push notifications with iOS. When you do so, iOS will ask your users for permission and enable the ability to receive notifications to that device.

If you are not already registering for push notifications all you have to do is call registerPushNotifications: on Taplytics, and we take care of all the rest!

Please Note that calling this function will show the permission dialog to the user.

```objc
/* Example usage */
[Taplytics registerPushNotifications];
```

### Register for Location Permissions

For automated push campaigns using location based regions you will need to add the `CoreLocation` framework to your app, and request location permissions from your users. Taplytics will automatically update and manage the monitored regions on your device for your automated push campaigns.

You can handle asking for location permissions yourself, or you can use our provided method as seen below. But make sure that you request `AuthorizedAlways` permissions so that we can set regions.

```objc 
// We will request AuthorizedAlways access to be able to set monitored regions
[Taplytics registerLocationAccess];
```

In order to allow the iOS location manager to successfully display a location request dialog to the user, the following properties must be added to the application's Plist settings:
```objc
NSLocationAlwaysUsageDescription
NSLocationWhenInUseUsageDescription
```

---

## 2. Receiving Push Notifications

To be able to send your users Push Notifications, we'll need you to upload your Apple Push certificates. Please follow [this guide](https://taplytics.com/docs/guides/push-notifications/apple-push-certificates) to do so.

### Environments (Development and Production)

In order to seperate your development devices and production devices, Taplytics automatically buckets devices into Development and Production buckets. We do this by looking at the provisioning profile that the app was built with.

#### Development Bucketing

If the app is built using a [Development Provisioning Profile](https://developer.apple.com/library/ios/documentation/IDEs/Conceptual/AppStoreDistributionTutorial/CreatingYourTeamProvisioningProfile/CreatingYourTeamProvisioningProfile.html), we bucket the device into the Development environment. You can change this by forcing an environment.

All devices that fall into the Development environment, Taplytics will use the [Development Push Notification Certificate](https://developer.apple.com/library/ios/documentation/IDEs/Conceptual/AppDistributionGuide/ConfiguringPushNotifications/ConfiguringPushNotifications.html) to attempt to send push notifications to your devices.

#### Production Bucketing

If the app is built using a [Distribution Provisioning Profile](https://developer.apple.com/library/ios/documentation/IDEs/Conceptual/AppDistributionGuide/TestingYouriOSApp/TestingYouriOSApp.html), we bucket the device into the Production environment. Note that this means that if you're distributing Ad-Hoc or Enterprise builds through a service like [Testflight](https://developer.apple.com/testflight/) or [Hockeyapp](http://hockeyapp.net/features/), then all those devices running those builds will fall into the Production environment. You can change this by forcing an environment.

All devices that fall into the Production environment, Taplytics will use the [Production Push Notification Certificate](https://developer.apple.com/library/ios/documentation/IDEs/Conceptual/AppDistributionGuide/ConfiguringPushNotifications/ConfiguringPushNotifications.html) to attempt to send push notifications to your devices.

#### Forcing an Environment

You can use the `options` attribute when you start Taplytics in order to force the environment that your devices are bucketed into. This can be especially useful for any Ad-Hoc and Enterprise distribution you might be doing.

Here's how you can achieve setting the Push environment:

```objc

// To bucket everyting into Production:
[Taplytics startTaplyticsAPIKey:@"SDK_TOKEN_HERE" options:@{@"pushSandbox":@0}];

// To bucket everyting into Development:
[Taplytics startTaplyticsAPIKey:@"SDK_TOKEN_HERE" options:@{@"pushSandbox":@1}];
```

---

## 3. Resetting Users

If you're using our User Attributes feature, you can easily disconnect a user from a device when they log out. This will prevent our system from sending push notifications to that device. It is especially important to reset the user when your push campaigns are targeted to a specific user. You can do this by calling our `resetUser:` function:

```objc
[Taplytics resetUser:^{
  // Finished User Reset
}];
```
    
