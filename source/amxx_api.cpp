#include "module.h"

StringHashMap<ke::AutoPtr<IEntDataEntry>> *g_entityData = nullptr;

void OnAmxxAttach()
{
    g_entityData = new StringHashMap<ke::AutoPtr<IEntDataEntry>>[gpGlobals->maxEntities];

    CreateHooks() && MF_AddNatives(g_natives);
}

void OnAmxxDetach()
{
    RestoreHooks();
}

void OnPluginsUnloaded()
{
    for(int i = 0; i < gpGlobals->maxEntities; i++)
    {
        g_entityData[i].clear();
    }

    delete g_entityData;
}