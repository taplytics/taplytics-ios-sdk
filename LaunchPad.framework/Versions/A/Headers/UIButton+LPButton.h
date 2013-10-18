//
//  UIButton+LPButton.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface UIButton (LPButton) <LPElementProtocol>

- (id)initWithElementKey:(NSString*)key styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)key styleKey:(NSString*)styleKey;

+ (instancetype)buttonWithType:(UIButtonType)buttonType elementKey:(NSString*)key stlyeKey:(NSString*)styleKey;

@end
