# File Monitoring and Sorting Utility

This utility monitors a specified directory for file changes and automatically sorts newly created files into corresponding folders based on their file extensions. It is implemented in C++ and utilizes the filesystem library for file manipulation and monitoring.

## How It Works

### 1. File Monitoring

The program uses platform-specific file system monitoring mechanisms to detect changes in the specified directory. For macOS, it utilizes the `FSEvents` API to monitor file system events such as file creation, deletion, and modification.

```cpp
class FileMonitor {
    // Implementation details for file monitoring using FSEvents API
};
```

### 2. File Sorting

When a new file is created in the monitored directory, the utility extracts its file extension and determines the appropriate destination folder based on predefined mappings.

```cpp
class DownloadHandler {
public:
    void onCreated(const std::filesystem::path &filePath) {
        // Extract file extension and determine destination folder
        // Move the file to the destination folder
    }
};
```

### 3. Threading

The file monitoring and sorting tasks are performed concurrently using threads to ensure efficient operation without blocking the main thread.

```cpp
void monitorDirectory(const std::string &downloadPath, DownloadHandler &handler) {
    // Continuously monitor the directory for new files
    // Invoke the handler when new files are detected
}
```

### 4. Main Function

In the main function, the user specifies the directory to monitor, initializes the `DownloadHandler`, and starts the monitoring thread.

```cpp
int main() {
    // Specify the directory to monitor
    std::string downloadPath = "/path/to/your/download/directory";

    // Initialize the DownloadHandler
    DownloadHandler handler(downloadPath);

    // Start the monitoring thread
    std::thread monitorThread(monitorDirectory, downloadPath, std::ref(handler));

    // Wait for the monitoring thread to finish
    monitorThread.join();

    return 0;
}
```

## Example Usage

```cpp
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>

// Include the necessary classes and functions here...

int main() {
    // Specify the directory to monitor
    std::string downloadPath = "/Users/username/Downloads";

    // Initialize the DownloadHandler
    DownloadHandler handler(downloadPath);

    // Start the monitoring thread
    std::thread monitorThread(monitorDirectory, downloadPath, std::ref(handler));

    // Wait for the monitoring thread to finish
    monitorThread.join();

    return 0;
}
```

## Dependencies

- C++17 compiler with filesystem library support
- macOS operating system (for the provided example)

## Customization

- Modify the `extensionToFolders` mapping in the `DownloadHandler` class to define custom mappings between file extensions and destination folders.
- Ensure proper permissions are granted to access the monitored directory.

## Disclaimer

This utility is provided as-is without any warranty. Use it at your own risk. Chances of failure or file damage.
