//
//  UIDatePicker+TLDatePicker.h
//  Taplytics
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TLElementProtocol.h"

@interface UIDatePicker (TLDatePicker) <TLElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
