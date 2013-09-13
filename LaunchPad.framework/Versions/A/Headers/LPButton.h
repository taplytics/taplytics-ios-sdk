//
//  LPButton.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface LPButton : UIButton <LPElementProtocol>

- (id)initWithLPElementKey:(NSString*)key styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame LPElementKey:(NSString*)key styleKey:(NSString*)styleKey;

+ (instancetype)buttonWithType:(UIButtonType)buttonType LPElementKey:(NSString*)key stlyeKey:(NSString*)styleKey;

@end
