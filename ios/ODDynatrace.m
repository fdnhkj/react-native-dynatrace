//
//  ODDynatrace.m
//  ODDynatrace
//
//  Created by OLIVIER DEMOLLIENS on 01/11/2017.
//  Copyright © 2017 DEMOLLIENS. All rights reserved.
//

#import "ODDynatrace.h"
#import "DynatraceUEM.h"

@implementation ODDynatrace

- (dispatch_queue_t)methodQueue
{
    return dispatch_get_main_queue();
}

RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(startup:(NONNULL NSString *)appId
                  serverURL:(NONNULL NSString *)serverURL)
{
    CPWR_StatusCode statusCode = [DynatraceUEM startupWithApplicationName:appId
                                                                serverURL:serverURL
                                                             allowAnyCert:NO
                                                          certificatePath:nil
                                  ];
}

RCT_EXPORT_METHOD(shutdown)
{
    [DynatraceUEM shutdown];
}

RCT_EXPORT_METHOD(enterAction:(NONNULL NSString *)actionName)
{
    UEMAction *action = [UEMAction enterActionWithName: actionName];
    //temporary leaving action directly
    [action leaveAction];
}

@end

