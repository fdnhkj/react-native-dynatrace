// DynatraceUEM.h
// Version: 6.3.16.1014
//
// These materials contain confidential information and
// trade secrets of Compuware Corporation. You shall
// maintain the materials as confidential and shall not
// disclose its contents to any third party except as may
// be required by law or regulation. Use, disclosure,
// or reproduction is prohibited without the prior express
// written permission of Compuware Corporation.
//
// All Compuware products listed within the materials are
// trademarks of Compuware Corporation. All other company
// or product names are trademarks of their respective owners.
//
// Copyright 2011-2015 Compuware Corporation

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

/*!
 @file DynatraceUEM.h

 @brief This is the file developers include in their projects to use the DynatraceUEM ADK.

 This file provides the declarations of the DynatraceUEM and UEMAction classes and should
 be included in any iOS source file that uses the DynatraceUEM ADK.
 */

/*!
 @brief Defines the possible set of return codes for DynatraceUEM ADK methods
 */
typedef NS_ENUM(int, CPWR_StatusCode) {
    //! ADK is not enabled or can't capture data.
    CPWR_UemOff = 1,

    //! ADK is enabled.
    CPWR_UemOn = 2,

    //! PL Crash Reporter framework is unavailable to ADK.
    CPWR_CrashReportingUnavailable = 4,

    //! PL Crash Reporter framework is available to ADK.
    CPWR_CrashReportingAvailable = 5,

    //! ADK is not initialized.
    CPWR_Error_NotInitialized = -1,

    //! Parameter value specified is outside of permitted range
    CPWR_Error_InvalidRange = -2,

    //! An internal error occured
    CPWR_Error_InternalError = -3,

    //! A Corresponding enterAction event was not found for the current leaveAction
    CPWR_Error_ActionNotFound = -4,

    //! A null or 0 length serverURL, applicationName, actionName, or eventName are used
    CPWR_Error_InvalidParameter = -5,

    //! The action has already been ended via the leaveAction method
    CPWR_Error_ActionEnded = -6,

    //! Returned if the DT server has turned error reporting off
    CPWR_ReportErrorOff = -8,

    //! Returned if the actionName, eventName exceeds maximum length
    CPWR_TruncatedEventName = -9,

    //! Crash Report was invalid.
    CPWR_CrashReportInvalid = -10,
};

#if __has_feature(nullability)
#define NULLABLE nullable
#define NONNULL nonnull
#else
#define NULLABLE
#define NONNULL
#endif

/*!
 @brief Encapsulates a timed mobile action.

 It creates or extends a mobile action PurePath in dynaTrace.  It provides methods to report values,
 events, and errors against actions.
 */
@interface UEMAction : NSObject

/*!
 @brief Starts a top level action.

 The top level action results in a new mobile action PurePath in dynaTrace. An action allows you
 to time an interval in your code.  Call enterActionWithName: at the point you want to start timing.
 Call the leaveAction instance method on the returned object at the point you want to stop timing.

 @param actionName Name of action

 @return Returns the new action or nil if an error occurs.
 */
+ (NULLABLE UEMAction *)enterActionWithName:(NONNULL NSString *)actionName;

/*!
 @brief Starts a child action.

 The action adds a node to an existing mobile action PurePath in dynaTrace. An action allows you
 to time an interval in your code.  Call enterActionWithName:parentAction: at the point you want to
 start timing.  Call the leaveAction instance method on the returned object at the point you want
 to stop timing.

 @param actionName Name of action

 @param parentAction The parent action for this action.

 @return Returns the new action or nil if an error occurs.
 */
+ (NULLABLE UEMAction *)enterActionWithName:(NONNULL NSString *)actionName
                               parentAction:(NULLABLE UEMAction *)parentAction;

/*!
 @brief Ends an action and computes its interval.

 All reported events, values, and tagged web requests between start and end of an action are
 nested in the mobile action PurePath. If this action has any child actions, they are ended
 first. Call this method at the end of the code that you wish to time. The number of milliseconds
 since the action began is stored as the interval.

 In non-ARC code the UEMAction must be released after calling this method.

 @return Returns a CPWR_StatusCode indicating success (CPWR_CaptureOn) or failure
 */
- (CPWR_StatusCode)leaveAction;

