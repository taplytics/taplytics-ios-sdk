//
//  TLElementProtocol.h
//  Taplytics
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NSString* const TLKEY_isSettingUP = @"TL_isSettingUP";
NSString* const TLKEY_isSettingProperties = @"TL_isSettingProperties";
NSString* const TLKEY_elementKey = @"TL_elementKey";
NSString* const TLKEY_styleKey = @"TL_styleKey";
NSString* const TLKEY_stateName = @"TL_stateName";
NSString* const TLKEY_viewKey = @"TL_viewKey";

@protocol TLElementProtocol <NSObject>

@required

@property (nonatomic, strong) NSString* elementKey;
@property (nonatomic, strong) NSString* styleKey;
@property (nonatomic, strong) NSString* stateName;
@property (nonatomic) BOOL isSettingProperties;

- (void)setupWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (void)setElementState:(NSString*)stateName;

@optional

- (BOOL)setElementPropertyforKey:(NSString*)key value:(id)value;

@end
