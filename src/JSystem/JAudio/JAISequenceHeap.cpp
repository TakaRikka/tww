//
// Generated by dtk
// Translation Unit: JAISequenceHeap.cpp
//

#include "JSystem/JAudio/JAISequenceHeap.h"
#include "JSystem/JAudio/JAIBasic.h"
#include "JSystem/JAudio/JAIGlobalParameter.h"
#include "JSystem/JKernel/JKRSolidHeap.h"

JAInter::HeapBlock* JAInter::HeapMgr::sAutoHeap;
JAInter::HeapBlock* JAInter::HeapMgr::sStayHeap;
u32 JAInter::HeapMgr::sAutoHeapCount;
u32 JAInter::HeapMgr::sStayHeapCount;

/* 80294F5C-8029531C       .text init__Q27JAInter7HeapMgrFUcUlUcUl */
void JAInter::HeapMgr::init(u8 param_1, u32 param_2, u8 param_3, u32 param_4) {
    sAutoHeap = new (JAIBasic::getCurrentJAIHeap(), 0x20) HeapBlock[param_3];
    JUT_ASSERT_MSG(38, sAutoHeap, "JAIHeapMgr::initHeap Cannot Alloc Heap!!\n");
    for (u32 i = 0; i < param_3; i++) {
        sAutoHeap[i].mStatus = 0;
        sAutoHeap[i].field_0xc = 0;
        sAutoHeap[i].field_0x8 = -1;
        sAutoHeap[i].field_0x10 = -1;
        sAutoHeap[i].mPointer = new (JAIBasic::getCurrentJAIHeap(), 0x20) u8[param_4];
    }
    sStayHeap = new (JAIBasic::getCurrentJAIHeap(), 0x20) HeapBlock[param_1];
    JUT_ASSERT_MSG(48, sStayHeap, "JAIHeapMgr::initHeap Cannot Alloc Heap!!\n");
    sStayHeap->mPointer = new (JAIBasic::getCurrentJAIHeap(), 0x20) u8[param_2];
    for (u32 i = 0; i < param_1; i++) {
        sStayHeap[i].mStatus = 0;
        sStayHeap[i].field_0xc = 0;
        sStayHeap[i].field_0x8 = -1;
        sStayHeap[i].field_0x10 = -1;
    }
}

/* 8029531C-80295324       .text getAutoHeapPointer__Q27JAInter7HeapMgrFv */
JAInter::HeapBlock* JAInter::HeapMgr::getAutoHeapPointer() {
    return sAutoHeap;
}

/* 80295324-8029541C       .text checkOnMemory__Q27JAInter7HeapMgrFUlPUc */
void* JAInter::HeapMgr::checkOnMemory(u32 param_1, u8* param_2) {
    for (u8 i = 0; i < JAIGlobalParameter::getParamAutoHeapMax(); i++) {
        if (param_1 != sAutoHeap[i].field_0x8) {
            continue;
        }
        if (sAutoHeap[i].mStatus == 1) {
            return (void*)-1;
        }
        if (param_2) {
            *param_2 = i;
        }
        return sAutoHeap[i].getPointer();
    }
    for (u8 i = 0; i < sStayHeapCount; i++) {
        if (param_1 != sStayHeap[i].field_0x8) {
            continue;
        }
        if (param_2) {
            *param_2 = 0xff;
        }
        return sStayHeap[i].getPointer();
    }
    return NULL;
}

/* 8029541C-80295440       .text releaseAutoHeapPointer__Q27JAInter7HeapMgrFUc */
void JAInter::HeapMgr::releaseAutoHeapPointer(u8 param_1) {
    /* Nonmatching */
    if (param_1 == 0xff) {
        return;
    }
    sAutoHeap[param_1].field_0x10 = -1;
}

/* 80295440-80295518       .text checkUsefulAutoHeapPosition__Q27JAInter7HeapMgrFv */
u8 JAInter::HeapMgr::checkUsefulAutoHeapPosition() {
    int i = 0;
    u32 r29 = -1;
    int r28 = 0;
    for (; i < JAIGlobalParameter::getParamAutoHeapMax(); i++) {
        if (sAutoHeap[i].field_0x8 == -1) {
            break;
        }
    }
    if (i == JAIGlobalParameter::getParamAutoHeapMax()) {
        for (i = 0; i < JAIGlobalParameter::getParamAutoHeapMax(); i++) {
            if (r29 > sAutoHeap[i].field_0xc && sAutoHeap[i].field_0x10 == -1) {
                r28 = i;
                r29 = sAutoHeap[i].field_0xc;
            }
        }
        if (r29 != -1) {
            i = r28;
        }
    }
    return i;
}

/* 80295518-80295560       .text getFreeAutoHeapPointer__Q27JAInter7HeapMgrFUcUl */
void* JAInter::HeapMgr::getFreeAutoHeapPointer(u8 param_1, u32 param_2) {
    /* Nonmatching */
    sAutoHeap[param_1].field_0x8 = param_2;
    void* result = sAutoHeap[param_1].mPointer;
    sAutoHeap[param_1].field_0x10 = sAutoHeapCount;
    sAutoHeap[param_1].field_0xc = sAutoHeapCount;
    sAutoHeapCount++;
    return result;
}

/* 80295560-80295658       .text getFreeStayHeapPointer__Q27JAInter7HeapMgrFUlUl */
void* JAInter::HeapMgr::getFreeStayHeapPointer(u32 param_1, u32 param_2) {
    /* Nonmatching */
    if (sStayHeapCount >= JAIGlobalParameter::getParamStayHeapMax()) {
        return NULL;
    }
    void* r30 = sStayHeap[0].getPointer();
    void* r29 = sStayHeap[sStayHeapCount].getPointer();
    if (u32(r29) + param_1 < u32(r30) + JAIGlobalParameter::getParamStayHeapSize() && sStayHeapCount < JAIGlobalParameter::getParamStayHeapMax()) {
        r29 = sStayHeap[sStayHeapCount].getPointer();
        sStayHeap[sStayHeapCount].field_0x8 = param_2;
        r30 = (void*)(u32(sStayHeap[sStayHeapCount].getPointer()) + ALIGN_PREV(param_1, 32));
        if (IS_NOT_ALIGNED(param_1, 32)) {
            r30 = (void*)(u32(r30) + 32);
        }
        sStayHeapCount++;
        if (sStayHeapCount < JAIGlobalParameter::getParamStayHeapMax()) {
            sStayHeap[sStayHeapCount].setPointer(r30);
        }
    } else {
        r29 = NULL;
    }
    return r29;
}

/* 80295658-8029566C       .text setAutoHeapLoadedFlag__Q27JAInter7HeapMgrFUcUc */
void JAInter::HeapMgr::setAutoHeapLoadedFlag(u8 param_1, u8 param_2) {
    sAutoHeap[param_1].setStatus(param_2);
}

/* 8029566C-80295684       .text __ct__Q27JAInter9HeapBlockFv */
JAInter::HeapBlock::HeapBlock() {
    field_0xc = 0;
    field_0x8 = -1;
    field_0x10 = -1;
}
