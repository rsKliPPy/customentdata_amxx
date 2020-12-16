#ifndef MODULE_H
#define MODULE_H

#include "amxxsdk/amxxmodule.h"
#include "sm_stringhashmap.h"
#include "EntData.h"


extern AMX_NATIVE_INFO g_natives[];
extern StringHashMap<std::unique_ptr<IEntDataEntry>> *g_entityData;

#endif // MODULE_H
