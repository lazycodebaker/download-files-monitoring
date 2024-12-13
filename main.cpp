#include <CoreServices/CoreServices.h>
#include <iostream>
#include <map>
#include <string>
#include <filesystem>

class FileMonitor
{
public:
    FileMonitor(const std::string &directoryPath) : directoryPath(directoryPath){};

    void startMonitoring()
    {
        CFStringRef cfDirectoryPath = CFStringCreateWithCString(nullptr, directoryPath.c_str(), kCFStringEncodingUTF8);

        CFArrayRef pathsToWatch = CFArrayCreate(nullptr, reinterpret_cast<const void **>(&cfDirectoryPath), 1, nullptr);
        void *fileMonitorContext = this;

        FSEventStreamContext context = {0, fileMonitorContext, nullptr, nullptr, nullptr};
        eventStream = FSEventStreamCreate(nullptr, &fileSystemEventCallback, &context, pathsToWatch, kFSEventStreamEventIdSinceNow, 1.0, kFSEventStreamCreateFlagNone);

        // FSEventStreamScheduleWithRunLoop(eventStream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);

        FSEventStreamSetDispatchQueue(eventStream, dispatch_get_main_queue());

        // print
        std::cout << "Monitoring directory: " << directoryPath << std::endl;
        // print the change file of the directory
        std::cout << "Press Ctrl+C to stop monitoring" << std::endl;

        FSEventStreamStart(eventStream);
        CFRunLoopRun();
    };

private:
    static void fileSystemEventCallback(
        ConstFSEventStreamRef streamRef,
        void *clientCallBackInfo, size_t numEvents,
        void *eventPaths,
        const FSEventStreamEventFlags eventFlags[],
        const FSEventStreamEventId eventIds[])
    {
        FileMonitor *fileMonitor = static_cast<FileMonitor *>(clientCallBackInfo);

        for (size_t i = 0; i < numEvents; ++i)
        {
            std::string filePath(static_cast<char **>(eventPaths)[i]);

            std::cout << "File changed: " << filePath << std::endl;

            fileMonitor->processFile(filePath);
        }
    }
    void processFile(const std::string &filePath)

#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>

class DownloadHandler
{
public:
    DownloadHandler(const std::string &downloadPath) : downloadPath(downloadPath) {}

    void onCreated(const std::filesystem::path &filePath)
    {
        if (!std::filesystem::is_directory(filePath))
        {
            processFile(filePath);
        }
    }

    void processFile(const std::filesystem::path &filePath)
    {
        std::string extension = filePath.extension().string();
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

        std::string destinationFolder = downloadPath + "/" + extension + "Files";

        if (!std::filesystem::exists(destinationFolder))
        {
            std::filesystem::create_directories(destinationFolder);
        }

        std::string destinationPath = destinationFolder + "/" + filePath.filename().string();

        std::filesystem::rename(filePath, destinationPath);

        std::cout << "Moved file: " << filePath << " to: " << destinationPath << std::endl;
    }

private:
    std::string downloadPath;
    std::unordered_map<std::string, std::string> extensionToFolders;
};

void monitorDirectory(const std::string &downloadPath, DownloadHandler &handler)
{
    while (true)
    {
        for (const auto &entry : std::filesystem::directory_iterator(downloadPath))
        {
            handler.onCreated(entry.path());
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    std::string downloadPath = "/Users/anshumantiwari/Documents/CODES/C++";

    DownloadHandler handler(downloadPath);

    std::thread monitorThread(monitorDirectory, downloadPath, std::ref(handler));

    monitorThread.join();

    return 0;
}
