#ifndef MODULE_H
#define MODULE_H

#include "amxxsdk/amxxmodule.h"
#include <amtl/am-autoptr.h>
#include "sm_stringhashmap.h"
#include "EntData.h"


extern AMX_NATIVE_INFO g_natives[];
extern StringHashMap<ke::AutoPtr<IEntDataEntry>> *g_entityData;

bool CreateHooks();
void RestoreHooks();


#endif // MODULE_H