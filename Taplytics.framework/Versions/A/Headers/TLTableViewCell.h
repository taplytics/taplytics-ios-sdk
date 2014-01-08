//
//  TLTableViewCell.h
//  Taplytics
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TLElementProtocol.h"
#import "TLLabel.h"

@interface TLTableViewCell : UITableViewCell <TLElementProtocol>

- (id)initWithElementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithFrame:(CGRect)frame elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
         elementKey:(NSString*)elementKey styleKey:(NSString*)styleKey;

@end
