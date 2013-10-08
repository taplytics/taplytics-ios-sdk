//
//  LPProperties.h
//  LaunchPad
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPElementProtocol.h"

@interface LPProperties : NSObject

@property (nonatomic, readonly, strong) NSString* appName;
@property (nonatomic, readonly, strong) NSString* appID;
@property (nonatomic, readonly, strong) NSNumber* version;
@property (nonatomic, readonly, strong) NSDictionary* project;
@property (nonatomic, readonly, strong) NSDictionary* views;
@property (nonatomic, readonly, strong) NSDictionary* elements;
@property (nonatomic, readonly, strong) NSDictionary* styles;
@property (nonatomic, readonly, strong) NSDictionary* theme;
@property (nonatomic, readonly, strong) NSDictionary* propertyTypes;
@property (nonatomic, readonly, strong) NSDictionary* releaseInfo;
@property (nonatomic, readonly, strong) NSString* themeName;

- (id)initWithJSONDic:(NSDictionary*)dic;

- (void)updateDataWithDictionary:(NSDictionary*)dic;

- (NSDictionary *)getPropertiesForElement:(id<LPElementProtocol>)element;

- (NSDictionary *)getPropertiesForElementKey:(NSString *)key styleKey:(NSString*)style state:(NSString *)stateName;

- (NSString*)styleKeyForElementKey:(NSString*)elementKey;

- (NSString*)propertyTypeForPropertyName:(NSString*)name;

- (NSDictionary*)getAnalyticsPropertiesForElement:(id<LPElementProtocol>)element analyticsSource:(NSString*)source;

@end