/*!
 @brief Sends an event to dynaTrace.

 The event becomes a node of the mobile action PurePath.

 @param eventName Name of event

 @return Returns a CPWR_StatusCode
 */
- (CPWR_StatusCode)reportEventWithName:(NONNULL NSString *)eventName;

/*!
 @brief Sends a key/value pair to dynaTrace.

 The value becomes a node of the mobile action PurePath. The value can be processed by a measure and
 thus be charted.

 @param valueName Name of value

 @param intValue An integer value associated with the value name

 @return Returns a CPWR_StatusCode
 */
- (CPWR_StatusCode)reportValueWithName:(NONNULL NSString *)valueName intValue:(int)intValue;

/*!
 @brief Sends a key/value pair to dynaTrace.

 The value becomes a node of the mobile action PurePath. The value can be processed by a measure and
 thus be charted.

 @param valueName Name of value

 @param doubleValue A double value associated with the value name

 @return Returns a CPWR_StatusCode
 */
- (CPWR_StatusCode)reportValueWithName:(NONNULL NSString *)valueName doubleValue:(double)doubleValue;

/*!
 @brief Sends a key/value pair to dynaTrace.

 The value becomes a node of the mobile action PurePath.

 @param valueName Name of value

 @param stringValue A string value associated with the value name

 @return Returns a CPWR_StatusCode
 */
- (CPWR_StatusCode)reportValueWithName:(NONNULL NSString *)valueName stringValue:(NONNULL NSString *)stringValue;

/*!
 @brief Sends an error value to dynaTrace.

 The error becomes a node of the mobile action PurePath.

 @param errorName Name of error

 @param errorValue An integer value associated with the error

 @return Returns a CPWR_StatusCode
 */
- (CPWR_StatusCode)reportErrorWithName:(NONNULL NSString *)errorName errorValue:(int)errorValue;

/*!
 @brief Sends an exception to dynaTrace.

 The exception becomes a node of the mobile action PurePath.  This can be used to report exceptions
 that are caught and handled.

 @param errorName Name of error

 @param exception An exception object that has been caught.  The description string of this
 object is sent to the server along with the call stack if one is present.

 @return Returns a CPWR_StatusCode
 */
- (CPWR_StatusCode)reportErrorWithName:(NONNULL NSString *)errorName exception:(NONNULL NSException *)exception;

/*!
 @brief Sends an error object to dynaTrace.

 The error becomes a node of the mobile action PurePath.

 @param errorName Name of error

 @param error An error object that has been caught.  The error information for this
 object is sent to the server.

 @return Returns a CPWR_StatusCode
 */
- (CPWR_StatusCode)reportErrorWithName:(NONNULL NSString *)errorName error:(NONNULL NSError *)error;

/*!
 @brief Sends an error value to dynaTrace.

 Because this is a class method, the error is not associated with an action.  It creates
 its own mobile-only PurePath.

 @param errorName Name of error

 @param errorValue An integer value associated with the error

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)reportErrorWithName:(NONNULL NSString *)errorName errorValue:(int)errorValue;

/*!
 @brief Sends an exception to dynaTrace.

 Because this is a class method, the exception is not associated with an action.  It creates
 its own mobile-only PurePath.

 @param errorName Name of error

 @param exception An exception object that has been caught.  The description string of this
 object is sent to the server along with the call stack if one is present.

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)reportErrorWithName:(NONNULL NSString *)errorName exception:(NONNULL NSException *)exception;

/*!
 @brief Sends an error object to dynaTrace.

 Because this is a class method, the error is not associated with an action.  It creates
 its own mobile-only PurePath.

 @param errorName Name of error

 @param error An error object that has been caught.  The error information for this
 object is sent to the server.

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)reportErrorWithName:(NONNULL NSString *)errorName error:(NONNULL NSError *)error;

/*!
 @brief Ends the visit for dynaTrace.

 The endVisit becomes a node of the mobile action PurePath.  This is
 used to end a visit within the context of an action.

 @return Returns a CPWR_StatusCode
 */
- (CPWR_StatusCode)endVisit;

/*!
 @brief Ends the visit for dynaTrace.

 Because this is a class method, the endVisit is not associated with an action.  It creates
 its own mobile-only PurePath.

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)endVisit;

@property (nonatomic, readonly, assign) int tagId;

@end

/*************************************************************************************************/

