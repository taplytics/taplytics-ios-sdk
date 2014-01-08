//
//  TLProperties.h
//  Taplytics
//
//  Copyright (c) 2013 Syrp Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TLElementProtocol.h"

@interface TLProperties : NSObject

@property (nonatomic, readonly, strong) NSString* appName;
@property (nonatomic, readonly, strong) NSString* appID;
@property (nonatomic, readonly, strong) NSString* sessionID;
@property (nonatomic, readonly, strong) NSNumber* version;
@property (nonatomic, readonly, strong) NSDictionary* project;
@property (nonatomic, readonly, strong) NSDictionary* views;
@property (nonatomic, readonly, strong) NSDictionary* elements;
@property (nonatomic, readonly, strong) NSDictionary* styles;
@property (nonatomic, readonly, strong) NSDictionary* theme;
@property (nonatomic, readonly, strong) NSDictionary* propertyTypes;
@property (nonatomic, readonly, strong) NSDictionary* releaseInfo;
@property (nonatomic, readonly, strong) NSDictionary* analyticsSettings;
@property (nonatomic, readonly, strong) NSDictionary* images;
@property (nonatomic, readonly, strong) NSString* themeName;

- (id)initWithJSONDic:(NSDictionary*)dic;

- (void)updateDataWithDictionary:(NSDictionary*)dic;

- (NSDictionary *)getPropertiesForElement:(id<TLElementProtocol>)element;

- (NSDictionary *)getPropertiesForElementKey:(NSString *)key styleKey:(NSString*)style state:(NSString *)stateName;

- (NSString*)styleKeyForElementKey:(NSString*)elementKey;

- (NSString*)propertyTypeForPropertyName:(NSString*)name;

- (NSDictionary*)getAnalyticsPropertiesForElement:(id<TLElementProtocol>)element analyticsSource:(NSString*)source;

@end
