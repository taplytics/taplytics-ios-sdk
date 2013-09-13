//
//  LPImageView.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface LPImageView : UIImageView <LPElementProtocol>

- (id)initWithLPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame LPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithImage:(UIImage *)image LPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithImageForLPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithImage:(UIImage *)image highlightedImage:(UIImage *)highlightedImage
                 LPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)imageViewWithLPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)imageViewWithImage:(UIImage*)image LPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

+ (instancetype)imageWithImage:(UIImage *)image highlightedImage:(UIImage *)highlightedImage
                  LPElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
