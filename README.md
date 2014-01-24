# Taplytics iOS SDK

_Description: Taplytics is a native mobile A/B testing platform that allows you to create new tests and push them live without any code updates!_

## Project Setup

_How do I, as a developer, start using Taplytics?_ 

1. _Sign up for a free account at Taplytics.com._
2. _Install the SDK._
3. _Create an experiment and push it live to your users!_

## Installation Instructions (using CocoaPods)
    
1. _Install using CocoaPods_
    - Add a Podfile to the root of your project directory with the following:

    ```ruby
    platform :ios
    pod 'Taplytics'
    ```
    
2. _Add an import for the taplytics framework to your _prefix.pch file._
    
    ```
    // YourApp_prefix.pch:
    #ifdef __OBJC__
      #import <Foundation/Foundation.h>
      #import <UIKit/UIKit.h>
      // Add the following line:
      #import <Taplytics/Taplytics.h>
    #endif
    ```

3. _Initialize the SDK by adding a line of code with your API key in your AppDelegate.m file_

    
    ```objective-c
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
        ...
        [TaplyticsManager startTaplyticsAPIKey:@"Your App Token Here"];
        ...
    }
    ```

## Installation Instructions (Manual Installation)


1. _Download the SDK / clone into your app._
2. _Load the Taplytics framework into your app._
3. _Add the required frameworks:_
    
    ```objective-c
    CFNetwork.framework
    Security.framework
    CoreTelephony.framework
    AdSupport.framework
    SystemConfiguration.framework
    libicucore.dylib
    ```
4. _Add the -ObjC Linker flag to your project settings_
5. _Add an import for the taplytics framework to your _prefix.pch file._

    ```objective-c
    
    // YourApp_prefix.pch:
    
    #ifdef __OBJC__
      #import <Foundation/Foundation.h>
      #import <UIKit/UIKit.h>
      // Add the following line:
      #import <Taplytics/Taplytics.h>
    #endif
    ```

6. _Initialize the SDK by adding a line of code with your API key in your AppDelegate.m file_
    
    ```objective-c
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    ...
    [TaplyticsManager startTaplyticsAPIKey:@"Your App Token Here" liveUpdate:YES];
    
    //For internal builds, use liveUpdate:YES. For public builds, use liveUpdate:NO.
    ...
    }
    ```

## Questions or Need Help?

_The taplytics team is available 24/7 to answer any questions you have. Just email help@taplytics.com or visit http://help.taplytics.com for more detailed installation and usage information._
