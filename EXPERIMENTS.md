Creating experiments is easy using Taplytics. You can either use our visual editor or create code-based experiments. You can find documentation on how to do this below.

| Table of Contents |
| ----------------- |
| [Dynamic Variables & Code Blocks](#dynamic-variables-&-code-blocks) |
| [Code Experiments](#code-experiments) |
| [Visual Editing](#visual-editing) |
| [First-view Experiments](#delay-load) |
| [List Running Experiments](#running-experiments) |

## Dynamic Variables & Code Blocks

**To see and modify these variables or blocks on the dashboard, the app must be launched and this code containing the variable or block must be navigated to a least once.**

The code below is used to send the information of the variable or block to Taplytics, so it will appear on the dashboard.

###Dynamic Variables

Taplytics variables are dynamic variables that can be used to change content or functionality of your app dynamically from the Taplytics website. Variables are re-useable between experiments and are instantiated with three variables:

1. Variable name (String)
2. Default Value
 
*Variables should always implement the update code block, the value of the variable can be changed asynchronously once experiment properties are loaded from Taplytics Servers, but always called before your app's launch image is hidden.
 
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

Similar to Dynamic Variables, Taplytics has an option for 'Code Blocks'. Code blocks are linked to Experiments through the Taplytics website very much the same way that Dynamic Variables are, and will be executed based on the configuration of the experiment through the Taplytics website. A Code Block is a callback that can be enabled or disabled depending on the variation. If enabled, the code within the callback will be executed. If disabled, the variation will not get the callback.

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
    
## Code Experiments (Deprecated)

#### Setup

To set up a code-based experiment in Taplytics, please refer to the [Taplytics code-based experiment docs](https://taplytics.com/docs/guides/code-experiments).

#### Usage

Taplytics automatically generates the base needed for your code experiment. Paste it into the relevant section of your app, and apply the variables as necessary.

*Note that the Dictionary of variables can be empty, if your app loads for the first time and is unable to download properties from Taplytics servers, the baseline block will be called with an empty Dictionary. This will  cause all your code variables to be null, it is good practice to set a default value as shown below.

#### Objective-C Experiments

For example, an experiment named "Code Experiment #1" with a baseline block, and two variation blocks. Within each block we can get a `numberValue` variable from the `variables` NSDictionary, variables can have a different values set for each variation.
    
```objc
[Taplytics runCodeExperiment:@"Code Experiment #1" withBaseline:^(NSDictionary *variableDic) {
    // code variables can be null
    NSNumber* numberValue = variableDic[@"numberValue"] ? variableDic[@"numberValue"] : @0; 
    // Insert baseline experiment code here
} variations:@{@"Variation 1": ^(NSDictionary *variableDic) {
    // code variables can be null
    NSNumber* numberValue = variableDic[@"numberValue"] ? variableDic[@"numberValue"] : @1; 
    // Insert Variation 1 variation code here
}, @"Variation 2": ^(NSDictionary *variableDic) {
    // code variables can be null
    NSNumber* numberValue = variableDic[@"numberValue"] ? variableDic[@"numberValue"] : @2; 
    // Insert Variation 2 variation code here
}}];
```

#### Swift Experiments

Due to how blocks/closures are handled in Swift, passing blocks/closures in an NSDictioary as we do in `runCodeExperiment:withBaseline:variations:` is not well supported. The `runCodeExperiment:forBaseline:forVariation:` method handles the same functionality for Swift code.

For example the same code experiment in Objective-C from above, using Swift:

```swift
Taplytics.runCodeExperiment("Code Experiment #1",
    forBaseline: { variables in
        let numberValue: NSNumber? = variables?["numberValue"] as? NSNumber // can be null
        // Insert baseline experiment code here
    },
    forVariation: { variationName, variables in
        let numberValue: NSNumber? = variables?["numberValue"] as? NSNumber // can be null
        if variationName == "Variation 1" {
            // Insert Variation 1 variation code here
        }
        else if variationName == "Variation 2" {
            // Insert Variation 2 variation code here
        }
    }
)
```

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

If you would like to see which variations and experiments are running on a given device, there exists a `getRunningExperimentsAndVariations()` function which provides a callback with the current experiments and their running variation. An example:

```obc
[Taplytics getRunningExperimentsAndVariations:^(NSDictionary *experimentsAndVariations) {
    // For example: 
    // NSDictionary* experimentsAndVariations = @{
    //  @"Experiment 1": @"baseline",
    //  @"Experiment 2": @"Variation 1"
    //};
}];
```
NOTE: The block can return asynchronously once Taplytics properties have loaded. The block will return a `NSDictionary` with experiment names as the key value, and variation names as the value.
