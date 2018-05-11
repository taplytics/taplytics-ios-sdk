Setting up Push Notifications using Taplytics is simple. Follow the steps below to get started.

| # | Step |
| --- | --- |
| 1 | [Setup](#1-setup) |
| 2 | [Receiving Push Notifications](#2-receiving-push-notifications) |
| 3 | [Resetting Users](#3-resetting-users) |
| 4 | [Rich Push Notifications](#4-rich-push-notifications-ios-10) |

## 1. Setup

### Required Code for iOS 9 and Below
For iOS and Taplytics to know that your app accepts Push Notifications, you must implement the following methods on your  `UIApplicationDelegate`.

<sub>**Objective-C**</sub>
```objc
// Implement these methods for Taplytics Push Notifications
- (void)application:(UIApplication *)application
didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings {
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
}

// Method will be called if the app is open when it recieves the push notification
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
	// "userInfo" will give you the notification information
}

// Method will be called when the app receives a push notification
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
	// "userInfo" will give you the notification information
	completionHandler(UIBackgroundFetchResultNoData);
}
```

<sub>**Swift**</sub>
```swift
func application(_ application: UIApplication, didRegister notificationSettings: UIUserNotificationSettings) {
}

func application(_ application: UIApplication, didRegisterForRemoteNotificationsWithDeviceToken deviceToken: Data) {
}

func application(_ application: UIApplication, didFailToRegisterForRemoteNotificationsWithError error: Error) {
}

func application(_ application: UIApplication, didReceiveRemoteNotification userInfo: [AnyHashable : Any]) {
	// "userInfo" will give you the notification information
}

func application(_ application: UIApplication, didReceiveRemoteNotification userInfo: [AnyHashable : Any], fetchCompletionHandler completionHandler: @escaping (UIBackgroundFetchResult) -> Void) {
	// "userInfo" will give you the notification information
	completionHandler(UIBackgroundFetchResult.noData)
}
```

### Required Code for iOS 10
For iOS 10, you'll need to implement the new `UserNotification` class to allow Taplytics and iOS to accept Push Notifications.  You will need to change your `UIApplicationDelegate` header file to look something like the following

<sub>**Objective-C**</sub>
```objc
#import <UIKit/UIKit.h>
#import <UserNotifications/UserNotifications.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate, UNUserNotificationCenterDelegate>

@end
```

<sub>**Swift**</sub>
```swift
import UIKit
import UserNotifications

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, UNUserNotificationCenterDelegate {
	...
}
```

You will also need to add the following methods to your 'UIApplicationDelegate'

<sub>**Objective-C**</sub>
```objc
// Implement these methods for Taplytics Push Notifications
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
}

// Method will be called when the app recieves the push notification
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
   // "userInfo" will give you the notification information
   completionHandler(UIBackgroundFetchResultNoData);
}

// Method will be called if the app is open when it recieves the push notification
- (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions))completionHandler{
   // "notification.request.content.userInfo" will give you the notification information
   completionHandler(UNNotificationPresentationOptionBadge);
}

// Method will be called if the user opens the push notification
- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void (^)())completionHandler {
	// "response.notification.request.content.userInfo" will give you the notification information
	completionHandler();
}
```

<sub>**Swift**</sub>
```swift
func application(_ application: UIApplication, didRegisterForRemoteNotificationsWithDeviceToken deviceToken: Data) {
}

func application(_ application: UIApplication, didFailToRegisterForRemoteNotificationsWithError error: Error) {
}

func application(_ application: UIApplication, didReceiveRemoteNotification userInfo: [AnyHashable : Any], fetchCompletionHandler completionHandler: @escaping (UIBackgroundFetchResult) -> Void) {
	// "userInfo" will give you the notification information
	completionHandler(UIBackgroundFetchResult.noData)
}

func userNotificationCenter(_ center: UNUserNotificationCenter, willPresent notification: UNNotification, withCompletionHandler completionHandler: @escaping (UNNotificationPresentationOptions) -> Void) {
	// "notification.request.content.userInfo" will give you the notification information
	completionHandler(UNNotificationPresentationOptions.badge)
}

func userNotificationCenter(_ center: UNUserNotificationCenter, didReceive response: UNNotificationResponse, withCompletionHandler completionHandler: @escaping () -> Void) {
	// "response.notification.request.content.userInfo" will give you the notification information
	completionHandler()
}
```

If you want your app to also support lower versions of iOS, you just need to add the missing methods described in the above section.

### Register for Push Notifications

You'll also need to register for push notifications with iOS. When you do so, iOS will ask your users for permission and enable the ability to receive notifications to that device.

You'll need to enable a few capabilities on your app. Go into your project settings and find your project under Targets. Select the Capabilities tab and turn on Push Notifications and Background Modes.  Under Background Modes, enable Remote Notifications.

If you are not already registering for push notifications all you have to do is call registerPushNotifications: on Taplytics, and we take care of all the rest!

Please Note that calling this function will show the permission dialog to the user.

<sub>**Objective-C**</sub>
```objc
[Taplytics registerPushNotifications];
```

<sub>**Swift**</sub>
```swift
Taplytics.registerPushNotifications()
```

#### Register for Location Permissions (Optional)

For automated push campaigns using location based regions you will need to add the `CoreLocation` framework to your app, and request location permissions from your users. Taplytics will automatically update and manage the monitored regions on your device for your automated push campaigns.

You can handle asking for location permissions yourself, or you can use our provided method as seen below. But make sure that you request `AuthorizedAlways` permissions so that we can set regions.

<sub>**Objective-C**</sub>
```objc
// We will request AuthorizedAlways access to be able to set monitored regions
[Taplytics registerLocationAccess];
```

<sub>**Swift**</sub>
```swift
Taplytics.registerLocationAccess()
```

In order to allow the iOS location manager to successfully display a location request dialog to the user, the following properties must be added to the application's Plist settings:

```objc
NSLocationAlwaysUsageDescription
NSLocationWhenInUseUsageDescription
```

These values will be used by the OS to display the reason for requesting location access.

---

## 2. Receiving Push Notifications

To be able to send your users Push Notifications, we'll need you to upload your Apple Push certificates. Please follow [this guide](https://taplytics.com/docs/guides/push-notifications/apple-push-certificates) to do so.

### Environments (Development and Production)

In order to separate your development devices and production devices, Taplytics automatically buckets devices into Development and Production buckets. We do this by looking at the provisioning profile that the app was built with.

#### Development Bucketing

If the app is built using a [Development Provisioning Profile](https://developer.apple.com/library/ios/documentation/IDEs/Conceptual/AppStoreDistributionTutorial/CreatingYourTeamProvisioningProfile/CreatingYourTeamProvisioningProfile.html), we bucket the device into the Development environment. You can change this by forcing an environment.

All devices that fall into the Development environment, Taplytics will use the [Development Push Notification Certificate](https://developer.apple.com/library/ios/documentation/IDEs/Conceptual/AppDistributionGuide/ConfiguringPushNotifications/ConfiguringPushNotifications.html) to attempt to send push notifications to your devices.

#### Production Bucketing

If the app is built using a [Distribution Provisioning Profile](https://developer.apple.com/library/ios/documentation/IDEs/Conceptual/AppDistributionGuide/TestingYouriOSApp/TestingYouriOSApp.html), we bucket the device into the Production environment. Note that this means that if you're distributing Ad-Hoc or Enterprise builds through a service like [Testflight](https://developer.apple.com/testflight/) or [Hockeyapp](http://hockeyapp.net/features/), then all those devices running those builds will fall into the Production environment. You can change this by forcing an environment.

All devices that fall into the Production environment, Taplytics will use the [Production Push Notification Certificate](https://developer.apple.com/library/ios/documentation/IDEs/Conceptual/AppDistributionGuide/ConfiguringPushNotifications/ConfiguringPushNotifications.html) to attempt to send push notifications to your devices.

#### Forcing an Environment

You can use the `options` attribute when you start Taplytics in order to force the environment that your devices are bucketed into. This can be especially useful for any Ad-Hoc and Enterprise distribution you might be doing.

Here's how you can achieve setting the Push environment:

<sub>**Objective-C**</sub>
```objc
// To bucket everyone into Production:
[Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{@"pushSandbox":@0}];

// To bucket everything into Development:
[Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{@"pushSandbox":@1}];
```

<sub>**Swift**</sub>
```swift
// To bucket everyone into Production:
Taplytics.startAPIKey("API_KEY", options: ["pushSandbox": 0])

// To bucket everything into Development:
Taplytics.startAPIKey("API_KEY", options: ["pushSandbox": 1])
```

---

## 3. Resetting Users

If you're using our User Attributes feature, you can easily disconnect a user from a device when they log out. This will prevent our system from sending push notifications to that device. It is especially important to reset the user when your push campaigns are targeted to a specific user. You can do this by calling our `resetUser:` function:

<sub>**Objective-C**</sub>
```objc
[Taplytics resetUser:^{
	// Finished User Reset
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.resetUser {
  // Finished user reset
}
```

___

## 4. Rich Push Notifications (iOS 10+)

Implementing rich push notification support can help improve user engagement with your push notifications with image content attached. Rich push notifications make use of **Notification Service Extension** on iOS 10+ to display images attached to the push notifications. We currently support JPEG and PNG images sent through the Taplytics dashboard or API.

The max image size that can be uploaded is 10mb. Note that images are not downscaled and if an image is sent, the full file size of the crop will be used.

![image](https://github.com/taplytics/Taplytics-iOS-SDK/blob/master/third%20party%20integrations/rich-push-example.jpg?raw=true)


#### Create a Notification Service Extension

You'll need to add a Notification Service Extension to your app which is a small extension to your app that downloads the image attached to the notification and displays it as part of the notification. To create the extension open *File > New > Target* in Xcode, select **Notification Service Extension**, then name your service extension and create it with language **Swift**.

![image](https://github.com/taplytics/Taplytics-iOS-SDK/blob/master/third%20party%20integrations/notification-service-extension.png?raw=true)

Once you've created the Notification Service Extension you should have a file called *NotificationService.swift*, open that up and edit it's *didReceiveRequestWithContentHandler* method with the following code:

```swift
override func didReceive(_ request: UNNotificationRequest, withContentHandler contentHandler: @escaping (UNNotificationContent) -> Void) {
    self.contentHandler = contentHandler
    self.bestAttemptContent = request.content.mutableCopy() as? UNMutableNotificationContent

    // look for existance of taplytics data with image_url
    if let tlData = request.content.userInfo["taplytics"] as? [String: Any], let imageUrl = tlData["image_url"] as? String, let url = URL(string: imageUrl) {
        URLSession.shared.downloadTask(with: url) { (location, response, error) in
            if let location = location {
                // get path in temp directory for file
                let tempFileURL = URL(string: "file://".appending(NSTemporaryDirectory()).appending(url.lastPathComponent))!

                var attachment: UNNotificationAttachment?
                do {
                    // move file into temp directory to be displayed by Notification Service Extension
                    if (FileManager.default.fileExists(atPath: tempFileURL.relativePath)) {
                        try FileManager.default.removeItem(at: tempFileURL)
                    }
                    try FileManager.default.moveItem(at: location, to: tempFileURL)

                    // generate image attachment
                    attachment = try UNNotificationAttachment(identifier: "tl_image", url: tempFileURL)
                } catch let error {
                    print("Error: \(error)")
                }

                // Add the attachment to the notification content
                if let attachment = attachment {
                    self.bestAttemptContent?.attachments = [attachment]
                }
            }

            // render notification
            self.contentHandler!(self.bestAttemptContent!)
        }.resume()
    } else {
        // If there is no image payload render the notification as a normal notification.
        self.contentHandler!(self.bestAttemptContent!)
    }
}
```

What this code is doing is looking for any data attached to the push payload under a `taplytics` object, and specifically looking for a `taplytics.image_url` url to download an image from, which will then start a `downloadTask` for that url. Once the image is downloaded it will move the image to the Extension's temp directory and add the image as a notification attachment to the push, and finally render the notification to display it.

Any push notifications sent without the image url attached to its data will display as normal by iOS.

___

## 5. Push Notification Payload

If you are handling push notifications with custom payloads, the custom data key/values will be added to the base object as seen below:

```json
{
	"custom_data_key": "custom_data_value",
	"aps": {
		"alert": "Test Push",
		"badge": 1,
		"sound": "default",
		"tl_id": "",
		"content-available": "1",
		"mutable-content": "1"
	},
	"taplytics": {
		"image_url": ""
	}
}
```
