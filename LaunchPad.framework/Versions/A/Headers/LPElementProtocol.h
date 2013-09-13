//
//  LPElementProtocol.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

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
