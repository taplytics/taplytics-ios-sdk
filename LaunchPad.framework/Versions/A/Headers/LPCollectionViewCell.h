//
//  LPCollectionViewCell.h
//  LaunchPad
//
//  Created by Jonathan Norris on 2013-10-15.
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"
#import "LPLabel.h"

@interface LPCollectionViewCell : UICollectionViewCell <LPElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
