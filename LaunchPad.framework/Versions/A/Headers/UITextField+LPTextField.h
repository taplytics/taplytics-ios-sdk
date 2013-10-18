//
//  UITextField+LPTextField.h
//  LaunchPad
//
//  Created by Jonathan Norris on 2013-10-17.
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface UITextField (LPTextField) <LPElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)textFieldWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)textFieldWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
