#ifndef CENTDATAENTRY_H
#define CENTDATAENTRY_H

#include "amxxsdk/amxxmodule.h"
#include <amtl/am-string.h>
#include <amtl/am-autoptr.h>

class IEntDataEntry
{
public:
    enum EntryType
    {
        Cell = 0,
        Array,
        String
    };

public:
    virtual EntryType GetEntryType() const = 0;

    virtual ~IEntDataEntry()
    { }
};

class EntDataCell : public IEntDataEntry
{
public:
    EntryType GetEntryType() const override
    {
        return EntryType::Cell;
    }

    EntDataCell(cell data) : Data(data)
    {
    }

public:
    cell Data;
};

class EntDataArray : public IEntDataEntry
{
public:
    EntryType GetEntryType() const override
    {
        return EntryType::Array;
    }

    EntDataArray(ke::AutoPtr<cell[]> &&data, size_t size) : Data(ke::Move(data)), DataSize(size)
    {
    }

public:
    ke::AutoPtr<cell[]> Data;
    size_t DataSize;
};

class EntDataString : public IEntDataEntry
{
public:
    EntryType GetEntryType() const override
    {
        return EntryType::String;
    }

    EntDataString(const char *data) : Data(data)
    {
    }

public:
    ke::AString Data;
};

#endif // CENTDATAENTRY_H