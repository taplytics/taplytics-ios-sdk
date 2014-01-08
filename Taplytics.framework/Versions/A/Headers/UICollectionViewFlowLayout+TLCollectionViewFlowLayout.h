//
//  UICollectionViewFlowLayout+TLCollectionViewFlowLayout.h
//  Taplytics
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TLElementProtocol.h"

@interface UICollectionViewFlowLayout (TLCollectionViewFlowLayout) <TLElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
