//
//  UITableView+LPTableView.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface UITableView (LPTableView) <LPElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame style:(UITableViewStyle)style
         elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
