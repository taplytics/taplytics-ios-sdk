//
//  TLElementProtocol.h
//  Taplytics
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#define TLKEY_isSettingUP @"TL_isSettingUP"
#define TLKEY_isSettingProperties @"TL_isSettingProperties"
#define TLKEY_elementKey @"TL_elementKey"
#define TLKEY_styleKey @"TL_styleKey"
#define TLKEY_stateName @"TL_stateName"
#define TLKEY_viewKey @"TL_viewKey"

@protocol TLElementProtocol <NSObject>

@required

@property (nonatomic, strong) NSString* elementKey;
@property (nonatomic, strong) NSString* styleKey;
@property (nonatomic, strong) NSString* stateName;
@property (nonatomic, strong) NSMutableDictionary* origProperties;
@property (nonatomic) BOOL isSettingProperties;

- (void)setupWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (void)setElementState:(NSString*)stateName;

- (id)getOrigPropertyValueForKey:(NSString*)key;

- (void)setOrigPropertyValue:(id)value forKey:(NSString*)key;

@optional

- (BOOL)setElementPropertyforKey:(NSString*)key value:(id)value;

@end
