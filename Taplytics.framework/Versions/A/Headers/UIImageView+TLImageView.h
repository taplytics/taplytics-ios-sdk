//
//  UIImageView+TLImageView.h
//  Taplytics
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TLElementProtocol.h"

@interface UIImageView (TLImageView) <TLElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithImage:(UIImage *)image elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithImageForElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithImage:(UIImage *)image highlightedImage:(UIImage *)highlightedImage
         elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)imageViewWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)imageViewWithImage:(UIImage*)image elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)imageWithImage:(UIImage *)image highlightedImage:(UIImage *)highlightedImage
                    elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
