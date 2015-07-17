Setting up Push Notifications using Taplytics is simple. Follow the steps below to get started.

| # | Step |
| --- | --- |
| 1 | [Setup](#1-setup) |
| 2 | [Receiving Push Notifications](#2-receiving-push-notifictions) |
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

---


## 2. Receiving Push Notifications

To be able to send your users Push Notifications, we'll need you to upload your Apple Push certificates. Please follow [this guide](https://taplytics.com/docs/guides/push-notifications/apple-push-certificates) to do so.


---

## 3. Resetting Users

If you're using our User Attributes feature, you can easily disconnect a user from a device when they log out. This will prevent our system from sending push notifications to that device. It is especially important to reset the user when your push campaigns are targeted to a specific user. You can do this by calling our `resetUser:` function:

```objc
[Taplytics resetUser:^{
  // Finished User Reset
}];
```
    
