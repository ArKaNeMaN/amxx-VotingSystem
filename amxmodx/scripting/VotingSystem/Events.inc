#include <amxmodx>
#include "VotingSystem/DebugMode"

/*
Functions & Macroses:
    T_Events:Events_Init(const iEnum);

    
    Events_PushListener(const T_Events:aEvents, const any:iEvent, const iForwardHandler);
    Events_AddListener(const T_Events:aEvents, const any:iEvent, iPluginId, const sCallback[], ...param_types);

    Events_Call(const T_Events:aEvents, const any:iEvent);
    Events_CallP(const T_Events:aEvents, const any:iEvent, [...params_values]);
    Events_GetReturnedValue();
*/

// Thx: https://dev-cs.ru/threads/222/page-12#post-103174
#define Events_CompositeMacros(%1) \
    do { %1 } while(is_linux_server() == 0xDEADBEEF)

enum T_Events { Invalid_Events = -1 }

T_Events:Events_Init(const iEnum) {
    new Array:aEvents = ArrayCreate(1, iEnum);
    for (new i = 0; i < iEnum; i++) {
        ArrayPushCell(aEvents, Invalid_Array);
    }

    return T_Events:aEvents;
}

T_Events:Events_Destroy(&T_Events:aEvents) {
    if (aEvents == Invalid_Events) {
        Dbg_Log("Tried to destroy an invalid event handler.");
        return Invalid_Events;
    }

    for (new i = 0; i < ArraySize(Array:aEvents); i++) {
        DestroyForward(ArrayGetCell(Array:aEvents, i));
    }
    ArrayDestroy(Array:aEvents);

    return Invalid_Events;
}

#define Events_AddListener(%1,%2,%3) \
    Events_PushListener(%1, %2, CreateOneForward(%3))

Events_PushListener(const T_Events:aEvents, const any:iEvent, const iForwardHandler) {
    if (aEvents == Invalid_Events) {
        Dbg_Log("Tried to push a listener for an invalid event handler.");
        return;
    }

    new Array:aListeners = ArrayGetCell(Array:aEvents, _:iEvent);
    if (aListeners == Invalid_Array) {
        aListeners = ArrayCreate(1, 1);
        ArraySetCell(Array:aEvents, _:iEvent, aListeners);
    }
    
    ArrayPushCell(aListeners, iForwardHandler);
}

Array:Events_GetListeners(const T_Events:aEvents, const any:iEvent) {
    if (aEvents == Invalid_Events) {
        Dbg_Log("Tried to get a listener from an invalid event handler.");
        return Invalid_Array;
    }

    return Array:ArrayGetCell(Array:aEvents, _:iEvent);
}

// Events_ForeachListener(const T_Events:aEvents, const any:iEvent: aListeners[i] => iListener)
#define Events_ForeachListener(%1,%2:%3[%4]=>%5) \
    if (%1 != Invalid_Events) \
        for ( \
            new %4 = 0, Array:%3 = Events_GetListeners(%1, %2), %5; \
            ( \
                %4 < (%3 == Invalid_Array ? 0 : ArraySize(%3)) \
                && (%5 = ArrayGetCell(%3, %4)) \
            ); \
            %4++ \
        ) 

stock __Events_Call_ret;
#define Events_GetReturnedValue() \
    __Events_Call_ret

#define Events_CallP(%1,%2,[%3]) Events_CompositeMacros( \
        Events_ForeachListener(%1, %2: __Events_Call_listeners[__Events_Call_i] => __Events_Call_listener) { \
            ExecuteForward(__Events_Call_listener, __Events_Call_ret, %3); \
        } \
    )

#define Events_Call(%1,%2) Events_CompositeMacros( \
        Events_ForeachListener(%1, %2: __Events_Call_listeners[__Events_Call_i] => __Events_Call_listener) { \
            ExecuteForward(__Events_Call_listener, __Events_Call_ret); \
        } \
    )
