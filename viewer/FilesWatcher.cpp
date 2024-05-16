//
//  Copyright (C) 2024 Arthur Benilov <arthur.benilov@gmail.com>
//

#include "FilesWatcher.h"

FilesWatcher::FilesWatcher(double periodMs)
    : juce::Thread("VITRO View files watcher")
{
    watchPeriodMs = jlimit(200.0, 10000.0, periodMs);

    startThread();
}

FilesWatcher::~FilesWatcher()
{
    if (isThreadRunning()) {
        stopThread(-1);
    }
}

void FilesWatcher::clearWacthedFiles()
{
    std::scoped_lock lock{ mutex };
    filesToWatch.clear();
}

void FilesWatcher::addFileToWatch(const File& file)
{
    if (!file.existsAsFile())
        return;

    FileRecord record{};
    record.file = file;
    record.lastModifiedTime = file.getLastModificationTime();

    std::scoped_lock lock{ mutex };

    bool alreadyWatched{ false };

    for (auto& fileRecord : filesToWatch) {
        if (fileRecord.file.getFullPathName() == record.file.getFullPathName()) {
            // Adding an already watched file - just update the timestamp
            fileRecord.lastModifiedTime = record.lastModifiedTime;
            alreadyWatched = true;
            break;
        }
    }

    if (!alreadyWatched)
        filesToWatch.push_back(record);
}

void FilesWatcher::addListener(Listener* listener)
{
    jassert(listener != nullptr);
    listeners.add(listener);
}

void FilesWatcher::removeListener(Listener* listener)
{
    jassert(listener != nullptr);
    listeners.remove(listener);
}

void FilesWatcher::run()
{
    while (!threadShouldExit()) {
        if (checkAnyFileChanged()) {
            triggerAsyncUpdate();

            wait(watchPeriodMs);
        }
    }
}

void FilesWatcher::handleAsyncUpdate()
{
    notifyListeners();
}

bool FilesWatcher::checkAnyFileChanged()
{
    std::scoped_lock lock{ mutex };

    bool changed{ false };

    for (auto& fileRecord : filesToWatch) {
        if (fileRecord.file.existsAsFile()) {
            const auto modifiedTime{ fileRecord.file.getLastModificationTime() };

            if (fileRecord.lastModifiedTime != modifiedTime) {
                changed = true;
                fileRecord.lastModifiedTime = modifiedTime;
                // Don't break here as we want to update all modified
                // timestamps to avoid burst notifications
            }
        }
    }

    return changed;
}

void FilesWatcher::notifyListeners()
{
    listeners.call(&Listener::onWatchedFilesChanged);
}