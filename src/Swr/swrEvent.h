#ifndef SWREVENT_H
#define SWREVENT_H

#include "types.h"
#include "macros.h"

// 0x004bfec0
swrEventManager eventManagerMain[][9] = {
    {
        {
            .event = EVENT("Test"),
            .unk1 = 0x31,
            .count = 0,
            .size = 0x1f28,
            .head = NULL,
            .f0 = NULL, // TODO
            .f1 = NULL, // TODO
            .f2 = NULL, // TODO
            .f3 = NULL, // TODO
            .f4 = NULL, // TODO
        },
        {
            .event = EVENT("Toss"),
            .unk1 = 1,
            .count = 0,
            .size = 0x7c,
            .head = NULL,
            .f0 = NULL, // TODO
            .f1 = NULL,
            .f2 = NULL, // TODO
            .f3 = NULL, // TODO
            .f4 = NULL, // TODO
        },
        {
            .event = EVENT("Trig"),
            .unk1 = 0,
            .count = 0,
            .size = 0x58,
            .head = NULL,
            .f0 = NULL, // TODO
            .f1 = NULL,
            .f2 = NULL, // TODO
            .f3 = NULL, // TODO
            .f4 = NULL, // TODO
        },
        {
            .event = EVENT("Hang"),
            .unk1 = 0,
            .count = 0,
            .size = 0xd0,
            .head = NULL,
            .f0 = NULL, // TODO
            .f1 = NULL,
            .f2 = NULL, // TODO
            .f3 = NULL, // TODO
            .f4 = NULL, // TODO
        },
        {
            .event = EVENT("Jdge"),
            .unk1 = 0x31,
            .count = 0,
            .size = 0x1e8,
            .head = NULL,
            .f0 = NULL, // TODO
            .f1 = NULL,
            .f2 = NULL, // TODO
            .f3 = NULL, // TODO
            .f4 = NULL, // TODO
        },
        {
            .event = EVENT("Scen"),
            .unk1 = 0,
            .count = 0,
            .size = 0x1b4c,
            .head = NULL,
            .f0 = NULL, // TODO
            .f1 = NULL,
            .f2 = NULL, // TODO
            .f3 = NULL, // TODO
            .f4 = NULL, // TODO
        },
        {
            .event = EVENT("Elmo"),
            .unk1 = 0x31,
            .count = 0,
            .size = 0xc0,
            .head = NULL,
            .f0 = NULL, // TODO
            .f1 = NULL,
            .f2 = NULL, // TODO
            .f3 = NULL, // TODO
            .f4 = NULL, // TODO
        },
        {
            .event = EVENT("Smok"),
            .unk1 = 0x31,
            .count = 0,
            .size = 0x108,
            .head = NULL,
            .f0 = NULL, // TODO
            .f1 = NULL,
            .f2 = NULL, // TODO
            .f3 = NULL, // TODO
            .f4 = NULL, // TODO
        },
        {
            .event = EVENT("cMan"),
            .unk1 = 0x31,
            .count = 0,
            .size = 0x3a8,
            .head = NULL,
            .f0 = NULL, // TODO
            .f1 = NULL,
            .f2 = NULL, // TODO
            .f3 = NULL, // TODO
            .f4 = NULL, // TODO
        },
    },
    NULL,
};

#define swrEvent_Initialize_ADDR (0x00450850)

#define swrEvent_CallAllF0_ADDR (0x004508b0)

#define swrEvent_CallAllF1_ADDR (0x00450930)

#define swrEvent_CallAllF2_ADDR (0x004509b0)

#define swrEvent_CallAllF3_ADDR (0x00450a30)

#define swrEvent_FindObjectById_ADDR (0x00450aa0)

#define swrEvent_GetEventCount_ADDR (0x00450b00)

#define swrEvent_GetItem_ADDR (0x00450b30)

#define swrEvent_DispatchSubEvents_ADDR (0x00450c00)

#define swrEvent_CallF4_ADDR (0x00450c50)

#define swrEvent_SetObjs_ADDR (0x00450ce0)

#define swrEvent_AllocObj_ADDR (0x00450d20)

#define swrEvent_FreeObjs_ADDR (0x00450db0)

void swrEvent_Initialize(int event);

void swrEvent_CallAllF0(void);

void swrEvent_CallAllF1(void);

void swrEvent_CallAllF2(void);

void swrEvent_CallAllF3(void);

void* swrEvent_FindObjectById(int event, int id);

int swrEvent_GetEventCount(int event);

void* swrEvent_GetItem(int event, int index);

void swrEvent_DispatchSubEvents(void* obj, int* subEvents); // int[2]

void swrEvent_CallF4(int event, void* forward_param);

void* swrEvent_SetObjs(int event, int count, void* obj);

void* swrEvent_AllocObj(int event);

void swrEvent_FreeObjs(int event);

#endif // SWREVENT_H
