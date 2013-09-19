//
//  LPProperties.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface LPProperties : NSObject

@property (nonatomic, strong) NSString* appName;
@property (nonatomic, strong) NSString* appID;
@property (nonatomic, strong) NSNumber* version;
@property (nonatomic, strong) NSDictionary* views;
@property (nonatomic, strong) NSDictionary* elements;
@property (nonatomic, strong) NSDictionary* styles;
@property (nonatomic, strong) NSDictionary* theme;
@property (nonatomic, strong) NSDictionary* propertyTypes;
@property (nonatomic, strong) NSString* themeName;

- (id)initWithJSONDic:(NSDictionary*)dic;

- (void)updateDataWithDictionary:(NSDictionary*)dic;

- (NSDictionary *)getPropertiesForElement:(id<LPElementProtocol>)element;

- (NSDictionary*)getPropertiesForElementKey:(NSString*)key;

- (NSString*)styleKeyForElementKey:(NSString*)elementKey;

- (NSString*)propertyTypeForPropertyName:(NSString*)name;

@end
