
#import "PXSDynatrace.h"
#import "DynatraceUEM.h"

#import <React/RCTLog.h>

@implementation PXSDynatrace

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
    RCTLogInfo(@"Dynatrace startup status code = %d", statusCode);
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
