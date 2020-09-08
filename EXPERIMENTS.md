Creating experiments is easy using Taplytics. You can either use our visual editor or create code-based experiments. You can find documentation on how to do this below.

#### *Note: The visual editor is only available in our iOS framework, not available on tvOS.*

| Table of Contents |
| ----------------- |
| [Dynamic Variables & Code Blocks](#dynamic-variables--code-blocks) |
| [Feature Flags](#feature-flags) |
| [Visual Editing](#visual-editing) |
| [First-view Experiments](#delay-load) |
| [List Running Experiments](#running-experiments) |

## Dynamic Variables & Code Blocks

**To see and modify these variables or blocks on the dashboard, the app must be launched and this code containing the variable or block must be navigated to a least once.**

The code below is used to send the information of the variable or block to Taplytics, so it will appear on the dashboard.

### Dynamic Variables

Taplytics variables are values in your app that are controlled by experiments. Changing the values can update the content or functionality of your app. Variables are reusable between experiments and operate in one of two modes: synchronous or asynchronous. If logging is enabled, logs will show the value when a variable has been set or updated.

#### Synchronous

Synchronous variables are guaranteed to have the same value for the entire session and will have that value immediately after construction.

Due to the synchronous nature of the variable, if it is used before the experiments have been loaded from Taplytics servers (for example on the first launch of your app), it's value will be the default value rather than the value set for that experiment. This could taint the results of the experiment. In order to prevent this you can ensure that the experiments are loaded before using the variable. This can be done using the `newSessionCallback:` method, as an example:

<sub>**Objective-C**</sub>
```objc
[Taplytics newSessionCallback:^(BOOL loaded) {
    [self loadTLVariables];
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.newSessionCallback { (loaded) in
    loadTLVariables()
}
```

Note that this must be done only _after_ startTaplytics.

Synchronous variables take two parameters in its constructor:

1. Variable name (String)
2. Default Value

The type of the variable is defined by the type of the Default Value and can be a JSON serializable `NSDictionary`, `NSString`, `NSNumber` or a `Boolean` casted to a `NSNumber`.

We do support arrays within JSON code variables, however, it has to be a top level array where it would resemble something like this `{"a" : [1,2,3]}`.

Here's an example, using a variable of type `String`, using its value to get the value of the variable:

<sub>**Objective-C**</sub>
```objc
TaplyticsVar* stringVar = [TaplyticsVar taplyticsSyncVarWithName:@"stringVar" defaultValue:@"string"];
NSString* string = (NSString*)stringVar.value;
```

<sub>**Swift**</sub>
```swift
let stringVar = TaplyticsVar.sync(name: "stringVar", defaultValue: "string" as NSString)
let string = stringVar.value as? String
```

Using a casted `Boolean` to a `NSNumber`:

<sub>**Objective-C**</sub>
```objc
TaplyticsVar* boolVar = [TaplyticsVar taplyticsSyncVarWithName:@"boolVar" defaultValue:@(YES)];
BOOL boolean = [(NSNumber*)boolVar.value boolValue];
```

<sub>**Swift**</sub>
```swift
let boolVar = TaplyticsVar.sync(name: "boolVar", defaultValue: true as NSNumber)
let boolean = boolVar.value as? Bool
```

#### Asynchronous

Asynchronous variables take care of insuring that the experiments have been loaded before returning a value. This removes any danger of tainting the results of your experiment with bad data. What comes with the insurance of using the correct value is the possibility that the value will not be set immediately. If the variable is constructed *before* the experiments are loaded, you won't have the correct value until the experiments have finished loading. If the experiments fail to load, then you will be given the default value, as specified in the variables constructor.

Asynchronous variables take three parameters in its constructor:

1. Variable name (String)
2. Default Value
3. TLVarBlock

Just as for synchronous variables the type of the variable is defined by the type of the default value, and can be a `NSString`, `NSNumber` or a `Boolean` casted to a `NSNumber`.

For example, using a variable of type `NSNumber`:

<sub>**Objective-C**</sub>
```objc
// In your Interface create a strong reference to the variable
@property (nonatomic, strong) TaplyticsVar* tlVar;

// Using the variable in your code:
self.tlVar = [TaplyticsVar taplyticsVarWithName:@"numVar" defaultValue:@(1) updatedBlock:^(NSObject *value) {
    if (value) {
        NSNumber* num = (NSNumber*)value;
    }
}];
```

<sub>**Swift**</sub>
```swift
self.tlVar = TaplyticsVar.async(name: "numVar", defaultValue: 1 as NSNumber) { (updatedValue) in
    guard let value = updatedValue as? NSNumber else {
        return
    }
    // use value
}
```

When the variable's value has been updated, the updated block will be called with that updated value. Note that we only store a weak reference to your variables, for the updated block to work correctly you will need to store a strong reference to the variable object.

**Note: Default values for dynamic variables cannot be NULL. NULL values may cause default to trigger in all scenarios**

#### Testing Dynamic Variables

When testing dynamic variables in live update mode you can change the values on the fly via the taplytics interface and you can switch variations with the shake menu on the device.

**Important Note:** When testing synchronous dynamic variables you must initialize the variable again to see the new value, as there are no callbacks which occur when the variable is updated with a new value.

This can be achieved by using a properties loaded callback. Here is an example for updating a label:

<sub>**Objective-C**</sub>
```objc
__weak id weakSelf = self;
[Taplytics newSessionCallback:^(BOOL loaded) {
    TaplyticsVar* var = [TaplyticsVar taplyticsSyncVarWithName:@"stringVar" defaultValue:@"defaultValue"];
    if (weakSelf && weakSelf.label) {
        weakSelf.label.text = var.value;
    }
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.newSessionCallback { (loaded) in
    guard loaded, let label = self.label else {
        return
    }

    let stringVar = TaplyticsVar.sync(name: "stringVar", defaultValue: "string" as NSString)
    if let stringValue = stringVar.value as? String {
        label.text = stringValue
    }
}
```

### Testing Specific Experiments

To test/QA specific experiment and variation combinations use the `TaplyticsOptionTestExperiments` start option with a  `NSDictionary` containing keys of the experiment names, and values of variation names (or `baseline`).

<sub>**Objective-C**</sub>
```objc
[Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{
    TaplyticsOptionTestExperiments: @{
        @"Experiment 1": @"Variation 1",
        @"Experiment 2": @"baseline"
    }
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.startAPIKey("API_KEY", options: [
    TaplyticsOptionTestExperiments: [
        "Experiment 1": "Variation 1",
        "Experiment 2": "baseline"
    ]
])
```

---

## Feature Flags

Taplytics feature flags operate in synchronous mode. They also support optional default values that can be set to `true` or `false` in the case where the user does not have the feature flag enabled.

### Synchronous

Synchronous feature flags are guaranteed to have the same value for the entire session and will have that value immediately after construction.

<sub>**Objective-C**</sub>
```
if ([Taplytics featureFlagEnabled:@"featureFlagKey" defaultValue:NO]) {
    // Put feature code here, or launch feature from here
}
```

<sub>**Swift**</sub>
```swift
if (Taplytics.featureFlagEnabled(key: "featureFlagKey", defaultValue: false)) {
    // Put feature code here, or launch feature from here
}
```

Due to the synchronous nature of feature flags, if it is used before the feature flags have been loaded from Taplytics servers (for example on the first launch of your app), it will default to as if the feature flag is not present. In order to prevent this you can ensure that the feature flags are loaded before using the feature flag. This can be done using the `newSessionCallback:` method, as an example:

<sub>**Objective-C**</sub>
```objc
[Taplytics newSessionCallback:^(BOOL loaded) {
    if ([Taplytics featureFlagEnabled:@"featureFlagKey"]) {
        // Put feature code here, or launch feature from here
    }
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.newSessionCallback { (loaded) in
    if (Taplytics.featureFlagEnabled(key: "featureFlagKey")) {
        // Put feature code here, or launch feature from here
    }
}
```

---

## Running Feature Flags

If you would like to see which feature flags are running on a given device, there exists a `getRunningFeatureFlags()` function which provides a callback with the current experiments and their running variation. An example:

<sub>**Objective-C**</sub>
```objc
[Taplytics getRunningFeatureFlags:^(NSDictionary *featureFlags) {
    // For example featureFlags will contain:
    // @{
    //     @"Feature Flag 1's Name": @"Feature Flag 1's Key",
    //     @"Feature Flag 2's Name": @"Feature Flag 2's Key"
    // };
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.getRunningFeatureFlags { (featureFlags) in
    // For example featureFlags will contain:
    // [
    //     @"Feature Flag 1's Name": @"Feature Flag 1's Key",
    //     @"Feature Flag 2's Name": @"Feature Flag 2's Key"
    // ]
}
```

NOTE: The block can return asynchronously once Taplytics properties have loaded. The block will return a `NSDictionary` with feature flag names as the key value, and feature flag keys as the value.

---

## Visual Editing
You don't have to do anything else! You can use the Taplytics dashboard to make all your visual changes. See the docs on visual editing [here](https://docs.taplytics.com/docs/guides-visual-experiments).

### Accessibility Identifier Matching [v2.37.0]

Visual editing works best on static elements so that the visual editor can identify the elements easier. If your element's attributes morphs, it can get missed when applying edits. 

You can set an `accessibilityIdentifier` on your element through the interface builder so that the visual editor can identify the element needed to apply the correct change. To enable this functionality, set `TaplyticsOptionMatchByAccessibilityIdentifier` to `@YES` in your starting options.

*Note: Only available using our iOS framework, not available on tvOS.*

---

## Delay Load

On the first launch of your app, the Taplytics SDK will show your iOS launch image up to a maximum 4 seconds while it downloads properties from Taplytics servers. This delay will enable you to run experiments in the first view of your app.

If you would like to disable showing the launch image:

<sub>**Objective-C**</sub>
```objc
[Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{TaplyticsOptionDelayLoad:@0}];
```

<sub>**Swift**</sub>
```swift
Taplytics.startAPIKey("API_KEY", options: [TaplyticsOptionDelayLoad: 0])
```

Or increase the maximum wait time to 10 seconds:

<sub>**Objective-C**</sub>
```objc
[Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{TaplyticsOptionDelayLoad:@10}];
```

<sub>**Swift**</sub>
```swift
Taplytics.startAPIKey("API_KEY", options: [TaplyticsOptionDelayLoad: 10])
```

---

## Running Experiments

If you would like to see which variations and experiments are running on a given device, there exists a `getRunningExperimentsAndVariations()` function which provides a callback with the current experiments and their running variation. If logging is enabled, logs will also show them.

An example:

<sub>**Objective-C**</sub>
```objc
[Taplytics getRunningExperimentsAndVariations:^(NSDictionary *experimentsAndVariations) {
    // For example experimentsAndVariations will contain:
    // @{
    //     @"Experiment 1": @"baseline",
    //     @"Experiment 2": @"Variation 1"
    // };
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.getRunningExperimentsAndVariations { (experimentsAndVariations) in
    // For example experimentsAndVariations will contain:
    // [
    //    "Experiment 1": "baseline",
    //    "Experiment 2": "Variation 1",
    // ]
}
```

NOTE: The block can return asynchronously once Taplytics properties have loaded. The block will return a `NSDictionary` with experiment names as the key value, and variation names as the value.

## Sessions

By default, Taplytics defines a session as when a user is using the app with less than 10 minutes of inactivity. If the app has been backgrounded for 10 minutes, the next time the user opens the app it will be considered a new session. Similarly, if the app is entirely force closed, the next time the app is opened, it will be considered a new session.

### Manually starting a new session

To manually force a new user session (ex: A user has logged in / out), there exists a ```startNewSession``` method.

If there is an internet connection, a new session will be created, and new experiments/variations will be fetched from Taplytics if they exist. If logging is enabled, logs will show when a new session has been started or if an error has occurred.

It can be used as follows:

<sub>**Objective-C**</sub>
```objc
[Taplytics startNewSession:^(BOOL success) {
    // New session here! Success will be false if this failed.
}];
```

<sub>**Swift**</sub>
```swift
Taplytics.startNewSession { (success) in
    // New session here! Success will be false if this failed.
}
```

## Debugging

The shake menu allows you to switch variations on your device on the fly. You can use the shake functionality to open it, or you can call it in code like so:

<sub>**Objective-C**</sub>

```objc
[Taplytics showMenu];
```

<sub>**Swift**</sub>

```swift
Taplytics.showMenu()
```
