//
//  LPLabel.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface LPLabel : UILabel <LPElementProtocol>

- (id)initWithLPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame LPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)labelWithLPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)labelWithFrame:(CGRect)frame LPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
