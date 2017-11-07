//
//  ODDynatrace.h
//  ODDynatrace
//
//  Created by OLIVIER DEMOLLIENS on 01/11/2017.
//  Copyright © 2017 DEMOLLIENS. All rights reserved.
//

#if __has_include(<React/RCTBridgeModule.h>)
#import <React/RCTBridgeModule.h>
#elif __has_include("RCTBridgeModule.h")
#import "RCTBridgeModule.h"
#else
#import "React/RCTBridgeModule.h"   // Required when used as a Pod in a Swift project
#endif

@interface ODDynatrace : NSObject <RCTBridgeModule>

@end
  
