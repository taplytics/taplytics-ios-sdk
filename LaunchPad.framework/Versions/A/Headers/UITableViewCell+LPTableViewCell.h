//
//  UITableViewCell+LPTableViewCell.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface UITableViewCell (LPTableViewCell) <LPElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
         elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
