#include "filesystem.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

FileSystem *mapFileSystem(char *diskFile)
{
    if (diskFile == NULL) {
        return NULL;
    }

    // ----------------
    // Use mmap system call to map the file into memory.
    // ----------------

    return NULL;
}

static OpenFileHandle *_openFileAtBlock(FileSystem *fs, uint32_t blockIndex,
    uint32_t length)
{
    assert(fs != NULL);
    assert(blockIndex < FILE_SYSTEM_BLOCKS);

    OpenFileHandle *handle = malloc(sizeof(OpenFileHandle));
    if (handle == NULL) {
        return NULL;
    }

    handle->fileSystem        = fs;
    handle->currentBlock      = blockIndex;
    handle->currentFileOffset = 0;
    handle->length            = length;

    return handle;
}

static int _hasMoreBytes(OpenFileHandle *handle)
{
    assert(handle != NULL);
    assert(handle->currentFileOffset <= handle->length);

    (void)handle;

    // ----------------
    // Check if there are more bytes to read in the file.
    // ----------------

    return 0;
}

OpenFileHandle *openFile(FileSystem *fs, char *name)
{
    if ((fs == NULL) || (name == NULL)) {
        return NULL;
    }

    // Open the root directory file.
    OpenFileHandle *root = _openFileAtBlock(fs, ROOT_DIRECTORY_BLOCK,
                                            fs->rootDirectorySize);
    if (root == NULL) {
        return NULL;
    }

    // ----------------
    // Find the directory entry with that name.
    // You can use readFile to read from the directory stream.
    // ----------------

    closeFile(root);

    // ----------------
    // Return a file handle if the file could be found.
    // ----------------
    return NULL;
}

void closeFile(OpenFileHandle *handle)
{
    if (handle == NULL) {
        return;
    }

    // Since we opened the file system with read access only, we do not have
    // any pending modifications that might need to be written back to the file
    // prior closing. Hence, we can just free the handle and call it a day.
    free(handle);
}

static char _readFileByte(OpenFileHandle *handle)
{
    assert(handle != NULL);
    assert(_hasMoreBytes(handle));
    assert(handle->fileSystem != NULL);
    assert(handle->currentBlock < FILE_SYSTEM_BLOCKS);

    // ----------------
    // Read a byte from the file. This should never fail, because the function
    // must not be called if there are not more bytes to read.
    // ----------------

    return 0;
}

// This acts like the default linux read() system call on your file.
int readFile(OpenFileHandle *handle, char *buffer, int length)
{
    if ((handle == NULL) || (buffer == NULL)) {
        return -1;
    }

    int n = 0;
    while ((n < length) && _hasMoreBytes(handle)) {
        buffer[n] = _readFileByte(handle);

        ++n;
    }

    return n;
}