import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
import os
import shutil

class DownloadHandler(FileSystemEventHandler):
    def __init__(self, download_path):
        self.download_path = download_path

    def on_created(self, event):
        if not event.is_directory:
            file_path = event.src_path
            self.process_file(file_path)

    def process_file(self, file_path):
        _, extension = os.path.splitext(file_path)
        extension : str = extension.lower()
        
        self.extension_to_folders = extension.upper().split('.')[1] + "Files"

        destination_folder = os.path.join(self.download_path, self.extension_to_folders)

        if not os.path.exists(destination_folder):
            os.makedirs(destination_folder)

        destination_path = os.path.join(destination_folder, os.path.basename(file_path))

        shutil.move(file_path, destination_path)
        print(f"Moved file: {file_path} to: {destination_path}")

def main():
    download_path = "/Users/anshumantiwari/Documents/CODES/C++/"  # Change this to the path of your download directory

    event_handler = DownloadHandler(download_path)
    
    observer = Observer()
    observer.schedule(event_handler, path=download_path, recursive=False)
    observer.start()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()

    observer.join()

if __name__ == "__main__":
    main()
