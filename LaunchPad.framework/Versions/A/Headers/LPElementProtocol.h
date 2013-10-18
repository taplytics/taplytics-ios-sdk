//
//  LPElementProtocol.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#define LPKEY_isSettingUP           @"LP_isSettingUP"
#define LPKEY_isSettingProperties   @"LP_isSettingProperties"
#define LPKEY_elementKey            @"LP_elementKey"
#define LPKEY_styleKey              @"LP_styleKey"
#define LPKEY_stateName             @"LP_stateName"

@protocol LPElementProtocol <NSObject>

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
