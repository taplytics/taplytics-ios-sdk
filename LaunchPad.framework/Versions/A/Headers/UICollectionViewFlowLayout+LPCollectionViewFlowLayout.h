//
//  UICollectionViewFlowLayout+LPCollectionViewFlowLayout.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface UICollectionViewFlowLayout (LPCollectionViewFlowLayout) <LPElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