/*!
 @brief Provides the ability to manually tag and time web requests.

 The UEMWebRequestTiming class provides the ability to manually time web requests.
 */
@interface UEMWebRequestTiming : NSObject

/*!
 @deprecated
 @brief Creates a UEMWebRequestTiming object.

 This method is deprecated.  Please use getUEMWebRequestTiming:requestUrl: instead.

 This method creates an instance of the UEMWebRequestTiming object.

 @param requestTagString the value of the HTTP header that you must add to your web request. this
 is obtained from the DynatraceUEM getRequestTagValueForURL method.

 @return Returns the UEMWebRequestTiming object.
 */
+ (NULLABLE UEMWebRequestTiming *)getUEMWebRequestTiming:(NONNULL NSString *)requestTagString
    DEPRECATED_MSG_ATTRIBUTE("Please use getUEMWebRequestTiming:requestUrl:");

/*!
 @brief Creates a UEMWebRequestTiming object.

 This method creates an instance of the UEMWebRequestTiming object.

 @param requestTagString the value of the HTTP header that you must add to your web request. this
 is obtained from the DynatraceUEM getRequestTagValueForURL method.

 @param requestUrl the value of the URL for the web request

 @return Returns the UEMWebRequestTiming object.
 */
+ (NULLABLE UEMWebRequestTiming *)getUEMWebRequestTiming:(NONNULL NSString *)requestTagString
                                              requestUrl:(NULLABLE NSURL *)requestUrl;

/*!
 @brief Manaully start timing a web request.

 The DynatraceUEM ADK automatically times web requests made using NSURLRequest, NSURLConnection,
 NSURLProtocol, NSString, UIWebView, and ASIHTTPRequest.  If you use an alternate technology to make
 web requests and want to time them, use the getRequestTagHeader method, adding that information to
 your request, and then this method to start the timing.

 @return Returns a CPWR_StatusCode
 */
- (CPWR_StatusCode)startWebRequestTiming;

/*!
 @deprecated
 @brief Manually finish timing a web request.

 This method is deprecated.  Please use stopWebRequestTiming: for returning an NSError instead.

 The DynatraceUEM ADK automatically times web requests made using NSURLRequest, NSURLConnection,
 NSURLProtocol, NSString, UIWebView, and ASIHTTPRequest.  If you use an alternate technology to make
 web requests and want to time them, use the getRequestTagHeader method, adding that information to
 your request, and then this method to stop the timing and send the information to the mobile action
 PurePath.

 @return Returns a CPWR_StatusCode
 */
- (CPWR_StatusCode)stopWebRequestTiming
    DEPRECATED_MSG_ATTRIBUTE("Please use stopWebRequestTiming: to return error code instead");

/*!
 @brief Manually finish timing a web request.

 @param errorCode the response status code for a successful web request or the error code
 for a failed web request

 The DynatraceUEM ADK automatically times web requests made using NSURLRequest, NSURLConnection,
 NSURLProtocol, NSString, UIWebView, and ASIHTTPRequest.  If you use an alternate technology to make
 web requests and want to time them, use the getRequestTagHeader method, adding that information to
 your request, and then this method to stop the timing and send the information to the mobile action PurePath.

 @return Returns a CPWR_StatusCode
 */
- (CPWR_StatusCode)stopWebRequestTiming:(NULLABLE NSString *)errorCode;

@end

/*************************************************************************************************/

/*!
 @brief Provides for startup and shutdown of the DynatraceUEM ADK.

 The DynatraceUEM class provides the ability to startup, shutdown, and control other global
 attributes of the DynatraceUEM ADK.
 */
@interface DynatraceUEM : NSObject

