//
//  TLButton.h
//  Taplytics
//
//  Copyright (c) 2014 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TLElementProtocol.h"

@interface TLButton : UIButton <TLElementProtocol>

- (id)initWithElementKey:(NSString*)key styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)key styleKey:(NSString*)styleKey;

+ (instancetype)buttonWithType:(UIButtonType)buttonType elementKey:(NSString*)key stlyeKey:(NSString*)styleKey;

@end
