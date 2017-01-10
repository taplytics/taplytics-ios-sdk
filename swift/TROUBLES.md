Here are some of the common errors we've run into when installing the Taplytics SDK and the fixes to go with them. We hope it helps keep the installation smooth, if you feel like you need a hand, please don't hesitate to reach out. We'd love to hear from you.

| Table of Contents |
| ----------------- |
| ["_OBJC_CLASS_$_Taplytics" not found](#objc_class_taplytics-not-found) |
| ["_utf8_nextCharSafeBody" build error](#_utf8_nextcharsafebody-build-error) |
| [Terminating app due to uncaught exception 'NSInvalidArgumentException'](#terminating-app-due-to-uncaught-exception) |
| ["OTHER_LDFLAGS" Error](#other_ldflags-error) |


### "_OBJC_CLASS_$_Taplytics" not found

```
Undefined symbols for architecture x86_64:
  "_OBJC_CLASS_$_Taplytics", referenced from:
      objc-class-ref in AppDelegate.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

If you encounter the error above when attempting to build and run your app in XCode, please make sure Taplytics.framework is in the Link Binary With Libraries.

To navigate to the correct menu:

Project => Build Phases => Link Binary With Libraries


### "_utf8_nextCharSafeBody" build error

```
Undefined symbols for architecture x86_64:
  "_utf8_nextCharSafeBody", referenced from:
      -[TL_SRWebSocket _innerPumpScanner] in Taplytics(TL_SRWebSocket.o)
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

If you encounter this error when attempting to build and run your app in XCode, the entry for libicucore.dylib might be missing, please make sure that it has been added to your Link Binary With Libraries list.

To navigate to the correct menu:

Project => Build Phases => Link Binary With Libraries


### Terminating app due to uncaught exception

```
Terminating app due to uncaught exception 'NSInvalidArgumentException'
...
libc++abi.dylib: terminating with uncaught exception of type NSException
```

If you encounter this error when attempting to build and run your app in XCode, the -ObjC flag is missing under Other Linker Flags.

To navigate to the correct menu:

Project => Build Settings => Other Linker Flags = "-ObjC"


### "OTHER_LDFLAGS" Error

If you're running into an "OTHER_LDFLAGS" error when trying to build your podfile using $pod install, we have a simple fix for you!

Here's an example of the error:

```
[!] The target `Taplytics Example App [Debug]` overrides the `OTHER_LDFLAGS` build setting defined in `Pods/Pods.xcconfig'.
  - Use the `$(inherited)` flag, or
  - Remove the build settings from the target.
[!] The target `Taplytics Example App [Debug - Release]` overrides the `OTHER_LDFLAGS` build setting defined in `Pods/Pods.xcconfig'.
  - Use the `$(inherited)` flag, or
  - Remove the build settings from the target.
```

The Fix:

In XCode, go to "Build Settings" and find the "Other Linker Flags" setting under "Linking". The entry for this setting should be bolded.




#### OPTION A:

Select the value for the "Other Linker Flags" setting and hit backspace. This should remove the bolded value, and a list of non-bolded values should appear. These are all the flags from the CocoaPod.

#### OPTION B:

If you need to have your own flags declared, include $(inherited) in the list of flags. This should append all the flags defined in the CocoaPod to your list of flags.

THE ADDITIONAL FIX:

If the fix above still doesn't address the compilation error, please try clearing the bolded values or add $(inherited) to the following Build Settings:

Framework Search Paths
Header Search Paths