/*!
 @brief Initializes the DynatraceUEM ADK.

 This must be invoked before any Events can be captured. Multiple calls to this method are
 ignored if the ADK is not shut down between them.

 This method will be called automatically if you specify the value cpwrUEM_startup.agentPath in
 your application's Info.plist file.  The parameter descriptions below specify the info.plist value
 to use to specify each parameter value when using auto-start.

 @param applicationName A user-defined name for the application. (Info.plist value
 cpwrUEM_startup.sApplId)

 @param serverURL The URL of the web server with an active dynaTrace UEM agent
 (eg: "http://myhost.mydomain.com:8080/agentLocation/").  The URL scheme dictates whether the ADK
 uses http or https. The URL must contain the agent location specified in the dynaTrace UEM settings
 for this application. (Info.plist value cpwrUEM_startup.agentPath)

 @param allowAnyCert Allow any certificate for https communication. This is only evaluated if
 the https transport mechanism is specified in the server name.  (Info.plist value
 cpwrUEM_startup.useAnyCert)

 @param pathToCertificateAsDER Path to a (self-signed) certificate in DER format or nil.  Adds a
 certificiate in DER format which is used as an additional anchor to validate https communication.
 This is needed if allowAnyCert is NO and a self-signed certificate is used on the server.  You can
 retrieve the path for a file in your application bundle using code like this:

 <code>
 NSString *pathToCertificateAsDER =
     [[NSBundle mainBundle] pathForResource:@"myAppCert" ofType:@"der"];
 </code>

 (Info.plist value cpwrUEM_startup.certPath)

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)startupWithApplicationName:(NONNULL NSString *)applicationName
                                    serverURL:(NONNULL NSString *)serverURL
                                 allowAnyCert:(BOOL)allowAnyCert
                              certificatePath:(NULLABLE NSString *)pathToCertificateAsDER;

/*!
 @brief Initializes the DynatraceUEM ADK.
 
 This must be invoked before any Events can be captured. Multiple calls to this method are
 ignored if the ADK is not shut down between them.
 
 This method will be called automatically if you specify the value cpwrUEM_startup.agentPath in
 your application's info.plist file.  The parameter descriptions below specify the info.plist value
 to use to specify each parameter value when using auto-start.
 
 @param applicationName A user-defined name for the application. (Info.plist value
 cpwrUEM_startup.sApplId)
 
 @param serverURL The URL of the web server with an active dynaTrace UEM agent
 (eg: "http://myhost.mydomain.com:8080/agentLocation/").  The URL scheme dictates whether the ADK
 uses http or https. The URL must contain the agent location specified in the dynaTrace UEM settings
 for this application. (Info.plist value cpwrUEM_startup.agentPath)
 
 @param authenticationClassDelegate The name of the class that implements a class method with the
 following selector:
 
<code>
 +(void)requestAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;
</code>
 
 Add &lt;DTXAuthenticationClassDelegate&gt; to your class interface.
 
 (Info.plist value DTXAuthenticationClassDelegate)
 
 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)startupWithApplicationName:(NONNULL NSString *)applicationName
                                    serverURL:(NONNULL NSString *)serverURL
                  authenticationClassDelegate:(NONNULL Class)authenticationClassDelegate;

/*!
 @brief Stops DynatraceUEM monitoring.

 Collected data will be flushed to the server.

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)shutdown;

/*!
 @brief Set the current GPS location of the user.

 The DynatraceUEM library does not automatically collect location information.  If the
 developer wants location information to be transmitted to dynaTrace, then this function should
 be used to provide it.

 @param gpsLocation CLLocation object with GPS coordinates aquired by customer application

 @return Returns a CPWR_StatusCode indicating current uem capture status (if the ADK is not
 capturing no GPS location is set)
 */
+ (CPWR_StatusCode)setGpsLocation:(NONNULL CLLocation *)gpsLocation;

/*!
 @brief Provides information regarding internal errors.

 Use this to obtain the error code associated with the most recent CPWR_Error_InternalError or
 enterActionWithName.

 @return Returns the error code or 0 if there is no error.
 */
+ (int)lastErrorCode;

/*!
 @brief Provides a string describing internal errors.

 Use this to obtain the error message associated with most recent CPWR_Error_InternalError.

 @return Returns the error message or nil if there is no error.
 */
+ (NULLABLE NSString *)lastErrorMsg;

