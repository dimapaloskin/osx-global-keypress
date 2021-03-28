#include <stdio.h>
#include <ApplicationServices/ApplicationServices.h>
CGEventRef
myCGEventCallback(CGEventTapProxy proxy, CGEventType type,
                  CGEventRef event, void *refcon)
{
    int flags = CGEventGetFlags(event);
    if (type == kCGEventLeftMouseDown) {
        printf("%d left", flags);
        fflush(stdout);
    } else if (type == kCGEventRightMouseDown) {
        printf("%d right", flags);
        fflush(stdout);
    } else if (type == kCGEventOtherMouseDown) {
        printf("%d middle", flags);
        fflush(stdout);
    } else {
        CGKeyCode keycode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
        printf("%d %d", flags, keycode);
        fflush(stdout);
    }
    return event;
}

int
main(void)
{
    CFMachPortRef      eventTap;
    CGEventMask        eventMask;
    CFRunLoopSourceRef runLoopSource;

    eventMask
        = (1 << kCGEventKeyDown)
        | (1 << kCGEventLeftMouseDown)
        | (1 << kCGEventRightMouseDown)
        | (1 << kCGEventOtherMouseDown);
    eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0,
                                eventMask, myCGEventCallback, NULL);

    if (!eventTap) {
        fprintf(stderr, "Can't create event handler. Try to run with sudo.\n");
        exit(1);
    }

    runLoopSource = CFMachPortCreateRunLoopSource(
                        kCFAllocatorDefault, eventTap, 0);

    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource,
                       kCFRunLoopCommonModes);

    CGEventTapEnable(eventTap, true);
    CFRunLoopRun();

    //exit(0);
}
