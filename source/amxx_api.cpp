#include "module.h"

StringHashMap<ke::AutoPtr<IEntDataEntry>> *g_entityData = nullptr;

void OnAmxxAttach()
{
    MF_AddNatives(g_natives);
}

void OnPluginsLoaded()
{
    g_entityData = new StringHashMap<ke::AutoPtr<IEntDataEntry>>[gpGlobals->maxEntities];
}

void OnPluginsUnloaded()
{
    for(int i = 0; i < gpGlobals->maxEntities; i++)
    {
        g_entityData[i].clear();
    }

    delete g_entityData;
}

void OnFreeEntPrivateData_Post(edict_t *ed)
{
    // TODO: Let plugins somehow release handles bound to this entity

    g_entityData[g_engfuncs.pfnIndexOfEdict(ed)].clear();
}