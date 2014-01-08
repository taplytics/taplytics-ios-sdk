//
//  UIView+TLView.h
//  Taplytics
//
//  Created by Jonathan Norris on 2013-10-17.
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TLElementProtocol.h"

@interface UIView (TLView) <TLElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)viewWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)viewWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
