//
//  Copyright (C) 2024 Arthur Benilov <arthur.benilov@gmail.com>
//

#pragma once

#include <JuceHeader.h>
#include <mutex>

/** Monitor UI resources.
 
    This class is used to watch all the files loader
    by the Vitro loader in order to trigger reload on
    any of the files change. 
*/
class FilesWatcher : private juce::Thread,
                     private juce::AsyncUpdater
{
public:

    class Listener
    {
    public:
        ~Listener() = default;
        virtual void onWatchedFilesChanged() = 0;
    };

    FilesWatcher(double periodMs = 1000.0);
    ~FilesWatcher();

    void clearWacthedFiles();
    void addFileToWatch(const File& file);

    void addListener(Listener* listener);
    void removeListener(Listener* listener);

private:

    // juce::Thread
    void run() override;

    // juce::AsyncUpdater
    void handleAsyncUpdate() override;

    bool checkAnyFileChanged();

    void notifyListeners();

    std::mutex mutex{};
    double watchPeriodMs{};

    struct FileRecord
    {
        juce::File file{};
        juce::Time lastModifiedTime{};
    };

    std::vector<FileRecord> filesToWatch{};

    juce::ListenerList<Listener> listeners{};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilesWatcher)
};
