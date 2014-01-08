//
//  TLTextField.h
//  Taplytics
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TLElementProtocol.h"

@interface TLTextField : UITextField <TLElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)textFieldWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)textFieldWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
