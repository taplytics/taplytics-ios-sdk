//
//  UILabel+TLLabel.h
//  Taplytics
//
//  Copyright (c) 2014 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TLElementProtocol.h"

@interface UILabel (TLLabel) <TLElementProtocol>

@property (nonatomic, strong) NSString* elementKey;
@property (nonatomic, strong) NSString* styleKey;
@property (nonatomic, strong) NSString* stateName;
@property (nonatomic) BOOL isSettingProperties;

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)labelWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)labelWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
