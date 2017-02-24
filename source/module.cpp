#include "module.h"
#include "chooker.h"
#include <amtl/am-platform.h>


static CHooker Hooker;

static CFunc* funcFreeEntPrivateData = nullptr;

void FreeEntPrivateData_Hook(edict_t *ed)
{
    GET_ORIG_FUNC(func);

    if(func->Restore())
    {
        g_entityData[g_engfuncs.pfnIndexOfEdict(ed)].clear();

        g_engfuncs.pfnFreeEntPrivateData(ed);

        funcFreeEntPrivateData->Patch();
    }
}

bool CreateHooks()
{
    funcFreeEntPrivateData = Hooker.CreateHook((void *)g_engfuncs.pfnFreeEntPrivateData, (void *)FreeEntPrivateData_Hook, TRUE);
    if(funcFreeEntPrivateData == nullptr)
    {
        g_engfuncs.pfnServerPrint("[CED] Failed to create FreeEntPrivateData() hook...\n");
        return false;
    }

    return true;
}

void RestoreHooks()
{
    if(funcFreeEntPrivateData != nullptr)
        funcFreeEntPrivateData->Restore();
}