#include "module.h"
#include "chooker.h"
#include <amtl/am-platform.h>


static CHooker Hooker;

using FN_ED_Free = void (*)(edict_t *);
//typedef void (*FN_ED_Free)(edict_t *);

static FN_ED_Free pfnED_Free = nullptr;
static CFunc* funcED_Free = nullptr;


void ED_Free_Hook(edict_t *ed)
{
    GET_ORIG_FUNC(func);

    if(func->Restore())
    {
        g_entityData[g_engfuncs.pfnIndexOfEdict(ed)].clear();

        pfnED_Free(ed);

        funcED_Free->Patch();
    }
}

bool CreateHooks()
{
#ifdef KE_WINDOWS
    pfnED_Free = Hooker.MemorySearch<FN_ED_Free>("0x55,0x8B,0xEC,0x56,0x8B,0x75,*,0x57,0x33,0xFF,0x39,0x3E", (void *)gpGlobals, FALSE);
#else
    pfnED_Free = Hooker.MemorySearch<FN_ED_Free>("ED_Free", (void *)gpGlobals, TRUE);
#endif

    funcED_Free = Hooker.CreateHook((void *)pfnED_Free, (void *)ED_Free_Hook, TRUE);
    if(funcED_Free == nullptr)
    {
        g_engfuncs.pfnServerPrint("Failed to create ED_Free() hook...\n");
        return false;
    }

    g_engfuncs.pfnServerPrint("Successfully hooked ED_Free()\n");

    return true;
}

void RestoreHooks()
{
    funcED_Free->Restore();
}