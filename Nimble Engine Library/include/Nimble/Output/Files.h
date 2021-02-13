#include "../NimbleLicense.h"
/*
 * Files.h
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-12-07.
 * Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
 *
 */

/**
 * @file Files.h
 * @author Avery Aaron
 * @copyright
 * @parblock
 * The MIT License (MIT)
 * Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * @endparblock
 * @date 2020-12-07
 *
 * @brief This class defines file functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_FILES_H
#define NIMBLE_ENGINE_FILES_H /**< Header definition */

#include "../Nimble.h"

#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#if NIMBLE_OS == NIMBLE_WINDOWS
#include <direct.h>
#include <io.h>
#include <process.h>
#include <Windows.h>

#elif defined(NIMBLE_STD_UNIX)
#include <unistd.h>
#endif


#ifndef NFILE_BUFFER_SIZE
#  define NFILE_BUFFER_SIZE 1024
#endif

#if !defined(PATH_MAX) && defined(MAX_PATH)
#  define PATH_MAX MAX_PATH
#endif

#if NIMBLE_OS == NIMBLE_WINDOWS
#  define NFILE_DIR_SEP '\\'
#else
#  define NFILE_DIR_SEP '/'
#endif

#if NIMBLE_OS == NIMBLE_WINDOWS
/* access() args */
#  ifndef R_OK
#    define R_OK 4 /* Test for read permission.  */
#  endif
#  ifndef W_OK
#    define W_OK 2 /* Test for write permission.  */
#  endif
#  ifndef X_OK
#    define X_OK 1 /* Test for execute permission (unsupported in Windows). */
#  endif
#  ifndef F_OK
#    define F_OK 0 /* Test for existence.  */
#  endif

/* open() args */
#  ifndef O_RDONLY
#    define O_RDONLY _O_RDONLY
#  endif
#  ifndef O_WRONLY
#    define O_WRONLY _O_WRONLY
#  endif
#  ifndef O_RDWR
#    define O_RDWR _O_RDWR
#  endif
#  ifndef O_APPEND
#    define O_APPEND _O_APPEND
#  endif
#  ifndef O_CREAT
#    define O_CREAT _O_CREAT
#  endif
#  ifndef O_TRUNC
#    define O_TRUNC _O_TRUNC
#  endif
#  ifndef O_EXCL
#    define O_EXCL _O_EXCL
#  endif
#  ifndef O_BINARY
#    define O_BINARY _O_BINARY
#  endif
#  ifndef O_TEXT
#    define O_TEXT _O_TEXT
#  endif

#  ifndef S_IREAD
#    define S_IREAD _S_IREAD
#  endif
#  ifndef S_IWRITE
#    define S_IWRITE _S_IWRITE
#  endif
#  ifndef S_IEXEC
#    define S_IEXEC _S_IEXEC
#  endif

/* Functions */
#  ifndef access
#    define access _access
#  endif
#  ifndef dup2
#    define dup2 _dup2
#  endif
#  ifndef execve
#    define execve _execve
#  endif
#  ifndef ftruncate
#    define ftruncate _chsize
#  endif
#  ifndef unlink
#    define unlink _unlink
#  endif
#  ifndef fileno
#    define fileno _fileno
#  endif
#  ifndef getcwd
#    define getcwd _getcwd
#  endif
#  ifndef chdir
#    define chdir _chdir
#  endif
#  ifndef isatty
#    define isatty _isatty
#  endif
#  ifndef lseek
#    define lseek _lseek
#  endif
#  ifndef realpath
#    define realpath(path, rltvPath) _fullpath(path, rltvPath, PATH_MAX)
#  endif
#  ifndef popen
#    define popen _popen
#endif
/** @note Sockets are not files in Windows. Use network functions. */
#  ifndef read
#    define read _read
#  endif
#  ifndef write
#    define write _write
#  endif

/* Standard file descriptors */
#  ifndef STDIN_FILENO
#    define STDIN_FILENO  0
#  endif
#  ifndef STDOUT_FILENO
#    define STDOUT_FILENO 1
#  endif
#    ifndef STDERR_FILENO
#    define STDERR_FILENO 2
#  endif
#endif

/* File flags */
enum nFileFlags {
    NFILE_F_READ = O_RDONLY, /**< Open for reading. */
    NFILE_F_WRITE = O_RDWR, /**< Open for writing. */

    NFILE_F_CREATE = O_CREAT, /**< Create the file if it doesn't exist. */
    NFILE_F_CREATE_IF_NEEDED = NFILE_F_CREATE, /**< Create the file if it doesn't exist. */
    NFILE_F_CREATE_CHECK = O_CREAT | O_EXCL, /**< Create the file or fail if it exists. */

