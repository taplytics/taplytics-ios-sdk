Creating experiments is easy using Taplytics. You can either use our visual editor or create code-based experiments. You can find documentation on how to do this below.

| Table of Contents |
| ----------------- |
| [Dynamic Variables & Code Blocks](#dynamic-variables--code-blocks) |
| [Code Experiments](#code-experiments-deprecated) |
| [Visual Editing](#visual-editing) |
| [First-view Experiments](#delay-load) |
| [List Running Experiments](#running-experiments) |

## Dynamic Variables & Code Blocks

**To see and modify these variables or blocks on the dashboard, the app must be launched and this code containing the variable or block must be navigated to a least once.**

The code below is used to send the information of the variable or block to Taplytics, so it will appear on the dashboard.

### Dynamic Variables

Taplytics variables are values in your app that are controlled by experiments. Changing the values can update the content or functionality of your app. Variables are reusable between experiments and operate in one of two modes: synchronous or asynchronous.

#### Synchronous

Synchronous variables are guaranteed to have the same value for the entire session and will have that value immediately after construction. 

Due to the synchronous nature of the variable, if it is used before the experiments have been loaded from Taplytics servers (for example on the first launch of your app), it's value will be the default value rather than the value set for that experiment. This could taint the results of the experiment. In order to prevent this you can ensure that the experiments are loaded before using the variable. This can be done using the `propertiesLoadedCallback:` method, as an example: 

```objc
[Taplytics propertiesLoadedCallback:^(BOOL loaded) {
    [self loadTLVariables];
}];
```

Note that this must be done only _after_ startTaplytics. 

Synchronous variables take two parameters in its constructor:

1. Variable name (String)
2. Default Value

The type of the variable is defined by the type of the Default Value and can be a JSON serializable `NSDictionary`, `NSString`, `NSNumber` or a `Boolean` casted to a `NSNumber`. 

For example, using a variable of type `String`, using its value to get the value of the variable:
```objc
TaplyticsVar* stringVar = [TaplyticsVar taplyticsSyncVarWithName:@"stringVar" defaultValue:@"string"];
NSString* string = (NSString*)stringVar.value;
```
 
Using a casted `Boolean` to a `NSNumber`:

```objc
TaplyticsVar* boolVar = [TaplyticsVar taplyticsSyncVarWithName:@"boolVar" defaultValue:@(YES)];
BOOL boolean = [(NSNumber*)boolVar.value boolValue];
```

#### Asynchronous

Asynchronous variables take care of insuring that the experiments have been loaded before returning a value. This removes any danger of tainting the results of your experiment with bad data. What comes with the insurance of using the correct value is the possibility that the value will not be set immediately. If the variable is constructed *before* the experiments are loaded, you won't have the correct value until the experiments have finished loading. If the experiments fail to load, then you will be given the default value, as specified in the variables constructor.

Asynchronous variables take three parameters in its constructor:

1. Variable name (String)
2. Default Value
3. TLVarBlock

Just as for synchronous variables the type of the variable is defined by the type of the default value, and can be a `NSString`, `NSNumber` or a `Boolean` casted to a `NSNumber`. 

For example, using a variable of type `NSNumber`:

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

When the variable's value has been updated, the updated block will be called with that updated value. Note that we only store a weak reference to your variables, for the updated block to work correctly you will need to store a strong reference to the variable object.

**Note: Default values for dynamic variables cannot be NULL. NULL values may cause default to trigger in all scenarios**

#### Testing Dynamic Variables

When testing dynamic variables in live update mode you can change the values on the fly via the taplytics interface and you can switch variations with the shake menu on the device.

**Important Note:** When testing synchronous dynamic variables you must initialize the variable again to see the new value, as there are no callbacks which occur when the variable is updated with a new value.

This can be achieved by using a properties loaded callback. Here is an example for updating a label:

```objc
__weak id weakSelf = self;
[Taplytics propertiesLoadedCallback:^(BOOL loaded) {
    TaplyticsVar* var = [TaplyticsVar taplyticsSyncVarWithName:@"stringVar" defaultValue:@"defaultValue"];
    if (weakSelf && weakSelf.label) {
        weakSelf.label.text = var.value;
    }
}];
```

### Code Blocks

Similar to Dynamic Variables, Taplytics has an option for **Code Blocks**. Code Blocks are linked to Experiments through the Taplytics website very much the same way that Dynamic Variables are, and will be executed based on the configuration of the experiment through the Taplytics website. 

A Code Block is a callback that can be enabled or disabled depending on the variation. If the Code Block is enabled for the current variation, the code within the callback will be executed asynchronously when Taplytics properties are loaded. If the Code Block is disabled for the current variation, the callback will not be executed.

A Code Block can be used alongside as many other Code Blocks as you would like to determine a combination that yields the best results. Perhaps there are three different Code Blocks on one view. This means there could be 8 different combinations of Code Blocks being enabled / disabled on that view if you'd like.

Example Using Objective-C:

```objc
[Taplytics runCodeBlock:@"enableFeature" forBlock:^{
    // enable your feature here
}];
```

Example Using Swift: 

```swift
Taplytics.runCodeBlock("enableFeature", forBlock: {
    // enable your feature here
})
```
    
## Testing Specific Experiments

To test/QA specific experiment and variation combinations use the `TaplyticsOptionTestExperiments` start option with a  `NSDictionary` containing keys of the experiment names, and values of variation names (or `baseline`).

```objc
[Taplytics startTaplyticsAPIKey:@"API_KEY" options:@{
    TaplyticsOptionTestExperiments: @{
        @"Experiment 1": @"Variation 1",
        @"Experiment 2": @"baseline"
    }
}];
```

---

## Visual Editing
You don't have to do anything else! You can use the Taplytics dashboard to make all your visual changes. See the docs on visual editing [here](https://taplytics.com/docs/guides/visual-experiments).

---

## Delay Load

On the first launch of your app, the Taplytics SDK will show your iOS launch image up to a maximum 4 seconds while it downloads properties from Taplytics servers. This delay will enable you to run experiments in the first view of your app.

If you would like to disable showing the launch image:

```objc
[Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here" options:@{TaplyticsOptionDelayLoad:@0}];
```

Or increase the maximum wait time to 10 seconds:

```objc
[Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here" options:@{TaplyticsOptionDelayLoad:@10}];
```

---

## Running Experiments

If you would like to see which variations and experiments are running on a given device, there exists a `getRunningExperimentsAndVariations()` function which provides a callback with the current experiments and their running variation. An example:

```objc
[Taplytics getRunningExperimentsAndVariations:^(NSDictionary *experimentsAndVariations) {
    // For example: 
    // NSDictionary* experimentsAndVariations = @{
    //  @"Experiment 1": @"baseline",
    //  @"Experiment 2": @"Variation 1"
    //};
}];
```
NOTE: The block can return asynchronously once Taplytics properties have loaded. The block will return a `NSDictionary` with experiment names as the key value, and variation names as the value.

## Sessions

By default, Taplytics defines a session as when a user is using the app with less than 10 minutes of inactivity. If the app has been backgrounded for 10 minutes, the next time the user opens the app it will be considered a new session. Similarly, if the app is entirely force closed, the next time the app is opened, it will be considered a new session.

### Manually starting a new session

To manually force a new user session (ex: A user has logged in / out), there exists a ```startNewSession``` method.

If there is an internet connection, a new session will be created, and new experiments/variations will be fetched from Taplytics if they exist. 

It can be used as follows:

```java
    [Taplytics startNewSession:^(BOOL success) {
        //New session here! Success will be false if this failed.
    }]```

