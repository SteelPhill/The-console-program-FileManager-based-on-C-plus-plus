#pragma once

class Component
{
public:
    virtual ~Component(){}
    virtual void SetPath(const string& path) = 0;
    virtual string GetPath() const = 0;
    virtual void Add(const string& path) const = 0;
    virtual void Remove() const = 0;
    virtual void Rename(const string& newPath) const = 0;
    virtual void Copy() const = 0;
    virtual void Relocate() const = 0;
    virtual unsigned long long GetSizeInBytes() const = 0;
};