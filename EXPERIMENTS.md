Creating experiments are easy using Taplytics. You can either use our visual editor or create code-based experiments. You can find documentation on how to do this below.

| Table of Contents |
| ----------------- |
| [Dynamic Variables & Code Blocks](#dynamic-variables-&-code-blocks) |
| [Code Experiments](#code-experiments) |
| [Visual Editing](#visual-editing) |
| [First-view Experiments](#delay-load) |
| [List Running Experiments](#running-experiments) |

## Dynamic Variables & Code Blocks

###Dynamic Variables

Taplytics Variables are dynamic variables that can be used to change content or functionality of your app dynamically from the Taplytics website. Variables are re-useable between experiments and are defined with a name and default value that is used when there is no internet connection or when variables are not currently attached to any experiments.
 
Variables should always implement the update code block, the value of the variable can be changed asynchronously once experiment properties are loaded from Taplytics Servers, but always called before your app's launch image is hidden.
 
Variables can be NSString, NSNumber, and Booleans casted into NSNumbers.
 
For example using a NSString to set label text:
 
```objc
TaplyticsVar *var = [TaplyticsVar taplyticsVarWithName:@"stringVar" defaultValue:@"Hello World" updatedBlock:^(NSObject* value) {
    // updatedBlock will be called when the value is updated.
    if (value)
        _label.text = (NSString*)value;
}];
 
// variables can also use the value property to access the value.
_label.text = (NSString*)var.value;
```
Example of Using a NSNumber: 
 
```objc
[TaplyticsVar taplyticsVarWithName:@"numberOfCells" defaultValue:@10 updatedBlock:^(NSObject* value) {
    if (value)
        [weakSelf setNumberOfCells:value];
}];
```

Example of Using a Boolean casted as NSNumber:

```objc 
[TaplyticsVar taplyticsVarWithName:@"useNewCheckout" defaultValue:@(NO) updatedBlock:^(NSObject* value) {
    if (value)
        [weakSelf useNewCheckout:[(NSNumber*)value boolValue]];
}];
```

### Code Blocks

Taplytics not only lets you run visual experiments with no code needed, the SDK also offers a code-based solution to running experiments in your app.

Code Blocks allow you to run different variations of your app with simple code modifications. Code blocks are linked to Experiments through the Taplytics website very much the same way that Dynamic Variables are. A code block will be executed based on the configuration of the experiment through the Taplytics website.

Objective-C:

```objc
[Taplytics runCodeBlock:@"enableFeature" forBlock:^{
    // enable your feature here
}];
```

Swift: 

```swift
Taplytics.runCodeBlock("enableFeature", forBlock: {
    // enable your feature here
})
```
    
## Code Experiments (Deprecated)

#### Previewing Code Experiments

Implementing the TaplyticsDelegate is not necessary to properly run code-based experiments in a live environment, but with code experiments you will only see the changes when the runCodeExperiment block is executed. This means that when you are in a development environment and you switch between variations, you might not see changes until the view has been reloaded. If you would like to see these changes when you change variations (for example when you shake a development build to pull up the Taplytics Menu and choose a variation to test), you will have to implement the TaplyticsDelegate.

1. Add the TaplyticsDelegate to your Class

    ```objc
    #import <Taplytics/Taplytics.h>
    @interface SampleViewController : ViewController <TaplyticsDelegate>
    ```
2. Add the `taplyticsExperimentChanged:experimentName:variationName:` method to your Class and register the delegate with Taplytics using `setTaplyticsDelegate:`. Then call your code experiment again from that method. This delegate method will be called everytime the current variation is changed on the website or the shake menu.

    ```objc
    - (void)viewDidLoad {
        [super viewDidLoad];
        [Taplytics setTaplyticsDelegate:self];
        [self runMyCodeExperiment];
    }
    
    - (void)runMyCodeExperiment {
        [Taplytics runCodeBlock:@"enableFeature" forBlock:^{
            // enable your feature here
        }];
    }
    
    // TaplyticsDelegate
    - (void)taplyticsExperimentChanged:(NSString*)experimentName variationName:(NSString*)variationName {
        [self runMyCodeExperiment];
    }
    ```

---

## Visual Editing
You don't have to do anything else! You can use the Taplytics dashboard to make all your visual changes. See the docs on visual editing [here](https://taplytics.com/docs/guides/visual-experiments).

---

## Delay Load

On the first launch of your app, the Taplytics SDK will show your iOS launch image up to a maximum 4 seconds while it downloads properties from Taplytics servers. This delay will enable you to run experiments in the first view of your app.

If you would like to disable showing the launch image:

```obc
[Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here" options:@{@"delayLoad":@0}];
```

Or increase the maximum wait time to 10 seconds:

```obc
[Taplytics startTaplyticsAPIKey:@"Your_App_Token_Here" options:@{@"delayLoad":@10}];
```

---

## Running Experiments

The Taplytics SDK can tell you what experiments and variations are currently running. The block can return asynchronously once Taplytics properties have loaded. The block will return a `NSDictionary` with experiment names as the key value, and variation names as the value.

```obc
[Taplytics getRunningExperimentsAndVariations:^(NSDictionary *experimentsAndVariations) {
    // For example: 
    // NSDictionary* experimentsAndVariations = @{
    //  @"Experiment 1": @"baseline",
    //  @"Experiment 2": @"Variation 1"
    //};
}];
```
