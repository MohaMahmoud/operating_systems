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
if (diskFile == NULL) return NULL;

    // 1. Datei öffnen, um einen Dateideskriptor zu erhalten
    int fd = open(diskFile, O_RDONLY);
    if (fd < 0) return NULL;

    // 2. Dateigröße ermitteln (notwendig für mmap)
    struct stat st;
    if (fstat(fd, &st) < 0) {
        close(fd);
        return NULL;
    }

    // 3. Datei in den Adressraum mappen
    // PROT_READ: Erlaubt lesenden Zugriff
    // MAP_SHARED: Änderungen (falls erlaubt) werden in die Datei geschrieben
    void *map = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    
    // Dateideskriptor kann nach mmap geschlossen werden
    close(fd);

    if (map == MAP_FAILED) return NULL;

    // 4. Adresse auf die Zielstruktur casten und zurückgeben
    return (FileSystem *)map;   
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
    if (handle->currentFileOffset < handle->length) {
        return 1;
    }
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
    // 1. Offset innerhalb des aktuellen Blocks berechnen.
    // HINWEIS: Ersetze BLOCK_SIZE durch das Makro aus deiner filesystem.h 
    // (manchmal auch FS_BLOCK_SIZE o.ä. genannt).
    uint32_t blockOffset = handle->currentFileOffset % BLOCK_SIZE;

    // 2. Das Byte lesen. 
    // HINWEIS: Passe "dataRegion" an den echten Namen des Daten-Arrays in 
    // deiner FileSystem-Struktur an (z.B. fs->dataBlocks, fs->blocks etc.)
    char *data = (char *)handle->fileSystem->dataRegion;
    char byteRead = data[(handle->currentBlock * BLOCK_SIZE) + blockOffset];

    // 3. Den Offset für den nächsten Lesezugriff erhöhen.
    handle->currentFileOffset++;

    // 4. FAT-Lookup: Wenn wir durch das Erhöhen exakt die Grenze eines Blocks 
    // überschritten haben UND noch weitere Bytes in der Datei folgen, 
    // updaten wir currentBlock auf den nächsten Block in der FAT.
    if ((handle->currentFileOffset % BLOCK_SIZE == 0) && _hasMoreBytes(handle)) {
        handle->currentBlock = handle->fileSystem->fat[handle->currentBlock];
    }

    return byteRead;
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