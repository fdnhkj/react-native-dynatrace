
# react-native-dynatrace

## Getting started

`$ npm install react-native-dynatrace --save`

### Mostly automatic installation

`$ react-native link react-native-dynatrace`

### Manual installation


#### iOS

1. In XCode, in the project navigator, right click `Libraries` ➜ `Add Files to [your project's name]`
2. Go to `node_modules` ➜ `react-native-dynatrace` and add `PXSDynatrace.xcodeproj`
3. In XCode, in the project navigator, select your project. Add `libPXSDynatrace.a` to your project's `Build Phases` ➜ `Link Binary With Libraries`
4. Run your project (`Cmd+R`)<

#### Android

1. Open up `android/app/src/main/java/[...]/MainActivity.java`
  - Add `import com.reactlibrary.PXSDynatracePackage;` to the imports at the top of the file
  - Add `new PXSDynatracePackage()` to the list returned by the `getPackages()` method
2. Append the following lines to `android/settings.gradle`:
  	```
  	include ':react-native-dynatrace'
  	project(':react-native-dynatrace').projectDir = new File(rootProject.projectDir, 	'../node_modules/react-native-dynatrace/android')
  	```
3. Insert the following lines inside the dependencies block in `android/app/build.gradle`:
  	```
      compile project(':react-native-dynatrace')
  	```


## Usage
```javascript
import PXSDynatrace from 'react-native-dynatrace';

// TODO: What do with the module?
PXSDynatrace;
```

## TODO
- Possibility to get an action in JS side
	- Invalid type in JSON Write (UEMAction) - see screenshot `RCTJSONStringify-UEMAction-issue.png`
	- convert UEMAction to a NSDictionary
	- Useful links
		- https://github.com/wmcmahan/react-native-calendar-events/blob/master/RNCalendarEvents.m#L84
		- https://github.com/Microsoft/react-native-code-push/blob/master/ios/CodePush/CodePushConfig.m
		- https://facebook.github.io/react-native/docs/native-modules-ios.html
		- https://community.dynatrace.com/community/display/DOCDT63/Android+ADK+Setup+and+Instrumentation
		- https://community.dynatrace.com/community/display/DOCDT63/iOS+ADK+Setup+and+Instrumentation