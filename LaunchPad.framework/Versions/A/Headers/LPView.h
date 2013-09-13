//
//  LPView.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface LPView : UIView <LPElementProtocol>

- (id)initWithLPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame LPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)viewWithLPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)viewWithFrame:(CGRect)frame LPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
