//
//  TaplyticsVar.h
//  Taplytics
//
//  Copyright (c) 2015 Taplytics Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void(^TLVarBlock)(NSObject* value);

/**
 Taplytics Variables are dynamic variables that can be used to change content or functionality of your app dynamically
 from the Taplytics website. Variables are re-useable between experiments and are defined by their name and a
 default value that is used when there is no internet connection or when variables are not attached to any experiments.
 
 Variable are easiest to use and test if they are implemented asynchronously. Asynchronous variables should always implement the update code block,
 the value of the variable can be change asynchronously once experiment properties are loaded from Taplytics Servers, 
 but will always be called before your app's launch image is hidden.
 
 Variables accept NSString, NSNumber, and Booleans casted into NSNumbers as values.
 
 For example using a NSString to set label text:
 
 __weak id weakSelf = self;
 [TaplyticsVar taplyticsVarWithName:@"stringVar" defaultValue:@"Hello World" updatedBlock:^(NSObject* value) {
    // updatedBlock will be called when the value is updated.
    if (value && weakSelf)
        weakSelf.label.text = (NSString*)value;
 }];
 
 Example of Using a NSNumber: 
 
 __weak id weakSelf = self;
 [TaplyticsVar taplyticsVarWithName:@"numberOfCells" defaultValue:@10 updatedBlock:^(NSObject* value) {
    if (value && weakSelf)
        [weakSelf setNumberOfCells:value];
 }];

 Example of Using a Boolean casted as NSNumber:
 
 __weak id weakSelf = self;
 [TaplyticsVar taplyticsVarWithName:@"useNewCheckout" defaultValue:@(NO) updatedBlock:^(NSObject* value) {
    if (value && weakSelf)
        [weakSelf useNewCheckout:[(NSNumber*)value boolValue]];
 }];
 
 You can also use synchronous variables using the following, however you may need to implement callbacks to be able to test synchronous variables.
 For more info on testing synchronous variables, visit: https://github.com/taplytics/taplytics-ios-sdk/blob/master/EXPERIMENTS.md#dynamic-variables--code-blocks
 
 TaplyticsVar* syncVar = [TaplyticsVar taplyticsSyncVarWithName:@"syncVar" defaultValue:@(1)];
 NSNumber* value = (NSNumber*)syncVar.value;
 
 */

@interface TaplyticsVar : NSObject

/**
 value the value of the Taplytics Variable
 */
@property (nonatomic, readonly, strong) NSObject* value;

/**
 isSynchronous defines if the variable is a synchronous variable or async variable
 */
@property (nonatomic, readonly) BOOL isSynchronous;

/**
 Get instance of Taplytics Variable with name and defualt value synchronously. 
 
 @param name the name of the Taplytics Variable
 @param defaultValue the defualt value to be used and when not modified by a Taplytics Experiment or when experiments are not loaded before use
 */
 + (instancetype)taplyticsSyncVarWithName:(NSString *)name defaultValue:(NSObject*)defaultValue;

/**
 Get instance of Taplytics Variable with name and default value. Updates to its value are notified using the updatedBlock.
 
 @param name the name of the Taplytics Variable
 @param defaultValue the default value to be used when not modified by a Taplytics Experiment. 
 Can be NSString, NSNumber, or a Boolean casted as NSNumber
 @param codeBlock the update code block called when the Taplytics Variable's value is updated.
 */

+ (instancetype)taplyticsVarWithName:(NSString *)name defaultValue:(NSObject*)defaultValue updatedBlock:(TLVarBlock)codeBlock;

@end

