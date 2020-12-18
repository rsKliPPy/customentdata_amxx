#include "module.h"

StringHashMap<std::unique_ptr<IEntDataEntry>> *g_entityData = nullptr;

void OnAmxxAttach()
{
    MF_AddNatives(g_natives);
}

void OnPluginsLoaded()
{
    g_entityData = new StringHashMap<std::unique_ptr<IEntDataEntry>>[gpGlobals->maxEntities];
}

void OnPluginsUnloaded()
{
    for(int i = 0; i < gpGlobals->maxEntities; i++)
    {
        g_entityData[i].clear();
    }
}

void OnFreeEntPrivateData_Post(edict_t *ed)
{
    // TODO: Let plugins somehow release handles bound to this entity

    g_entityData[g_engfuncs.pfnIndexOfEdict(ed)].clear();

    RETURN_META(MRES_IGNORED);
}
