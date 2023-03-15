#include "module.h"

#define NATIVE_SETUP() \
    int index = params[1]; \
    edict_t *ent = g_engfuncs.pfnPEntityOfEntIndex(index); \
    if(ent == nullptr) \
    { \
        MF_LogError(amx, AMX_ERR_NATIVE, "Invalid entity %d", index); \
        return 0; \
    } \
    int dummyLen; \
    const char *key = MF_GetAmxString(amx, params[2], 1, &dummyLen);


//native CED_SetCell(entity, const key[], any:data);
static cell Native_SetCell(AMX *amx, cell *params)
{
    NATIVE_SETUP();

    g_entityData[index].replace(key, std::unique_ptr<IEntDataEntry>(new EntDataCell(params[3])));

    return 0;
}

//native CED_SetArray(entity, const key[], const any:data[], size);
static cell Native_SetArray(AMX *amx, cell *params)
{
    NATIVE_SETUP();
    
    std::unique_ptr<cell[]> data(new cell[params[4]]);
    MF_CopyAmxMemory(data.get(), MF_GetAmxAddr(amx, params[3]), params[4]);

    g_entityData[index].replace(key, std::unique_ptr<IEntDataEntry>(new EntDataArray(std::move(data), params[4])));

    return 0;
}

//native CED_SetString(entity, const key[], const buffer[]);
static cell Native_SetString(AMX *amx, cell *params)
{
    NATIVE_SETUP();

    g_entityData[index].replace(key, std::unique_ptr<IEntDataEntry>(new EntDataString(MF_GetAmxString(amx, params[3], 2, &dummyLen))));

    return 0;
}

//native bool:CED_GetCell(entity, const key[], &any:data);
static cell Native_GetCell(AMX *amx, cell *params)
{
    NATIVE_SETUP();

    std::unique_ptr<IEntDataEntry> *ptrData;
    if(g_entityData[index].retrieve(key, &ptrData))
    {
        EntDataCell *data = static_cast<EntDataCell *>(ptrData->get());
        if(data->GetEntryType() != IEntDataEntry::EntryType::Cell)
            return 0;

        *(MF_GetAmxAddr(amx, params[3])) = data->Data;
        return 1;
    }

    return 0;
}

//native bool:CED_GetArray(entity, const key[], any:data[], size);
static cell Native_GetArray(AMX *amx, cell *params)
{
    NATIVE_SETUP();

    std::unique_ptr<IEntDataEntry> *ptrData;
    if(g_entityData[index].retrieve(key, &ptrData))
    {
        EntDataArray *data = static_cast<EntDataArray *>(ptrData->get());
        if(data->GetEntryType() != IEntDataEntry::EntryType::Array)
            return 0;

        size_t size = static_cast<size_t>(params[4]);
        if(size > data->DataSize)
            size = data->DataSize;

        cell *outAddr = MF_GetAmxAddr(amx, params[3]);
        MF_CopyAmxMemory(outAddr, data->Data.get(), size);
        return 1;
    }

    return 0;
}

//native bool:CED_GetString(entity, const key[], buffer[], maxLength);
static cell Native_GetString(AMX *amx, cell *params)
{
    NATIVE_SETUP();

    std::unique_ptr<IEntDataEntry> *ptrData;
    if(g_entityData[index].retrieve(key, &ptrData))
    {
        EntDataString *data = static_cast<EntDataString *>(ptrData->get());
        if(data->GetEntryType() != IEntDataEntry::EntryType::String)
            return 0;

        MF_SetAmxString(amx, params[3], data->Data.c_str(), params[4]);
        return 1;
    }
    
    return 0;
}


AMX_NATIVE_INFO g_natives[] =
{
    {"CED_SetCell", Native_SetCell},
    {"CED_SetArray", Native_SetArray},
    {"CED_SetString", Native_SetString},

    {"CED_GetCell", Native_GetCell},
    {"CED_GetArray", Native_GetArray},
    {"CED_GetString", Native_GetString},

    {nullptr, nullptr}
};
