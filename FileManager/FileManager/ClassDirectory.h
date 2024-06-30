#pragma once

#include "ClassComponent.h"

class Directory : public Component
{
    string directoryPath;

    int DirectoryItemsNumber() const;
    unsigned long long GetSizeInBytesByRecursive(const string& directoryPath) const;
    string MaskSearchByRecursive(const string& directoryPath, const string& searchedText) const;

public:
    Directory();
    explicit Directory(const string& path);
    virtual void SetPath(const string& path);
    virtual string GetPath() const;
    string SelectDirectoryItem() const;
    string MaskSearch(const string& text);
    void ShowContent() const;
    void Previous();
    void GoToSelectedDirectory(const string& newPath);
    virtual void Add(const string& name) const;
    virtual void Remove() const;
    virtual void Rename(const string& name) const;
    virtual void Copy() const;
    virtual void Relocate() const;
    virtual unsigned long long GetSizeInBytes() const;
};