/*!
 @brief Send all collected events immediately.

 To reduce network traffic/usage the collected events are usually sent in packages where the oldest
 event has an age of up to 9 minutes. Using this method you can force sending of all collected
 events regardless of their age.

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)flushEvents;

/*!
 @brief Enable dynaTrace crash reporting.

 The DynatraceUEM ADK can report on application crashes using the KSCrash framwork.  Call this
 method after startupWithApplicationName:serverURL:allowAnyCert:certificatePath: to enable
 crash reporting to the dynaTrace server.

 When using auto-start use the info.plist value cpwrUEM_crash.reporting to control whether this
 method is invoked automatically.  You must disable the automatic invocation of this method if
 you wish to use one of the following methods to enable third party crash reporting.

 @param sendCrashReport YES to send complete crash report to dynaTrace premium mode server.  NO to
 send only minimal information.

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)enableCrashReportingWithReport:(BOOL)sendCrashReport;

/*!
 @deprecated
 @brief Enable dynaTrace and HockeyApp crash reporting.

 This method is deprecated.  New applications should use the newer version that includes
 the hockeyUserName parameter.

 The DynatraceUEM ADK can report on application crashes using the KSCrash framwork.  Call this
 method after startupWithApplicationName:serverURL:allowAnyCert:certificatePath: to enable
 crash reporting to the dynaTrace server as well as HockeyApp.  Crash information
 will be sent to both systems.

 When using auto-start you must set the cpwrUEM_crash.reporting info.plist value to NO when using
 this method to initiate crash reporting.

 @param sendCrashReport YES to send complete crash report to dynaTrace premium mode server.  NO to
 send only minimal information.

 @param appIdentifier The application identifier assigned by HockeyApp to your application.

 @param waitUntilReachable YES to wait until HockeyApp is reachable before sending.  NO to attempt
 sending whether available or not and simply fails if not available.

 @param userId Optional HockeyApp user ID.  Set to nil if not needed.

 @param contactEmail Optional HockeyApp user contact email address.  Set to nil if not needed.

 @param description Optional description to include with the crash report for HockeyApp.

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)enableCrashReportingWithReport:(BOOL)sendCrashReport
                              hockeyAppIdentifier:(NONNULL NSString *)appIdentifier
                         hockeyWaitUntilReachable:(BOOL)waitUntilReachable
                                     hockeyUserId:(NULLABLE NSString *)userId
                               hockeyContactEmail:(NULLABLE NSString *)contactEmail
                           hockeyCrashDescription:(NULLABLE NSString *)description
    DEPRECATED_MSG_ATTRIBUTE("The new version of this method includes the hockeyUserName parameter "
                             "to specify the HockeyApp user name");

/*!
 @brief Enable dynaTrace and HockeyApp crash reporting.

 The DynatraceUEM ADK can report on application crashes using the KSCrash framwork.  Call this
 method after startupWithApplicationName:serverURL:allowAnyCert:certificatePath: to enable
 crash reporting to the dynaTrace server as well as HockeyApp.  Crash information
 will be sent to both systems.

 When using auto-start you must set the cpwrUEM_crash.reporting info.plist value to NO when using
 this method to initiate crash reporting.

 @param sendCrashReport YES to send complete crash report to dynaTrace premium mode server.  NO to
 send only minimal information.

 @param appIdentifier The application identifier assigned by HockeyApp to your application.

 @param waitUntilReachable YES to wait until HockeyApp is reachable before sending.  NO to attempt
 sending whether available or not and simply fails if not available.

 @param userId Optional HockeyApp user ID.  Set to nil if not needed.

 @param userName Optional HockeyApp user name.  Set to nil if not needed.

 @param contactEmail Optional HockeyApp user contact email address.  Set to nil if not needed.

 @param description Optional description to include with the crash report for HockeyApp.

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)enableCrashReportingWithReport:(BOOL)sendCrashReport
                              hockeyAppIdentifier:(NONNULL NSString *)appIdentifier
                         hockeyWaitUntilReachable:(BOOL)waitUntilReachable
                                     hockeyUserId:(NULLABLE NSString *)userId
                                   hockeyUserName:(NULLABLE NSString *)userName
                               hockeyContactEmail:(NULLABLE NSString *)contactEmail
                           hockeyCrashDescription:(NULLABLE NSString *)description;

/*!
 @deprecated
 @brief Enable dynaTrace and Quincy crash reporting.

 This method is deprecated.  New applications should use the newer version that includes
 the quincyUserName parameter.

 The DynatraceUEM ADK can report on application crashes using the KSCrash framwork.  Call this
 method after startupWithApplicationName:serverURL:allowAnyCert:certificatePath: to enable
 crash reporting to the dynaTrace server as well as a Quincy server.  Crash
 information will be sent to both systems.

 When using auto-start you must set the cpwrUEM_crash.reporting info.plist value to NO when using
 this method to initiate crash reporting.

 @param sendCrashReport YES to send complete crash report to dynaTrace premium mode server.  NO to
 send only minimal information.

 @param serverURL The URL of your Quincy server.

 @param waitUntilReachable YES to wait until Quincy server is reachable before sending.  NO to
 attempt sending whether available or not and simply fails if not available.

 @param userId Optional Quincy user ID.  Set to nil if not needed.

 @param contactEmail Optional Quincy user contact email address.  Set to nil if not needed.

 @param description Optional description to include with the crash report for Quincy.

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)enableCrashReportingWithReport:(BOOL)sendCrashReport
                                        quincyURL:(NONNULL NSString *)serverURL
                         quincyWaitUntilReachable:(BOOL)waitUntilReachable
                                     quincyUserId:(NULLABLE NSString *)userId
                               quincyContactEmail:(NULLABLE NSString *)contactEmail
                           quincyCrashDescription:(NULLABLE NSString *)description
    DEPRECATED_MSG_ATTRIBUTE("The new version of this method includes the quincyUserName parameter "
                             "to specify the Quincy user name");

/*!
 @brief Enable dynaTrace and Quincy crash reporting.

 The DynatraceUEM ADK can report on application crashes using the KSCrash framwork.  Call this
 method after startupWithApplicationName:serverURL:allowAnyCert:certificatePath: to enable
 crash reporting to the dynaTrace server as well as a Quincy server.  Crash
 information will be sent to both systems.

 When using auto-start you must set the cpwrUEM_crash.reporting info.plist value to NO when using
 this method to initiate crash reporting.

 @param sendCrashReport YES to send complete crash report to dynaTrace premium mode server.  NO to
 send only minimal information.

 @param serverURL The URL of your Quincy server.

 @param waitUntilReachable YES to wait until Quincy server is reachable before sending.  NO to
 attempt sending whether available or not and simply fails if not available.

 @param userId Optional Quincy user ID.  Set to nil if not needed.

 @param userName Optional Quincy user name.  Set to nil if not needed.

 @param contactEmail Optional Quincy user contact email address.  Set to nil if not needed.

 @param description Optional description to include with the crash report for Quincy.

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)enableCrashReportingWithReport:(BOOL)sendCrashReport
                                        quincyURL:(NONNULL NSString *)serverURL
                         quincyWaitUntilReachable:(BOOL)waitUntilReachable
                                     quincyUserId:(NULLABLE NSString *)userId
                                   quincyUserName:(NULLABLE NSString *)userName
                               quincyContactEmail:(NULLABLE NSString *)contactEmail
                           quincyCrashDescription:(NULLABLE NSString *)description;

/*!
 @brief Enable dynaTrace and Victory crash reporting.

 The DynatraceUEM ADK can report on application crashes using the KSCrash framwork.  Call this
 method after startupWithApplicationName:serverURL:allowAnyCert:certificatePath: to enable
 crash reporting to the dynaTrace server as well as a Victory server.  Crash
 information will be sent to both systems.

 When using auto-start you must set the cpwrUEM_crash.reporting info.plist value to NO when using
 this method to initiate crash reporting.

 @param sendCrashReport YES to send complete crash report to dynaTrace premium mode server.  NO to
 send only minimal information.

 @param serverURL The URL of your Victory server.

 @param userName Optional Victory user name.  Set to nil and the KSCrash framework will use
 UIDevice.currentDevice.name.

 @param userEmail Optional Victory user contact email address.  Set to nil if not needed.

 @return Returns a CPWR_StatusCode
 */