    NFILE_F_APPEND = O_APPEND, /**< Start writing at the end of the file. */
    NFILE_F_CLEAR = O_TRUNC, /**< Clears the file's data when opening. */
    NFILE_F_RAW = O_BINARY, /**< Open file in binary mode (raw data transfer). */
    NFILE_F_TEXT = O_TEXT /**< Open file in text mode (translations like newline characters). */
};

/**
 * @brief The executable file path.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
char NEXEC[PATH_MAX + 1];

/**
 * @brief The length of the executable file path.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
size_t NEXEC_LEN;

/**
 * @brief The current working directory.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
char NCWD[PATH_MAX + 1];

/**
 * @brief The length of the current working directory.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
size_t NCWD_LEN;


/**
 * @brief Opens file @p path with @p flags.
 *
 * @param[in] file The file path of the file to open.
 * @param[in] flags The flags for the file opening. See #nFileFlags.
 * @param[out] fd The file descriptor to be set.
 * @return #NSUCCESS is returned if the file exists; otherwise an error code is
 * returned.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int nFileOpen(const char *const restrict file,
              int flags,
              int *restrict fd);


/**
 * @brief Closes file @p path.
 *
 * @param[in,out] fd The file descriptor to close.
 * @return #NSUCCESS is returned if the file exists; otherwise an error code is
 * returned.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int nFileClose(int *fd);

/**
 * @brief Reads up to @p size bytes from @p fd.
 * 
 * @param[in] fd The file descriptor to read from.
 * @param[out] dst The buffer to read into.
 * @param[in] size The maximum number of bytes to read.
 * @return Returns the number of successfully read bytes, or -1 if an error
 * occurs.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
ssize_t nFileRead(const int fd,
                  void *dst,
                  const size_t size);

/**
 * @brief Writes up to @p size bytes to @p fd.
 * 
 * @param[in] fd The file descriptor to write to.
 * @param[out] src The buffer to write from.
 * @param[in] size The number of bytes to write.
 * @return Returns the number of successfully written bytes, or -1 if an error
 * occurs.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
ssize_t nFileWrite(const int fd,
                   void *src,
                   const size_t size);

/**
 * @brief Deletes file @p file.
 * 
 * @param[in] file The file path of the file to delete.
 * @return #NSUCCESS is returned if successful; otherwise an error is returned.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int nFileDelete(const char *const file);

/**
 * @brief Renames @p oldPath to @p newPath.
 * 
 * @param[in] oldPath The current file path of the file to rename.
 * @param[in] newPath The new file path to rename @p oldPath to.
 * @return #NSUCCESS is returned if successful; otherwise an error is returned.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int nFileRename(const char *const restrict oldPath,
                const char *const restrict newPath);

/**
 * @brief Moves @p oldPath to @p newPath.
 * 
 * @param[in] oldPath The current file path of the file to move.
 * @param[in] newPath The new file path to move @p oldPath to.
 * @return #NSUCCESS is returned if successful; otherwise an error is returned.
 */
#define nFileMove nFileRename

/**
 * @brief Checks if a file exists.
 *
 * @param[in] file The file path of the file to check.
 * @return #NSUCCESS is returned if the file exists; otherwise an error code is
 * returned.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int nFileExists(const char *const file);

/**
 * @brief Checks if the file is an absolute path.
 *
 * @param[in] path The file path to check if absolute.
 * @param[in] len The length of the path to check. This can be 0 to use
 * strlen().
 * @return #NSUCCESS is returned if successful; otherwise -1 or an error is returned.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int nFilePathIsAbsolute(const char *const path,
                        size_t len);

/**
 * @brief Gets the current working directory path.
 * Gets the current working directory path and sets #NCWD and
 * #NCWD_LEN.
 *
 * @return #NCWD is returned if successful; otherwise the
 * engine crashes.
 * @note This function is not thread safe, as it is called during
 * initialization.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
char *
nFileSetCWD(void);

/**
 * @brief Gets the current executable file path.
 * Gets the current executable file path and sets #NEXEC and
 * #NEXEC_LEN.
 *
 * @return #NEXEC is returned if successful; otherwise the
 * engine crashes.
 *
 * @note This function is not thread safe, as it is called during
 * initialization.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
char *
nFileSetExecutablePath(void);

/**
 * @brief Copies @p src to @p dst.
 *
 * @param[in] src The file path of the source file to copy from.
 * @param[in] dst The file path of the destination file to copy to.
 * @return #NSUCCESS is returned if successful; otherwise an error is returned.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int nFileCopy(const char *const restrict src,
              const char *const restrict dst);

#endif // NIMBLE_ENGINE_FILES_H

#ifdef __cplusplus
}
#endif

// Files.h
