#pragma once

#include "ClassComponent.h"

class File : public Component
{
    string fileDirectoryPath;

public:
    explicit File(const string& fileDirectoryPath);
    virtual void SetPath(const string& fileDirectoryPath);
    virtual string GetPath() const;
    virtual void Add(const string& name) const;
    virtual void Remove() const;
    virtual void Rename(const string& name) const;
    virtual void Copy() const;
    virtual void Relocate() const;
    virtual unsigned long long GetSizeInBytes() const;
};