+ (CPWR_StatusCode)enableCrashReportingWithReport:(BOOL)sendCrashReport
                                       victoryURL:(NONNULL NSString *)serverURL
                                  victoryUserName:(NULLABLE NSString *)userName
                                 victoryUserEmail:(NULLABLE NSString *)userEmail;

/*!
 @brief Enable dynaTrace and email crash reporting.

 The DynatraceUEM ADK can report on application crashes using the KSCrash framwork.  Call this
 method after startupWithApplicationName:serverURL:allowAnyCert:certificatePath: to enable
 crash reporting to the dynaTrace server as well as by email.  Crash reports will
 be sent to the dynaTrace server, and the device user will have the opportunity to send the
 report by email to the address(es) of your choice.

 The device user will first see an alert on their screen.  You control the title, text, and button
 labels on the alert.  If the user taps the yes button, then the email UI will popup on the
 screen.  It will be preloaded with a message containing the recipients, subject, message, and the
 crash report as an attachment.  The can modify the message before sending it.

 When using auto-start you must set the cpwrUEM_crash.reporting info.plist value to NO when using
 this method to initiate crash reporting.

 @param sendCrashReport YES to send complete crash report to dynaTrace premium mode server.  NO to
 send only minimal information.

 @param recipients An array of NSString's each containing one email address.

 @param subject The email subject.

 @param message The email body text.

 @param filename The name to use for the file attachment containing the crash report.  Set to
 nil to use the default name.

 @param sendAppleStyleReport YES to send an Apple style crash report.  NO to send a JSON style
 crash report.

 @param alertTitle Title for the alert.

 @param alertMessage Message for the alert.

 @param yesButtonText Label for the yes button in the alert.  If the user taps this button, then
 the email UI appears.

 @param noButtonText Label for the no button in the alert.  If the user taps this button, then
 the crash report is not emailed.  It is still sent to dynaTrace.

 @return Returns a CPWR_StatusCode
 */

