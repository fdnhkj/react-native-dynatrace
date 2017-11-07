//
//  ODDynatraceModule.java
//  ODDynatraceModule
//
//  Created by OLIVIER DEMOLLIENS on 15/03/2017.
//  Copyright © 2017 DEMOLLIENS. All rights reserved.
//

package com.odemolliens.rn.dynatrace;

import android.util.Log;

import com.dynatrace.apm.uem.mobile.android.DynatraceUEM;
import com.dynatrace.apm.uem.mobile.android.UemAction;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Callback;

public class ODDynatraceModule extends ReactContextBaseJavaModule {

    private final ReactApplicationContext reactContext;

    public ODDynatraceModule(ReactApplicationContext reactContext) {
        super(reactContext);
        this.reactContext = reactContext;
    }

    @Override
    public String getName() {
        return "ODDynatrace";
    }


    @ReactMethod
    public void startup(String appId, String serverURL) {
        int statusCode = DynatraceUEM.startup(
                reactContext,
                appId,
                serverURL,
                false,
                null
        );
        switch (statusCode) {
            case DynatraceUEM.CPWR_UemOn:
                Log.i("ReactNative", "Dynatrace startup status code = Successful (CPWR_UemOn)");
                break;
            case DynatraceUEM.CPWR_Error_InvalidParameter:
                Log.e("ReactNative", "Dynatrace startup status code = appId or serverURL is null or empty (CPWR_Error_InvalidParameter)");
        }
    }

    @ReactMethod
    public void shutdown() {
        DynatraceUEM.shutdown();
    }

    @ReactMethod
    public void enterAction(String actionName) {
        UemAction action = DynatraceUEM.enterAction(actionName);
        //temporary leaving action directly
        action.leaveAction();
    }
}