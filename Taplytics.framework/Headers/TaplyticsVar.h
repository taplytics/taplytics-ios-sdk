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
 
 Variables should always implement the update code block, the value of the variable can be change asynchronously
 once experiment properties are loaded from Taplytics Servers, but always called before your app's launch image is hidden.
 
 Variables accept NSString, NSNumber, and Booleans casted into NSNumbers as values.
 
 For example using a NSString to set label text:
 
 TaplyticsVar *var = [TaplyticsVar taplyticsVarWithName:@"stringVar" defaultValue:@"Hello World" updatedBlock:^(NSObject* value) {
    // updatedBlock will be called when the value is updated.
    if (value)
        _label.text = (NSString*)value;
 }];
 
 // variables can also use the value property to access the value.
 _label.text = (NSString*)var.value;
 
 Example of Using a NSNumber: 
 
 [TaplyticsVar taplyticsVarWithName:@"numberOfCells" defaultValue:@10 updatedBlock:^(NSObject* value) {
    if (value)
        [weakSelf setNumberOfCells:value];
 }];

 Example of Using a Boolean casted as NSNumber:
 
 [TaplyticsVar taplyticsVarWithName:@"useNewCheckout" defaultValue:@(NO) updatedBlock:^(NSObject* value) {
    if (value)
        [weakSelf useNewCheckout:[(NSNumber*)value boolValue]];
 }];
 
 */

@interface TaplyticsVar : NSObject

@property (nonatomic, readonly, strong) NSObject* value;

/**
 Get instance of Taplytics Variable with name and default value. Updates to its value are notified using the updatedBlock.
 
 @param name the name of the Taplytics Variable
 @param defaultValue the default value to be used when not modified by a Taplytics Experiment. 
 Can be NSString, NSNumber, or a Boolean casted as NSNumber
 @param codeBlock the update code block called when the Taplytics Variable's value is updated.
 */

+ (instancetype)taplyticsVarWithName:(NSString *)name defaultValue:(NSObject*)defaultValue updatedBlock:(TLVarBlock)codeBlock;

@end