+ (CPWR_StatusCode)enableCrashReportingWithReport:(BOOL)sendCrashReport
                                  emailRecipients:(NULLABLE NSArray *)recipients
                                     emailSubject:(NULLABLE NSString *)subject
                                     emailMessage:(NULLABLE NSString *)message
                                    emailFilename:(NULLABLE NSString *)filename
                             sendAppleStyleReport:(BOOL)sendAppleStyleReport
                                       alertTitle:(NULLABLE NSString *)alertTitle
                                     alertMessage:(NULLABLE NSString *)alertMessage
                                    yesButtonText:(NULLABLE NSString *)yesButtonText
                                     noButtonText:(NULLABLE NSString *)noButtonText;

/*!
 @brief Set a cookie to be included in all ADK data transmissions.

 The DynatraceUEM ADK sends data to the server via HTTP or HTTPS.  If your infrastructure requires
 a cookie to be added to HTTP requests in order for them to pass you can use this method to set
 the value of the Cookie header.  This method must be called before the ADK is initialized using
 startupWithApplicationName:serverURL:allowAnyCert:certificatePath: so that the cookie is
 available for the first communication with the server.  It can be called again later to change
 the cookie value or to disable the Cookie header.

 @param cookieString The value for the HTTP Cookie header.  You can set multiple values by
 separating them with a semicolon and space as specified in the Cookie standard.  For instance
 "x=123; y=Open.gif".  Pass nil to remove the HTTP Cookie header from requests.
 */
+ (void)setMonitorCookie:(NONNULL NSString *)cookieString;

/*!
 @brief Returns the HTTP header to use for manual web request tagging.

 The DynatraceUEM ADK automatically tags web requests made using NSURLRequest, NSURLConnection,
 NSURLProtocol, NSString, UIWebView, and ASIHTTPRequest.  If you use an alternate technology to make
 web requests and want them to appear nested in a mobile action PurePath use this method and the
 getRequestTagValue method to retrieve the HTTP header and its value.  Adding that information to
 your request will include it in the PurePath.

 @return Returns the name of the HTTP header that you must add to your web request.
 */
+ (NONNULL NSString *)getRequestTagHeader;

/*!
 @deprecated
 @brief Returns the HTTP header value to use for manual web request tagging.

 This method is deprecated.  Please use getRequestTagValueForURL: instead.  If this method is
 used, you will not be able to time the web request using UEMWebRequestTiming.

 The DynatraceUEM ADK automatically tags web requests made using NSURLRequest, NSURLConnection,
 NSURLProtocol, NSString, UIWebView, and ASIHTTPRequest.  If you use an alternate technology to make
 web requests and want them to appear nested in a mobile action PurePath use this method and the
 getRequestTagHeader method to retrieve the HTTP header and its value.  Adding that information to
 your request will include it in the PurePath.

 @return Returns the value of the HTTP header that you must add to your web request.
 */
