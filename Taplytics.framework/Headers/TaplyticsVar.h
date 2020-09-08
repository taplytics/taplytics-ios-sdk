//
//  TaplyticsVar.h
//  Taplytics
//
//  Copyright © 2017 Taplytics. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void(^TLVarBlock)(NSObject* _Nonnull value);

/**
 Taplytics Variables are dynamic variables that can be used to change content or functionality of your app dynamically
 from the Taplytics website. Variables are re-useable between experiments and are defined by their name and a
 default value that is used when there is no internet connection or when variables are not attached to any experiments.
 
 Variable are easiest to use and test if they are implemented asynchronously. Asynchronous variables should always implement the update code block,
 the value of the variable can be change asynchronously once experiment properties are loaded from Taplytics Servers, 
 but will always be called before your app's launch image is hidden.
 
 Variables accept a JSON serializable NSDictionary, NSString, NSNumber, and Booleans casted into NSNumbers as values.
 
 For example using a NSNumber:
 
 // Using the variable in your code:
 [TaplyticsVar taplyticsVarWithName:@"numVar" defaultValue:@(1) updatedBlock:^(NSObject *value) {
     NSNumber* num = (NSNumber*)value;
 }];

 Example of Using a Boolean casted as NSNumber:
 
 __weak id weakSelf = self;
 [TaplyticsVar taplyticsVarWithName:@"useNewCheckout" defaultValue:@(NO) updatedBlock:^(NSObject* value) {
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
@property (readonly, strong) NSObject* _Nonnull value;

/**
 isSynchronous defines if the variable is a synchronous variable or async variable
 */
@property (readonly) BOOL isSynchronous;

- (nonnull instancetype)init NS_SWIFT_UNAVAILABLE("Remove exposure of init");

/**
 Get instance of Taplytics Variable with name and default value synchronously.

 Threading: This method is thread-safe.

 @param name the name of the Taplytics Variable
 @param defaultValue the defualt value to be used and when not modified by a Taplytics Experiment or when experiments are not loaded before use
 */
 + (nonnull instancetype)taplyticsSyncVarWithName:(nonnull NSString *)name
                                     defaultValue:(nonnull NSObject*)defaultValue
                                     NS_SWIFT_NAME(sync(name:defaultValue:));

/**
 Get instance of Taplytics Variable with name and default value. Updates to its value are notified using the updatedBlock.
 
 Threading: This method is thread-safe.

 @param name the name of the Taplytics Variable
 @param defaultValue the default value to be used when not modified by a Taplytics Experiment. 
 Can be NSString, NSNumber, or a Boolean casted as NSNumber
 @param updatedBlock the update code block called when the Taplytics Variable's value is updated.
 */

+ (nonnull instancetype)taplyticsVarWithName:(nonnull NSString *)name
                                defaultValue:(nonnull NSObject*)defaultValue
                                updatedBlock:(nullable TLVarBlock)updatedBlock
                                NS_SWIFT_NAME(async(name:defaultValue:updatedBlock:));

/**
 Created sync method to support deprecated Swift 3 variable formatting, calls [self taplyticsSyncVarWithName:defaultValue:] internally.
 */
+ (nonnull instancetype)syncVarWithName:(nonnull NSString *)name
                           defaultValue:(nonnull NSObject *) defaultValue
                            NS_SWIFT_NAME(taplyticsSyncVar(withName:defaultValue:)) __deprecated;
/**
 Created async method to support deprecated Swift 3 variable formatting, calls [self taplyticsVarWithName:defaultValue:updatedBlock:] internally.
 */
+ (nonnull instancetype)asyncVarWithName:(nonnull NSString *)name
                            defaultValue:(nonnull NSObject *)defaultValue
                            updatedBlock:(nullable TLVarBlock)updatedBlock
                            NS_SWIFT_NAME(init(name:defaultValue:updatedBlock:)) __deprecated;

@end

