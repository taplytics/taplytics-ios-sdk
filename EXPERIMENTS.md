Creating experiments are easy using Taplytics. You can either use our visual editor or create code-based experiments. You can find documentation on how to do this below.

| Table of Contents |
| ----------------- |
| [Code Experiments](#code-experiments) |
| [Visual Editing](#visual-editing) |
| [First-view Experiments](#delay-load) |
| [List Running Experiments](#running-experiments) |


## Code Experiments

Taplytics not only lets you run visual experiments with no code needed, the SDK also offers a code-based solution to running experiments in your app.

Code Experiments allow you to run different variations of your app with simple code blocks. You can also set different variable values for each variation to be returned in the code blocks. 

Note that the Dictionary of variables can be empty, if your app loads for the first time an is unable to download properties from Taplytics servers the baseline block will be called with an empty Dictionary. This will obviously cause all your code variables to be null, it is good practice to set a default value as seen below.

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
    
#### Testing Code Experiments

Implementing the TaplyticsDelegate is not necessary to properly run code-based experiments. But with code experiments you will only see the changes when the runCodeExperiment block is actually excecuted, so when you switch between variations you might not see changes until the view has been reloaded. If you would like to see these changes when you change variations (for example when you shake a development build and choose a different variation to test), you will have to implement the TaplyticsDelegate.

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
        [Taplytics runCodeExperiment:@"My Code Experiment" withBaseline:^(NSDictionary *variables) {
            //  Code for baseline
        } variations:@{@"variation 1": ^(NSDictionary *variables) {
            // Code for variation 1
        }}];
    }
    
    // TaplyticsDelegate
    - (void)taplyticsExperimentChanged:(NSString*)experimentName variationName:(NSString*)variationName {
        [self runMyCodeExperiment];
    }
    ```

---

## Visual Editing

You don't have to do anything else! All visual editing is done on the Taplytics dashboard. See the docs on visual editing [here](https://taplytics.com/docs/visual-experiments).

---

## Delay Load

On the first launch of your app the Taplytics SDK will show your iOS launch image up to a maximum 2 seconds while it downloads properties from Taplytics servers. This enables you to run experiments on the first view of your app.

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

The Taplytics SDK can tell you what experiments and variations are currently runing. The block can return asynchronously once Taplytics properties have loaded. The block will return a `NSDictionary` with experiment names as the key value, and variation names as the value.

```obc
[Taplytics getRunningExperimentsAndVariations:^(NSDictionary *experimentsAndVariations) {
    // For example: 
    // NSDictionary* experimentsAndVariations = @{
    //  @"Experiment 1": @"baseline",
    //  @"Experiment 2": @"Variation 1"
    //};
}];
```