+ (NULLABLE NSString *)getRequestTagValue DEPRECATED_MSG_ATTRIBUTE("Please use getRequestTagValueForURL:");

/*!
 @brief Returns the HTTP header value to use for manual web request tagging.

 The DynatraceUEM ADK automatically tags web requests made using NSURLRequest, NSURLConnection,
 NSURLProtocol, NSString, UIWebView, and ASIHTTPRequest.  If you use an alternate technology to make
 web requests and want them to appear nested in a mobile action PurePath use this method and the
 getRequestTagHeader method to retrieve the HTTP header and its value.  Adding that information to
 your request will include it in the PurePath.

 @param url The NSURL for the web request.

 @return Returns the value of the HTTP header that you must add to your web request.
 */
+ (NULLABLE NSString *)getRequestTagValueForURL:(NULLABLE NSURL *)url;

@end

/*!
 @deprecated
 @brief Captures lifecycle actions for UIViewController.

 You no longer need to derive from special classes in order to get lifecycle instrumentation.
 Please remove references to this class because it will be removed in a future release.
 */
DEPRECATED_MSG_ATTRIBUTE("DynatraceUEM view controller classes are no longer needed "
                         "for lifecycle instrumentation")
@interface CompuwareUEMViewController : UIViewController

@end

/*!
 @deprecated
 @brief Captures lifecycle actions for UINavigationController.

 You no longer need to derive from special classes in order to get lifecycle instrumentation.
 Please remove references to this class because it will be removed in a future release.
 */
DEPRECATED_MSG_ATTRIBUTE("DynatraceUEM view controller classes are no longer needed "
                         "for lifecycle instrumentation")
@interface CompuwareUEMNavigationController : UINavigationController

@end

/*!
 @deprecated
 @brief Captures lifecycle actions for UIPageViewController.

 You no longer need to derive from special classes in order to get lifecycle instrumentation.
 Please remove references to this class because it will be removed in a future release.
 */
DEPRECATED_MSG_ATTRIBUTE("DynatraceUEM view controller classes are no longer needed "
                         "for lifecycle instrumentation")
@interface CompuwareUEMPageViewController : UIPageViewController

@end

/*!
 @deprecated
 @brief Captures lifecycle actions for UIReferenceLibraryViewController.

 You no longer need to derive from special classes in order to get lifecycle instrumentation.
 Please remove references to this class because it will be removed in a future release.
 */
DEPRECATED_MSG_ATTRIBUTE("DynatraceUEM view controller classes are no longer needed "
                         "for lifecycle instrumentation")
@interface CompuwareUEMReferenceLibraryViewController : UIReferenceLibraryViewController

@end

/*!
 @deprecated
 @brief Captures lifecycle actions for UISplitViewController.

 You no longer need to derive from special classes in order to get lifecycle instrumentation.
 Please remove references to this class because it will be removed in a future release.
 */
DEPRECATED_MSG_ATTRIBUTE("DynatraceUEM view controller classes are no longer needed "
                         "for lifecycle instrumentation")
@interface CompuwareUEMSplitViewController : UISplitViewController

@end

/*!
 @deprecated
 @brief Captures lifecycle actions for UITabBarController.

 You no longer need to derive from special classes in order to get lifecycle instrumentation.
 Please remove references to this class because it will be removed in a future release.
 */
DEPRECATED_MSG_ATTRIBUTE("DynatraceUEM view controller classes are no longer needed "
                         "for lifecycle instrumentation")
@interface CompuwareUEMTabBarController : UITabBarController

@end

/*!
 @deprecated
 @brief Captures lifecycle actions for UITableViewController.

 You no longer need to derive from special classes in order to get lifecycle instrumentation.
 Please remove references to this class because it will be removed in a future release.
 */
DEPRECATED_MSG_ATTRIBUTE("DynatraceUEM view controller classes are no longer needed "
                         "for lifecycle instrumentation")
@interface CompuwareUEMTableViewController : UITableViewController

@end

/*
 @brief Protocol deffinition for authentication class delegate
 */
@protocol DTXAuthenticationClassDelegate <NSObject>

+ (void)requestAuthenticationChallenge:(NONNULL NSURLAuthenticationChallenge *)challenge;

@end
