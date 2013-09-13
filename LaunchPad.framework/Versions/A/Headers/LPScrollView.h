//
//  LPScrollView.h
//  LaunchPad
//
//  Created by Aaron Glazer on 2013-08-29.
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface LPScrollView : UIScrollView <LPElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)viewWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)viewWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
