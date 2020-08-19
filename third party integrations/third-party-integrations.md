# Third Party Integrations

### Push your experiments to your favourite analytics sources

The Taplytics SDK can automatically push experiments to the following Analytics Sources:

| [iOS SDK](#ios) | [Android SDK](#android)           
| ------------- |-------------    
| <ul><li>[Google Analytics](#google-analytics-ios)</li><li>[Flurry](#flurry-ios)</li><li>[MixPanel](#mixpanel-ios)</li><li>[Amplitude](#amplitude-ios)</li><li>[Intercom](#intercom-ios)</li><li>[Apsalar](#apsalar-ios)</li><li>[Parse](#parse-ios)</li><li>[Adobe](#adobe-ios)</li><li>[Localytics](#localytics-ios)</li><li>[Heap](#heap-ios)</li><li>[Optimizely](#optimizely-ios)</li><li>[Segment](#segment-ios)</li><li>[KISSMetrics](#kissmetrics-ios)</li><li>[Firebase](#firebase-ios)</li></ul>| <ul><li>[Google Analytics](#Google-Analytics-Android)</li><li>[Flurry](#flurry-android)</li><li>[MixPanel](#mixpanel-android)</li><li>[Amplitude](#amplitude-android)</li><li>[Adobe](#adobe-android)</li><li>[Localytics](#localytics-android)</li><li>[Segment](#segment-android)</li></ul>


To enable any of these, navigate to your project settings and select the analytics sources you want to use with Taplytics. If you don't see your analytics source listed here, feel free to let us know what other integrations you need.

Additionally, Taplytics will automatically track events from these sources directly into Taplytics.

![image](https://github.com/taplytics/Taplytics-iOS-SDK/blob/master/third%20party%20integrations/settings.png?raw=true)


## iOS
### Google Analytics iOS

Taplytics pushes experiment/variation info to the Google Analytics SDK in the following format:

```objectivec
id<GAITracker> tracker = [GAI sharedInstance].defaultTracker;
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 1",
    @"Experiment 2": @"baseline"
};
for (NSString* experimentName in experimentsAndVariations.allKeys) {
    NSString* variationName = experimentsAndVariations[experimentName];
    [tracker send:[[GAIDictionaryBuilder createEventWithCategory:@"TL_experiments"
                                           action:experimentName
                                            label:variationName
                                            value:nil] build]];
}
```


### Flurry iOS

Taplytics logs experiment/variation events to the Flurry iOS SDK as follows:

```objectivec
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 1",
    @"Experiment 2": @"baseline"
};
[Flurry logEvent:@"TL_experiments" withParameters:experimentsAndVariations];
```

### Mixpanel iOS

Taplytics tracks experiment/variation events to the Mixpanel iOS SDK as follows:

```objectivec
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 1",
    @"Experiment 2": @"baseline"
};
[[Mixpanel sharedInstance] track:@"TL_experiments" properties:experimentsAndVariations];
[[Mixpanel sharedInstance] registerSuperProperties:experimentsAndVariations];
```

### Intercom iOS

Taplytics logs experiment/variation events with Intercom in the following format:

```objectivec
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 1",
    @"Experiment 2": @"baseline"
};
[Intercom logEventWithName:@"TL_experiments" optionalMetaData:experimentsAndVariations];
```

### Adobe iOS

Taplytics logs experiment/variation events to the Adobe Omniture iOS SDK as follows:

```objectivec
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 1",
    @"Experiment 2": @"baseline"
};
[ADBMobile trackAction:@"TL_experiments" data:experimentsAndVariations];
```

### Localytics iOS

Taplytics logs experiment/variation events to the Localytics iOS SDK as follows:

```objectivec
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 1",
    @"Experiment 2": @"baseline"
};
[[LocalyticsSession shared] tagEvent:@"TL_experiments" attributes:experimentsAndVariations];
```
### Parse iOS

Taplytics logs experiment/variation events to the Parse iOS SDK as follows:

```objectivec 
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 1",
    @"Experiment 2": @"baseline"
};
[PFAnalytics trackEvent:@"TL_experiments" dimensions:experimentsAndVariations];
```

### Apsalar iOS

Taplytics logs experiment/variation events to the Apsalar iOS SDK as follows:

```objectivec
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 1",
    @"Experiment 2": @"baseline"
};
[Apsalar event:@"TL_experiments" withArgs:experimentsAndVariations];
```

### Segment iOS

Taplytics logs experiment/variation events to the Segment iOS SDK as follows..

Note that unlike other integrations, segment expects multiple events. Heres is an example of how a single one is sent: 

```objectivec
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 2"
};
        
[[SEGAnalytics sharedAnalytics] track:@"Experiment Viewed" properties:experimentsAndVariations];
                           
```

### Answers iOS

Taplytics logs experiment/variation events to the Fabric Answers iOS SDK as follows:

```objectivec
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 1",
    @"Experiment 2": @"baseline"
};
[Answers logCustomEventWithName:@"TL_Experiments" customAttributes:experimentsAndVariations];
```

### Kissmetrics iOS

Taplytics logs experiment/variation events to the Kissmetrics iOS SDK as follows:

```objectivec
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 1",
    @"Experiment 2": @"baseline"
};
[[KISSmetricsAPI sharedAPI] record:@"TL_Experiments" withProperties:experimentsAndVariations];
```

### Heap iOS

Taplytics logs experiment/variation events to the Heap iOS SDK as follows:

```objectivec
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 1",
    @"Experiment 2": @"baseline"
};
 [Heap track:@"TL_Experiments" withProperties:experimentsAndVariations];
```
### Amplitude iOS

As of 2.52.0, Taplytics sets experiment/variation events to the Amplitude iOS SDK as user property `TL_Experiments`. The value is an array of strings with the format:

```
[
	"exp1:var2",
	...
]
```

To log them as an event with event properties instead, use the new option: `TaplyticsOptionAmplitudeExpsAsEvents`

### Firebase iOS

Taplytics logs experiment/variation events to the Firebase iOS SDK as follows:

```objectivec
NSDictionary* experimentsAndVariations = @{
    @"Experiment 1": @"Variation 1",
    @"Experiment 2": @"baseline"
};

[FIRAnalytics logEventWithName:@"TL_Experiments" parameters:experimentsAndVariations];
```

## Android

### Google Analytics Android

Taplytics logs experiment/variation info to the Google Analytics SDK as follows:

```java
HashMap<String, String> experimentsAndVariations = new HashMap<>();
experimentsAndVariations.put("Experiment 1", "Variation 1");
experimentsAndVariations.put("Experiment 2", "Variation 3");

for (String experiment : experimentsAndVariations.keySet()) {
	googleTracker.set(experiment,experimentsAndVariations.get(experiment));
}
```

### Flurry Android

Taplytics logs experiment/variation events to the Flurry Android SDK as follows:

```java
HashMap<String, String> experimentsAndVariations = new HashMap<>();
experimentsAndVariations.put("Experiment 1", "Variation 1");
experimentsAndVariations.put("Experiment 2", "Variation 3");

FlurryAgent.logEvent("TL_Experiments", experimentsAndVariations)
```

### Mixpanel Android

Taplytics logs experiment/variation events to the Mixpanel Android SDK as follows:

```java
HashMap<String, String> experimentsAndVariations = new HashMap<>();
experimentsAndVariations.put("Experiment 1", "Variation 1");
experimentsAndVariations.put("Experiment 2", "Variation 3");

mixpanel.registerSuperProperties("TL_Experiments", experimentsAndVariations)
```

### Adobe Android

Taplytics logs experiment/variation events to the Adobe Omniture Android SDK as follows:

```java
HashMap<String, String> experimentsAndVariations = new HashMap<>();
experimentsAndVariations.put("Experiment 1", "Variation 1");
experimentsAndVariations.put("Experiment 2", "Variation 3");

Analytics.trackAction("TL_Experiments", experimentsAndVariations)
```

### Amplitude Android

Taplytics logs experiment/variation events to the Amplitude Android SDK as follows:

```java
HashMap<String, String> experimentsAndVariations = new HashMap<>();
experimentsAndVariations.put("Experiment 1", "Variation 1");
experimentsAndVariations.put("Experiment 2", "Variation 3");

Amplitude.getInstance().logEvent("TL_Experiments", experimentsAndVariations)
```

### Localytics Android

Taplytics logs experiment/variation events to the Amplitude Android SDK as follows:

```java
HashMap<String, String> experimentsAndVariations = new HashMap<>();
experimentsAndVariations.put("Experiment 1", "Variation 1");
experimentsAndVariations.put("Experiment 2", "Variation 3");

Localytics.tagEvent("TL_Experiments", experimentsAndVariations)
```

### Segment Android

Taplytics logs each experiment and variation to segment individually along with their experiment and variation ids. 

While the following isn't exactly how Taplytics handles the data, it serves to give you an idea of how experiment/variation data is sent to Segment.

```java
HashMap experiment1 = new HashMap
experiment1.put("experiment_name", "Experiment 1");
experiment1.put("experiment_id", "51353414351143");
experiment1.put("variation_name", "Variation 2");
experiment1.put("variation_id", "4919491294129");

Analytics.with(context).track("Experiment Viewed", new Properties().putAll(experiment1));
```



