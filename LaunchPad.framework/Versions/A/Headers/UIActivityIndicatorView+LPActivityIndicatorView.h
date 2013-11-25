//
//  UIActivityIndicatorView+LPActivityIndicatorView.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface UIActivityIndicatorView (LPActivityIndicatorView) <LPElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithActivityIndicatorStyle:(UIActivityIndicatorViewStyle)style elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
