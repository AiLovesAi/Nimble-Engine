/*
 *  Nimble Engine Example.c
 *  C 3D Game Base
 *
 *  Created by Avery Aaron on 8/9/19.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

/* COMPILE CONFIG */

#define EMERGENCY_MEMORY         5000UL // Bytes to be freed in case memory limit is reached
#define ALLOCATED_MEMORY_MINIMUM 50000000UL // Minimum amount of memory in bytes to be allocated before using the default
#define ALLOCATED_MEMORY_DEFAULT 100000000UL // Default amount of memory in bytes to be allocated
#define CRASH_WAIT_TIME          (5 * MILLIS_PER_SEC) // Time to wait for other threads when crashing.

#define GAME_TITLE   "Nimble Example"
#define GAME_VERSION "0.1.0"

#define GAME_TPS_MAX             200 // Maximum ticks per second
#define GAME_MOVEMENT_EVENT_TIME 50 // Maximum movement events per second
#define FPS_MINIMUM              5 // Minimum fps before crash
#define VIEW_DISTANCE_MIN        0.001f
#define VIEW_DISTANCE_MAX        100.0f
#define MOVEMENT_SPEED           0.00025f
#define SPRINT_MULTIPLIER        3.0f // How many times as fast to move when sprinting
#define SENSITIVITY_MIN          0.001f * M_DEG_TO_RAD // Minimum sensitivity, percentage of maximum sensitivity
#define SENSITIVITY_MAX          1.5f * M_DEG_TO_RAD // Maximum sensitivity in degrees per pixel cursor has moved

#define KEY_QUIT_DEFAULT       GLFW_KEY_ESCAPE
#define KEY_DEBUG_DEFAULT      GLFW_KEY_F1
#define KEY_FULLSCREEN_DEFAULT GLFW_KEY_F2
#define KEY_LOG_TEST_DEFAULT   GLFW_KEY_F3
#define KEY_FORWARD_DEFAULT    GLFW_KEY_W
#define KEY_BACKWARD_DEFAULT   GLFW_KEY_S
#define KEY_LEFT_DEFAULT       GLFW_KEY_A
#define KEY_RIGHT_DEFAULT      GLFW_KEY_D
#define KEY_SPRINT_DEFAULT     GLFW_KEY_LEFT_SHIFT

//Option defaults
#define    DEBUG_DEFAULT                    0
const char DEBUG_DEFAULT_STRING[]         = "0";
#define    FULLSCREEN_DEFAULT               0
const char FULLSCREEN_DEFAULT_STRING[]    = "0";
#define    SENSITIVITY_DEFAULT              0.5f
const char SENSITIVITY_DEFAULT_STRING[]   = "0.5f";
#define    RESOLUTION_DEFAULT               0.5f
const char RESOLUTION_DEFAULT_STRING[]    = "0.5";
#define    FOV_DEFAULT                      90.0f
const char FOV_DEFAULT_STRING[]           = "90.0";
#define    VOLUME_MASTER_DEFAULT            1.0f
const char VOLUME_MASTER_DEFAULT_STRING[] = "1.0";



/* INCLUDES */

#if defined(_WIN32)
#include <cglm/cglm.h>
#include <errno.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <windows.h>
#elif defined(__linux__)
#include <cglm/cglm.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <limits.h>
#include <math.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <unistd.h>
#elif defined(__APPLE__)
#include <cglm/cglm.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <limits.h>
#include <mach-o/dyld.h>
#include <math.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <unistd.h>
#endif

#include "NimbleBigNumber.h"
#include "NimbleError.h"
#include "NimbleFileManager.h"
#include "NimbleInput.h"
#include "NimbleMath.h"
#include "NimbleTime.h"
#include "NimbleLogger.h"
#include "NimbleSystemInfo.h"
#include "NimbleWorldObjects.h"

/* GLOBAL DEFINITIONS */
#ifndef NULL
#define NULL (void *) 0
#endif
#ifndef ptrSize
#define ptrSize sizeof(NULL)
#endif
#define NULL_CHAR (char) '\0'

#define FORMAT_LENGTH_2 2 // In printf format where t = type: "%t"
#define FORMAT_LENGTH_4 4 // In printf format where t = type and x = forced digits: "%xxt"


/* FUNCTION DECLARATIONS */
#define FUNCTION_GETTIMEOFDAY 1
#define FUNCTION_FWRITE       2
#define FUNCTION_RENAME       3
static void catchFunctionError(uint8_t function);


/* GLOBAL VARIABLES */

// TODO Encode shaders (and other necessary strings) so they aren't visible and editable in the application file
const char * vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"layout (location = 1) in vec2 tex;\n"
"uniform mat4 model;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"out vec2 texPos;\n"
"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(pos, 1.0f);\n"
"    texPos = tex;\n"
"}";
const char * fragmentShaderSource =
"#version 330 core\n"
"in vec2 texPos;\n"
"uniform sampler2D tex;"
"out vec4 color;\n"
"void main()\n"
"{\n"
"    color = texture(tex, texPos);\n"
"}";

extern int (*__errno(void));

void * emergencyMemory = NULL;

// Thread variables
volatile uint8_t running       = 0;
volatile uint8_t crashed       = 0;
volatile uint8_t activeThreads = 0;


// Game options
volatile uint8_t debug                  = DEBUG_DEFAULT;
volatile uint8_t fullscreen             = FULLSCREEN_DEFAULT;
volatile uint8_t windowShouldFullscreen = 0;
volatile uint8_t windowResized          = 1;
volatile float   sensitivity            = SENSITIVITY_DEFAULT;
volatile float   resolution             = RESOLUTION_DEFAULT;

volatile float volumeMaster = VOLUME_MASTER_DEFAULT;

volatile float fov = FOV_DEFAULT;


// Files
char *     executableDirectory       = NULL;
size_t     executableDirectoryLength = 0;
FILE *     logFile                   = NULL;
const char tempFileSuffix[]          = ".tmp";
const char optionsFileName[]         = "options.txt";
char *     optionsFilePath           = NULL;
size_t     optionsFilePathLength     = 0;

// Info
char *  cpuID                 = NULL;
uint8_t logicalProcessorCount = 0;
char *  graphicsCardInfo               = NULL;

// Memory
uint64_t memoryAllocated = 0;


// OpenGL
GLFWwindow * window            = NULL;
GLuint       frameBuffer       = 0;
GLuint       colorBuffer       = 0;
GLuint       depthBuffer       = 0;
GLuint       shaderProgram     = 0;
mat4         model             = {};
mat4         view              = {};
mat4         projection        = {};
GLuint       uniformModel      = 0;
GLuint       uniformView       = 0;
GLuint       uniformProjection = 0;

const versor emptyVersor = {0.0f, 0.0f, 0.0f, 1.0f};

vec3 cameraPitchAxis       = {1.0f, 0.0f, 0.0f};
vec3 cameraYawAxis         = {0.0f, 1.0f, 0.0f};
vec3 cameraRollAxis        = {0.0f, 0.0f, 1.0f};
vec3 cameraPosition        = {};
vec3 cameraAngles          = {};
vec3 cameraAngleDifference = {};
versor cameraOrientation   = {0.0f, 0.0f, 0.0f, 1.0f};

const unsigned int indices[] = {
    1, 3, 2,
    0, 1, 2,
    0, 1, 4,
    2, 3, 4,
    1, 3, 4,
    0, 2, 4
};
const float vertices[] = {
//    x      y     z      u     v
    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
    0.0f,  -1.0f, 1.0f,  0.5f, 0.0f,
    0.0f,  -1.0f, -1.0f, 0.0f, 0.5f,
    1.0f,  -1.0f, 0.0f,  1.0f, 0.0f,
    0.0f,  0.5f,  0.0f,  0.5f, 1.0f
};


// Threads
#if defined(WIN32)
uint32_t tickThread  = 0;
uint32_t soundThread = 0;
uint32_t eventThread = 0;
#else
pthread_t tickThread  = 0;
pthread_t soundThread = 0;
pthread_t eventThread = 0;
#endif


// Game input
volatile uint16_t pointerDifferenceX = 0;
volatile uint16_t pointerDifferenceY = 0;
volatile float    previousPointerX   = 0;
volatile float    previousPointerY   = 0;

volatile uint32_t screenWidth  = 0;
volatile uint32_t screenHeight = 0;
volatile uint16_t refreshRate  = 0;

volatile uint32_t windowX          = 0;
volatile uint32_t windowY          = 0;
volatile uint32_t windowWidth      = 0;
volatile uint32_t windowHeight     = 0;
volatile int32_t  prevWindowX      = 0;
volatile int32_t  prevWindowY      = 0;
volatile int32_t  prevWindowWidth  = 0;
volatile int32_t  prevWindowHeight = 0;
volatile uint16_t frameWidth       = 0;
volatile uint16_t frameHeight      = 0;

// Keys
volatile uint16_t KEY_QUIT       = KEY_QUIT_DEFAULT;
volatile uint16_t KEY_DEBUG      = KEY_DEBUG_DEFAULT;
volatile uint16_t KEY_FULLSCREEN = KEY_FULLSCREEN_DEFAULT;
volatile uint16_t KEY_LOG_TEST   = KEY_LOG_TEST_DEFAULT;
volatile uint16_t KEY_FORWARD    = KEY_FORWARD_DEFAULT;
volatile uint16_t KEY_BACKWARD   = KEY_BACKWARD_DEFAULT;
volatile uint16_t KEY_LEFT       = KEY_LEFT_DEFAULT;
volatile uint16_t KEY_RIGHT      = KEY_RIGHT_DEFAULT;
volatile uint16_t KEY_ROLL_LEFT  = GLFW_KEY_Q;
volatile uint16_t KEY_ROLL_RIGHT = GLFW_KEY_E;
volatile uint16_t KEY_SPRINT     = KEY_SPRINT_DEFAULT;


/* ERROR HANDLING / LOGGING */

// Forcefully stops the program and attempts to log error to the console and/or the log file.
static void crash(const char * error)
{
    
    if (crashed)
    {
        raise(SIGTERM);
    }
    
    crashed = 1;
    running = 0;
    
    free(emergencyMemory); // NOTE: In case of no memory, just to be sure it has enough to run the crash sequence.
    
    activeThreads--; // Closing this thread.
    const struct timeval threadCloseWaitTime = nimbleTimeSetTimerMillis(3 * MILLIS_PER_SEC);
    
    while (!nimbleTimeHasPast(threadCloseWaitTime) && activeThreads)
    {
        nimbleTimeSleepMillis(100); // Wait 3 seconds or until threads are closed.
    }
    
    const char crashTimePrefix[] = "\n\n[%02d-%02d-%04d %02d:%02d:%02d +%06d] ";
    const char crashReport[]     = "A fatal error occurred causing " GAME_TITLE " version " GAME_VERSION " to crash.\n"
    "Please research this error to find if any fixes are readily available. "
    "If you cannot find a solution using the corresponding error message and code, "
    "submit a help ticket at [website with help ticket].\n"
    "Here is the error that caused the crash:\n";
    const char crashNewLines[]   = "\n\n";
    
    struct timeval tv = {};
    size_t crashTimePrefixFormattedLength = (sizeof(crashNewLines) -
                                             sizeof(NULL_CHAR)); // NOTE: In case gettimeofday fails, "\n\n".
    
    if (!gettimeofday(&tv, NULL))
    {
        crashTimePrefixFormattedLength = ((sizeof(crashTimePrefix) -
                                           sizeof(NULL_CHAR) - (FORMAT_LENGTH_4 * 7)) +
                                          TM_DIGITS_MONTH + TM_DIGITS_DAY + TM_DIGITS_YEAR + TM_DIGITS_HOUR +
                                          TM_DIGITS_MINUTE + TM_DIGITS_SECOND + TM_DIGITS_MICROSECOND);
        // NOTE: FORMAT_LENGTH_4 * 7 for the 7 inputs to properly allocate memory.
    }
    
    const struct tm * gmNow = gmtime(&tv.tv_sec);
    
    const size_t errorLength         = strlen(error);
    const size_t outputLength        = (crashTimePrefixFormattedLength +
                                        (sizeof(crashReport) - sizeof(NULL_CHAR)) + errorLength +
                                        (sizeof(crashNewLines) - sizeof(NULL_CHAR)) + sizeof(NULL_CHAR));
    size_t       currentOutputLength = sizeof(NULL_CHAR);
    char *       output              = malloc(ptrSize + outputLength);
    
    if (!output)
    {
        crash("Ran out of memory.");
    }
    
    output[0] = NULL_CHAR;
    
    if (crashTimePrefixFormattedLength != (sizeof(crashNewLines) -
                                           sizeof(NULL_CHAR)))
    {
        snprintf(output, outputLength, crashTimePrefix,
                 (gmNow->tm_mon + TM_DIF_MONTH),gmNow->tm_mday, (gmNow->tm_year + TM_DIF_EPOCH),
                 gmNow->tm_hour, gmNow->tm_min, gmNow->tm_sec, tv.tv_usec);
        currentOutputLength += crashTimePrefixFormattedLength;
    } else
    {
        strncat(output, crashNewLines, (outputLength - currentOutputLength));
        currentOutputLength += (sizeof(crashNewLines) - sizeof(NULL_CHAR));
    }
    
    strncat(output, crashReport, (outputLength - currentOutputLength));
    currentOutputLength += (sizeof(crashReport) - sizeof(NULL_CHAR));
    strncat(output, error, (outputLength - currentOutputLength));
    currentOutputLength += errorLength;
    strncat(output, crashNewLines, (outputLength - currentOutputLength));
    // TODO System info
    
    fputs(output, stderr);
    
    if (logFile)
    {
        fputs(output, logFile);
        fclose(logFile);
        
        const char   crashReportName[]     = "crash.txt";
        const size_t crashReportPathLength = (sizeof(crashReportName) -
                                              sizeof(NULL_CHAR) + executableDirectoryLength + sizeof(NULL_CHAR));
        char *       crashReportPath       = malloc(ptrSize + crashReportPathLength);
        
        if (crashReportPath)
        {
            snprintf(crashReportPath, crashReportPathLength, "%s%s", executableDirectory, crashReportName);
            FILE * crashReportFile = fopen(crashReportPath, "wb");
            
            if (crashReportFile)
            {
                fputs(output, crashReportFile);
                fclose(crashReportFile);
            }
            
        }
        
    }
    
    if (window)
    {
        glfwDestroyWindow(window);
        window = NULL;
        glfwTerminate();
    }
    
    if (executableDirectory)
    {
        nimbleMemoryFree(executableDirectory, executableDirectoryLength + sizeof(NULL_CHAR));
        executableDirectory = NULL;
    }
    
    if (optionsFilePath)
    {
        nimbleMemoryFree(optionsFilePath, optionsFilePathLength + sizeof(NULL_CHAR));
        optionsFilePath = NULL;
    }
    
    if (cpuID)
    {
        nimbleMemoryFree(cpuID, strlen(cpuID) + sizeof(NULL_CHAR));
        cpuID = NULL;
    }
    
    while (objectCount)
    {
        nimbleObjectDestroy(0);
    }
    
    while (textureCount)
    {
        nimbleTextureUnload(0);
    }
    
    exit(EXIT_FAILURE);
}

// Catches errors caused by external functions and crashes with a corresponding error message.
static void catchFunctionError(uint8_t function)
{
    
    switch (function)
    {
            
        case FUNCTION_GETTIMEOFDAY:
        {
            
            switch (errno)
            {
                    
                case EFAULT:
                {
                    crash("Failed to run gettimeofday() because one of tv or tz pointed outside the accessible address space.");
                }
                break;
                    
                default:
                {
                    crash("Failed to run gettimeofday().");
                }
                break;
                    
                    
            }
            
        }
        break;
            
            
        case FUNCTION_FWRITE:
        {
            
            switch (errno)
            {
                    
                case EAGAIN:
                {
                    crash("Could not write to file because the O_NONBLOCK flag is set for the file descriptor underlying stream and the process would be delayed in the write operation.");
                }
                break;
                    
                    
                case EBADF:
                {
                    crash("Could not write to file because the file descriptor underlying stream is not a valid file descriptor open for writing.");
                }
                break;
                    
                case EFBIG:
                {
                    crash("Could not write to file because an attempt was made to write to a file that exceeds the maximum file size or the process' file size limit.");
                }
                break;
                    
                case EINTR:
                {
                    crash("Could not write to file because the write operation was terminated due to the receipt of a signal, and no data was transferred");
                }
                break;
                    
                case EIO:
                {
                    crash("Could not write to file because a physical I/O error has occurred, or the process is a member of a background process group attempting to write to its controlling terminal, TOSTOP is set, the process is neither ignoring nor blocking SIGTTOU and the process group of the process is orphaned. This error may also be returned under implementation-dependent conditions.");
                }
                break;
                    
                case ENOSPC:
                {
                    crash("Could not write to file because there was no free space remaining on the device containing the file.");
                }
                break;
                    
                case EPIPE:
                {
                    crash("Could not write to file because an attempt is made to write to a pipe or FIFO that is not open for reading by any process. A SIGPIPE signal will also be sent to the thread.");
                }
                break;
                    
                case ENXIO:
                {
                    crash("Could not write to file because a request was made of a non-existent device, or the request was outside the capabilities of the device.");
                }
                break;
                    
                case ENOMEM:
                    crash("Ran out of memory.");
                break;
                    
                default:
                {
                    crash("Could not write to file.");
                }
                break;
                    
            }
            
        }
        break;
            
        case FUNCTION_RENAME:
        {
            
            switch (errno)
            {
                    
                case EACCES:
                {
                    crash("Could not rename file because a component of either path prefix denies search permission; or one of the directories containing old or new denies write permissions; or write permission is required and is denied for a directory pointed to by the old or new arguments.");
                }
                break;
                    
                case EBUSY:
                {
                    crash("Could not rename file because the directory named by old or new is currently in use by the system or another process, and the implementation considers this an error; or the file named by the old or new arguments is a named STREAM.");
                }
                break;
                    
                case EEXIST:
                {
                    crash("Could not rename file because the link named by new is a directory that is not an empty directory.");
                }
                break;
                    
                case ENOTEMPTY:
                {
                    crash("Could not rename file because the link named by new is a directory that is not an empty directory.");
                }
                break;
                    
                case EINVAL:
                {
                    crash("Could not rename file because the new directory pathname contains a path prefix that names the old directory.");
                }
                break;
                    
                case EIO:
                {
                    crash("Could not rename file because a physical I/O error has occurred.");
                }
                break;
                    
                case EISDIR:
                {
                    crash("Could not rename file because the new argument points to a directory and the old argument points to a file that is not a directory.");
                }
                break;
                    
                case ELOOP:
                {
                    crash("Could not rename file because the file named by old is a directory, and the link count of the parent directory of new would exceed {LINK_MAX}; or more than {SYMLOOP_MAX} symbolic links were encountered during resolution of the path argument.");
                }
                break;
                    
                case ENAMETOOLONG:
                {
                    crash("Could not rename file because the length of the old or new argument exceeds {PATH_MAX} or a pathname component is longer than {NAME_MAX}; or as a result of encountering a symbolic link in resolution of the path argument, the length of the substituted pathname string exceeded {PATH_MAX}.");
                }
                break;
                    
                case ENOENT:
                {
                    crash("Could not rename file because the link named by old does not name an existing file, or either old or new points to an empty string.");
                }
                break;
                    
                case ENOSPC:
                {
                    crash("Could not rename file because the directory that would contain new cannot be extended.");
                }
                break;
                    
                case ENOTDIR:
                {
                    crash("Could not rename file because a component of either path prefix is not a directory; or the old argument names a directory and new argument names a non-directory file.");
                }
                break;
                    
                case EPERM:
                {
                    crash("Could not rename file because the S_ISVTX flag is set on the directory containing the file referred to by old and the caller is not the file owner, nor is the caller the directory owner, nor does the caller have appropriate privileges; or new refers to an existing file, the S_ISVTX flag is set on the directory containing this file, and the caller is not the file owner, nor is the caller the directory owner, nor does the caller have appropriate privileges.");
                }
                break;
                    
                case EROFS:
                {
                    crash("Could not rename file because the requested operation requires writing in a directory on a read-only file system.");
                }
                break;
                    
                case EXDEV:
                {
                    crash("Could not rename file because the links named by new and old are on different file systems and the implementation does not support links between file systems.");
                }
                break;
                    
                case ETXTBSY:
                {
                    crash("Could not rename file because the file to be renamed is a pure procedure (shared text) file that is being executed.");
                }
                break;
                    
                default:
                {
                    crash("Could not rename file.");
                }
                break;
                    
            }
            
        }
        break;
            
    }
    
}

// Crashes the game with a description of the signal raised, signum.
static void signalHandler(int signum)
{
    switch (signum)
    {
            
        case SIGSEGV:
        {
            crash("Caught invalid memory access signal (SIGSEGV).");
        }
        break;
            
        case SIGILL:
        {
            crash("Caught illegal instruction signal (SIGILL).");
        }
        break;
            
        case SIGABRT:
        {
            crash("Caught abort signal (SIGABRT).");
        }
        break;
            
        case SIGFPE:
        {
            crash("Caught floating point exception signal (SIGFPE).");
        }
        break;
            
#       if !defined(WIN32)
            
        case SIGPIPE:
        {
            crash("Caught broken pipe signal (SIGPIPE).");
        }
        break;
            
#       endif
            
        default:
        {
            crash("Caught unmanaged signal.");
        }
        break;
            
    }
    
}

// Gets data from a variable in a file.
static char * getVariable(const char * filePath, const char * location)
{
    FILE * file = fopen(filePath, "rb");
    // TODO
    fclose(file);
    return NULL;
}

// Writes data to a variable in a file
static void writeVariable(const char * filePath, const char * location, const char * data, const uint32_t size)
{
    const size_t filePathLength     = strlen(filePath);
    const size_t tempFilePathLength = (filePathLength + (sizeof(tempFileSuffix) - sizeof(NULL_CHAR)) + sizeof(NULL_CHAR));
    char *       tempFilePath       = malloc(ptrSize + tempFilePathLength);
    snprintf(tempFilePath, tempFilePathLength, "%s%s", filePath, tempFileSuffix);
    FILE * fileRead = fopen(filePath, "rb");
    
    if (!fileRead)
    {
        fileRead = fopen(filePath, "wb");
        
        if (!fileRead)
        {
            const char   crashMessage[]    = "Could not open the file \"%s\" for reading data.";
            const size_t crashOutputLength = ((sizeof(crashMessage) - FORMAT_LENGTH_2 - sizeof(NULL_CHAR)) + filePathLength + sizeof(NULL_CHAR));
            char *       crashOutput       = malloc(ptrSize + crashOutputLength);
            snprintf(crashOutput, crashOutputLength, crashMessage, filePath);
            crash(crashOutput);
        }
        
    }
    
    FILE * fileWrite = fopen(tempFilePath, "wb");
    
    if (!fileWrite)
    {
        const char   crashMessage[]    = "Could not create the file \"%s\" for writing data.";
        const size_t crashOutputLength = ((sizeof(crashMessage) - FORMAT_LENGTH_2 - sizeof(NULL_CHAR)) + tempFilePathLength);
        char *       crashOutput       = malloc(ptrSize + crashOutputLength);
        snprintf(crashOutput, crashOutputLength, crashMessage, tempFilePath);
        crash(crashOutput);
    }
    
    // TODO
    
    fclose(fileRead);
    fclose(fileWrite);
    
    if (rename(tempFilePath, filePath)) // NOTE: Overwrites file with new data.
    {
        catchFunctionError(FUNCTION_RENAME);
    }
    
}


// Logs GLFW errors.
static void glfwErrorHandler(const int errorCode, const char * errorDescription)
{
    const char   errorPrefix[]          = "GLFW Error caught (#%d): %s";
    const size_t errorDescriptionLength = strlen(errorDescription);
    const size_t entryLength            = (uint32_t) ((sizeof(errorPrefix) - (FORMAT_LENGTH_2 * 2) - sizeof(NULL_CHAR)) +
                                                      nimbleMathDigits32(errorCode) + errorDescriptionLength);
    char *       entry                  = nimbleMemoryAllocate(entryLength + sizeof(NULL_CHAR));
    
    snprintf(entry, (entryLength + sizeof(NULL_CHAR)), errorPrefix, errorCode, errorDescription);
    nimbleLoggerLog(logFile, entry, entryLength, ENTRY_TYPE_WARNING, 1);
    nimbleMemoryFree(entry, entryLength + sizeof(NULL_CHAR));
}

// Attempts to close the game or crashes if unsuccessful.
static inline void closeGame(void)
{
    running = 0;
    activeThreads--;
    
    nimbleTimeSleepMillis(0); // Give up thread priority.
    
    const struct timeval threadCloseWaitTime = nimbleTimeSetTimerMillis(CRASH_WAIT_TIME);
    
    while (!nimbleTimeHasPast(threadCloseWaitTime) && activeThreads)
    {
        nimbleTimeSleepMillis(100); // Wait 5 seconds or until threads are closed.
    }
    
    if (activeThreads)
    {
        crash("Could not close threads");
    }
    
    while (objectCount)
    {
        nimbleObjectDestroy(0);
    }
    
    while (textureCount)
    {
        nimbleTextureUnload(0);
    }
    
    glfwDestroyWindow(window);
    window = NULL;
    glfwTerminate();
    
    if (executableDirectory)
    {
        nimbleMemoryFree(executableDirectory, executableDirectoryLength + sizeof(NULL_CHAR));
        executableDirectory = NULL;
    }
    
    if (optionsFilePath)
    {
        nimbleMemoryFree(optionsFilePath, optionsFilePathLength + sizeof(NULL_CHAR));
        optionsFilePath = NULL;
    }
    
    if (cpuID)
    {
        nimbleMemoryFree(cpuID, strlen(cpuID) + sizeof(NULL_CHAR));
        cpuID = NULL;
    }
    
    if (nimbleMemoryUsed)
    {
        const char memoryLostString[] = "Memory lost during program execution: %lluB";
        const uint8_t memoryLostStringLength = (sizeof(memoryLostString) - FORMAT_LENGTH_4 - sizeof(NULL_CHAR)) + nimbleMathDigits64u(nimbleMemoryUsed);
        char * entry = malloc(ptrSize + memoryLostStringLength + sizeof(NULL_CHAR));
        snprintf(entry, (memoryLostStringLength + sizeof(NULL_CHAR)), memoryLostString, nimbleMemoryUsed);
        nimbleLoggerLog(logFile, entry, memoryLostStringLength, ENTRY_TYPE_WARNING, 1);
    }
    
    const char closeSuccessString[] = "Successfully closed " GAME_TITLE ".";
    nimbleLoggerLog(logFile, closeSuccessString, (sizeof(closeSuccessString) - sizeof(NULL_CHAR)), ENTRY_TYPE_INFO, 1);
    fclose(logFile);
    
    exit(EXIT_SUCCESS);
}

/* GAME INITIALIZATION/CALLBACKS */

// Initializes the log file and sets the executable directory.
static inline void initializeLogger(void)
{
    // Get executable directory
    executableDirectory = nimbleFileGetExecutableDirectory(&executableDirectoryLength);
    
    if (!executableDirectory)
    {
        crash("Could not get executable directory for logging.");
    }
    
    
    // Create log file
    const char   logFileName[]        = "log.txt";
    const size_t logPathLength        = executableDirectoryLength + (sizeof(logFileName) - sizeof(NULL_CHAR)) + sizeof(NULL_CHAR);
    char *       logPath              = nimbleMemoryAllocate(logPathLength);
    
    snprintf(logPath, logPathLength, "%s%s", executableDirectory, logFileName);
    logFile = fopen(logPath, "wb");
    nimbleMemoryFree(logPath, logPathLength);
    
    if (!logFile)
    {
        crash("Could not create log file.");
    }
    
    // Print OS name and MacOS
    const char gameLaunchedString[] = GAME_TITLE " version " GAME_VERSION " launched on %s in \"%s\".";
    uint8_t osStringLength = 0;
    char * osString = nimbleSystemGetOSString(&osStringLength);
    
    if (osString)
    {
        size_t entryLength = (sizeof(gameLaunchedString) - (FORMAT_LENGTH_2 * 2) - sizeof(NULL_CHAR)) + executableDirectoryLength + osStringLength;
        char * entry = nimbleMemoryAllocate(entryLength + sizeof(NULL_CHAR));
        snprintf(entry, entryLength + sizeof(NULL_CHAR), gameLaunchedString, osString, executableDirectory);
        nimbleMemoryFree(osString, osStringLength + sizeof(NULL_CHAR));
        nimbleLoggerLog(logFile, entry, entryLength, ENTRY_TYPE_PRINT, 1);
        nimbleMemoryFree(entry, entryLength + sizeof(NULL_CHAR));
    } else
    {
        const char versionNotFoundString[] = "Could not find OS version";
        nimbleLoggerLog(logFile, versionNotFoundString, (sizeof(versionNotFoundString) - sizeof(NULL_CHAR)), ENTRY_TYPE_WARNING, 1);
    }
    
}

// Gets and logs the system info.
static inline void logSystemInfo(void)
{
    uint8_t cpuIDLength = 0;
    cpuID = nimbleSystemGetCPUBrandString(&cpuIDLength);
    
    if (!cpuID)
    {
        const char cpuIDErrorString[] = "Could not get CPU ID.";
        nimbleLoggerLog(logFile, cpuIDErrorString, (sizeof(cpuIDErrorString) - sizeof(NULL_CHAR)), ENTRY_TYPE_WARNING, 1);
    }
    
    logicalProcessorCount = nimbleSystemGetLogicalProcessorCount();
    
    if (!logicalProcessorCount)
    {
        const char lpCountErrorString[] = "Could not get logical processor count.";
        nimbleLoggerLog(logFile, lpCountErrorString, (sizeof(lpCountErrorString) - sizeof(NULL_CHAR)), ENTRY_TYPE_WARNING, 1);
    }
    
    uint8_t graphicsCardInfoLength = 0;
    graphicsCardInfo = nimbleSystemGetGraphicsCardBrandString(&graphicsCardInfoLength);
    
    if (!graphicsCardInfo)
    {
        const char graphicsCardInfoErrorString[] = "Could not get GPU Info.";
        nimbleLoggerLog(logFile, graphicsCardInfoErrorString, (sizeof(graphicsCardInfoErrorString) - sizeof(NULL_CHAR)), ENTRY_TYPE_WARNING, 1);
    }
    
    char         systemInfo[] = "System info:\nCPU: %s\nLogical processors: %d\nGPU: %s\nAllocated memory: %dB";
    const size_t outputLength = ((sizeof(systemInfo) - sizeof(NULL_CHAR) - (FORMAT_LENGTH_2 * 4)) +
                                 cpuIDLength + nimbleMathDigits8u(logicalProcessorCount) + graphicsCardInfoLength +
                                 nimbleMathDigits64u(memoryAllocated));
    char *       output       = nimbleMemoryAllocate(outputLength + sizeof(NULL_CHAR));
    
    if (!output)
    {
        crash("Ran out of memory.");
    }
    
    snprintf(output, outputLength, systemInfo, cpuID, logicalProcessorCount, graphicsCardInfo, memoryAllocated);
    
    nimbleLoggerLog(logFile, output, outputLength, ENTRY_TYPE_INFO, 1);
    nimbleMemoryFree(output, outputLength + 1);
}


// Clears frame buffer data to prevent unwanted behavior when swapping buffers.
static inline void clearFrameBuffers(void)
{
    // NOTE: Clear buffer storage, swap buffers and do the same, swap back.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Handles GLFW event called when window moves on the screen.
static void onWindowMove(GLFWwindow * w, const int x, const int y)
{
    windowX = x;
    windowY = y;
}

// Handles GLFW event called when window is resized.
static void onWindowResize(GLFWwindow * w, const int width, const int height)
{
    windowResized = 1;
    windowWidth = width;
    windowHeight = height;
    
    if ((windowWidth > screenWidth) || (windowHeight > screenHeight)) // Different monitor
    {
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        
        if (mode)
        {
            if (windowWidth > screenWidth)
            {
                screenWidth = mode->width;
            }
            if (windowHeight > screenHeight)
            {
                screenHeight = mode->height;
            }
            refreshRate = mode->refreshRate;
        }
        
    }
    
    int32_t frameBufferWidth  = 0;
    int32_t frameBufferHeight = 0;
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
    glm_perspective_resize(((float) windowWidth / (float) windowHeight), projection);
    clearFrameBuffers();
}

// Sets the window to fullscreen if toFullscreen is true.
static void setFullscreen(uint8_t toFullscreen)
{
    
    if (toFullscreen)
    {
        int32_t width  = 0;
        int32_t height = 0;
        int32_t x      = 0;
        int32_t y      = 0;
        glfwGetWindowSize(window, &width, &height);
        glfwGetWindowPos(window, &x, &y);
        prevWindowWidth  = width;
        prevWindowHeight = height;
        prevWindowX      = x;
        prevWindowY      = y;
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, screenWidth, screenHeight, refreshRate);
    } else
    {
        glfwSetWindowMonitor(window, NULL, prevWindowX, prevWindowY, prevWindowWidth, prevWindowHeight, refreshRate);
    }
    
}

// Handles GLFW event called when the window is switches into or out of focus.
static void onWindowFocus(GLFWwindow * w, const int isFocused)
{
    
    if (isFocused)
    {
        // Resume game.
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        if (fullscreen)
        {
            setFullscreen(fullscreen);
        }
        
    } else
    {
        // Stop animations, sounds, etc.
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        
        if (fullscreen)
        {
            setFullscreen(!fullscreen);
        }
        
    }
    
}

// Handles GLFW event called when a key is pressed, held, or released while focused on the window.
static void onKeyboardInput(GLFWwindow * w, const int key, const int scancode, const int action, const int mods)
{
    
    if (key > 0 && key < sizeof(nimbleInputKeyDown))
    {
        nimbleInputKeyDown[key] = action;
    }
    
}

// Handles GLFW event called when the mouse buttons are pressed when focused on the window.
static void onMouseButton(GLFWwindow * w, const int button, const int action, const int mods)
{
    
    if (button > 0 && button < sizeof(nimbleInputButtonDown))
    {
        nimbleInputButtonDown[button] = action;
    }
    
}

// Handles GLFW event called when the pointer moves across the window.
static void onMouseMove(GLFWwindow * w, const double x, const double y)
{
    
    if (!windowResized)
    {
        const float yawDifference = (x - previousPointerX) * (SENSITIVITY_MAX * sensitivity); // NOTE: Gets percentage of maximum sensitivity (sensitivity ranges from 1-100%) and multiplies that by the movement.
        cameraAngleDifference[1] -= yawDifference;
        cameraAngles[1] += yawDifference;
        
        if (cameraAngles[1] >= (360.0f * M_DEG_TO_RAD))
        {
            cameraAngles[1] -= (360.0f * M_DEG_TO_RAD);
        } else if (cameraAngles[1] <= 0.0f)
        {
            cameraAngles[1] += (360.0f * M_DEG_TO_RAD);
        }
        
        const float pitchDifference = (y - previousPointerY) * (SENSITIVITY_MAX * sensitivity);
        cameraAngleDifference[0] -= pitchDifference;
        cameraAngles[0] -= pitchDifference;
        
        if (cameraAngles[0] >= (360.0f * M_DEG_TO_RAD))
        {
            cameraAngles[0] -= (360.0f * M_DEG_TO_RAD);
        } else if (cameraAngles[0] <= 0.0f)
        {
            cameraAngles[0] += (360.0f * M_DEG_TO_RAD);
        }
        
    } else
    {
        windowResized = 0;
    }
    
    previousPointerX = x;
    previousPointerY = y;
}


// Creates and configures the game window.
static inline void createWindow(void)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    
    if (!mode)
    {
        crash("Could not get video mode from primary monitor.");
    }
    
    screenWidth  = mode->width;
    screenHeight = mode->height;
    refreshRate  = mode->refreshRate;
    windowWidth  = (screenWidth / 1.5);
    windowHeight = (screenHeight / 1.5);
    windowX      = (screenWidth / 2 - windowWidth / 2);
    windowY      = (screenHeight / 2 - windowHeight / 2);
    
    window = glfwCreateWindow(windowWidth, windowHeight, GAME_TITLE, NULL, NULL);
    
    if (!window)
    {
        crash("Could not create window.");
    }
    
    glfwSetWindowPos(window, windowX, windowY);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

// Sets the GLFW event callbacks.
static inline void setGLFWEventCallbacks(void)
{
    glfwSetFramebufferSizeCallback(window, onWindowResize);
    glfwSetWindowPosCallback(window, onWindowMove);
    glfwSetWindowFocusCallback(window, onWindowFocus);
    glfwSetKeyCallback(window, onKeyboardInput);
    glfwSetCursorPosCallback(window, onMouseMove);
    glfwSetMouseButtonCallback(window, onMouseButton);
}

// Initializes the vertex, fragment, and geometry shaders.
static inline void initializeShaders(void)
{
    GLint success = 0;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    if (!vertexShader)
    {
        crash("Could not create vertex shader.");
    }
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        const char   crashMessage[]    = "Could not create vertex shader. Shader compile log:\n";
        size_t       infoLogLength     = strlen(infoLog);
        const size_t crashOutputLength = (infoLogLength + (sizeof(crashMessage) - sizeof(NULL_CHAR)) + sizeof(NULL_CHAR));
        char *       crashOutput       = malloc(crashOutputLength);
        
        if (!crashOutput)
        {
            crash("Ran out of memory.");
        }
        
        snprintf(crashOutput, crashOutputLength, "%s%s", crashMessage, infoLog);
        crash(crashOutput);
    }
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    if (!fragmentShader)
    {
        crash("Could not create fragment shader.");
    }
    
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
        const char   crashMessage[]    = "Could not create fragment shader. Shader compile log:\n";
        size_t       infoLogLength     = strlen(infoLog);
        const size_t crashOutputLength = (infoLogLength + (sizeof(crashMessage) - sizeof(NULL_CHAR)) + sizeof(NULL_CHAR));
        char *       crashOutput       = malloc(ptrSize + crashOutputLength);
        
        if (!crashOutput)
        {
            crash("Ran out of memory.");
        }
        
        snprintf(crashOutput, crashOutputLength, "%s%s", crashMessage, infoLog);
        crash(crashOutput);
    }
    
    shaderProgram = glCreateProgram();
    
    if (!shaderProgram)
    {
        crash("Could not create shader program.");
    }
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        const char   crashMessage[]    = "Could not link shader program. Program linking log:\n";
        size_t       infoLogLength     = strlen(infoLog);
        const size_t crashOutputLength = (infoLogLength + (sizeof(crashMessage) - sizeof(NULL_CHAR)) + sizeof(NULL_CHAR));
        char *       crashOutput       = malloc(ptrSize + crashOutputLength);
        
        if (!crashOutput)
        {
            crash("Ran out of memory.");
        }
        
        snprintf(crashOutput, crashOutputLength, "%s%s", crashMessage, infoLog);
        crash(crashOutput);
    }
    
    uniformModel = glGetUniformLocation(shaderProgram, "model");
    uniformView = glGetUniformLocation(shaderProgram, "view");
    uniformProjection = glGetUniformLocation(shaderProgram, "projection");
    
    glUseProgram(0);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Initialized OpenGL, GLFW, GLEW, sets the event callbacks, and creates the window.
static inline void initializeOpenGL(void)
{
    glewExperimental = TRUE;
    
    if (glfwInit() != GLFW_TRUE)
    {
        crash("Failed to initialize GLFW.");
    }
    
    glfwSetErrorCallback(glfwErrorHandler);
    const char glfwSuccessMessage[] = "Successfully initialized GLFW.";
    nimbleLoggerLog(logFile, glfwSuccessMessage, (sizeof(glfwSuccessMessage) - sizeof(NULL_CHAR)), ENTRY_TYPE_INFO, 1);
    
    createWindow();
    const char windowSuccessMessage[] = "Successfully created window.";
    nimbleLoggerLog(logFile, windowSuccessMessage, (sizeof(windowSuccessMessage) - sizeof(NULL_CHAR)), ENTRY_TYPE_INFO, 1);
    
    setGLFWEventCallbacks();
    
    glewExperimental = TRUE;
    GLenum err = glewInit();
    
    if (err != GLEW_OK)
    {
        const char crashMessage[]    = "Failed to initialize GLEW. GLEW generated reason: %s";
        size_t     crashOutputLength = (sizeof(crashMessage) - FORMAT_LENGTH_2 - sizeof(NULL_CHAR)) + sizeof(NULL_CHAR);
        char *     crashOutput       = malloc(ptrSize + crashOutputLength);
        if (!crashOutput)
        {
            crash("Ran out of memory.");
        }
        snprintf(crashOutput, crashOutputLength, crashMessage, glewGetErrorString(err));
        crash(crashOutput);
    }
    
    const char glewSuccessMessage[] = "Successfully initialized GLEW.";
    nimbleLoggerLog(logFile, glewSuccessMessage, (sizeof(glewSuccessMessage) - sizeof(NULL_CHAR)), ENTRY_TYPE_INFO, 1);
    
    initializeShaders();
    const char shaderProgramSuccessMessage[] = "Successfully created shader program.";
    nimbleLoggerLog(logFile, shaderProgramSuccessMessage, (sizeof(shaderProgramSuccessMessage) - sizeof(NULL_CHAR)), ENTRY_TYPE_INFO, 1);
    
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    
    frameWidth = nimbleMathCeilF(windowWidth * resolution, NULL);
    frameHeight = nimbleMathCeilF(windowHeight * resolution, NULL);
    
#   if 0
    glGenFramebuffers(1, &frameBuffer);
    glGenTextures(1, &colorBuffer);
    glGenRenderbuffers(1, &depthBuffer);
    
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frameWidth, frameHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);
    
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, frameWidth, frameHeight);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    
    GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        // TODO Use other format
        crash("Could not create frame buffer.");
    }
#   endif
    
    int32_t frameBufferWidth  = 0;
    int32_t frameBufferHeight = 0;
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
    
    glm_perspective((fov / 2), ((float) windowWidth / (float) windowHeight), VIEW_DISTANCE_MIN, VIEW_DISTANCE_MAX, projection);
    
    const char openGLSuccessMessage[] = "Successfully initialized OpenGL.";
    nimbleLoggerLog(logFile, openGLSuccessMessage, (sizeof(openGLSuccessMessage) - sizeof(NULL_CHAR)), ENTRY_TYPE_INFO, 1);
}

/* GAME THREADS */

// Handles sound playing.
static void * soundOff(void * args)
{
    
    while (running)
    {
        // TODO Sound code
    }
    
    activeThreads--;
    return NULL;
}

// Handles everything from movement to AI to physics.
static void * tick(void * args)
{
    struct timeval tickTimeMin = {};
    
    while (running)
    {
        tickTimeMin = nimbleTimeSetTimerMillis(MILLIS_PER_SEC / GAME_TPS_MAX);
        
        // TODO Game stuff
        for (uint32_t i = 0; i < objectCount; i++)
        {
            versor rotateYaw = {0.0f, 0.000005f, 0.0f, 1.0f};
            glm_quat_mul(worldObjects[i].orientation, rotateYaw, worldObjects[i].orientation);
        }
        
        while (!nimbleTimeHasPast(tickTimeMin))
        {
            nimbleTimeSleepMillis(0); // Wait for minimum tick time.
        }
        
    }
    
    activeThreads--;
    return NULL;
}

// Handles key holding events.
static void * pollEvents(void * args)
{
    struct timeval eventTimer = nimbleTimeSetTimerMillis(MILLIS_PER_SEC / GAME_MOVEMENT_EVENT_TIME);
    
    while (running)
    {
        
        if (nimbleInputKeyDown[KEY_QUIT] == GLFW_PRESS)
        {
            nimbleInputKeyDown[KEY_QUIT] = GLFW_RELEASE;
            glfwSetWindowShouldClose(window, 1);
        }
        
        if (nimbleInputKeyDown[KEY_DEBUG] == GLFW_PRESS)
        {
            nimbleInputKeyDown[KEY_DEBUG] = GLFW_RELEASE;
            
            if (debug)
            {
                const char debugOnString[] = "Debug toggled off.";
                nimbleLoggerLog(logFile, debugOnString, (sizeof(debugOnString) - sizeof(NULL_CHAR)), ENTRY_TYPE_INFO, 1);
            } else
            {
                const char debugOffString[] = "Debug toggled on.";
                nimbleLoggerLog(logFile, debugOffString, (sizeof(debugOffString) - sizeof(NULL_CHAR)), ENTRY_TYPE_INFO, 1);
            }
            
            debug = !debug;
        }
        
        if (nimbleInputKeyDown[GLFW_KEY_F2] == GLFW_PRESS)
        {
            nimbleInputKeyDown[KEY_FULLSCREEN] = GLFW_RELEASE;
            fullscreen = !fullscreen;
            
            if (debug)
            {
                
                if (fullscreen)
                {
                    const char fullscreenOnString[] = "Fullscreen toggled on.";
                    nimbleLoggerLog(logFile, fullscreenOnString, (sizeof(fullscreenOnString) - sizeof(NULL_CHAR)), ENTRY_TYPE_INFO, 1);
                } else
                {
                    const char fullscreenOffString[] = "Fullscreen toggled off.";
                    nimbleLoggerLog(logFile, fullscreenOffString, (sizeof(fullscreenOffString) - sizeof(NULL_CHAR)), ENTRY_TYPE_INFO, 1);
                }
                
            }
            
            windowShouldFullscreen = 1;
        }
        
        if (nimbleInputKeyDown[KEY_LOG_TEST] == GLFW_PRESS)
        {
            nimbleInputKeyDown[KEY_LOG_TEST] = GLFW_RELEASE;
            const char entryTest[] = "Testing log entry.";
            nimbleLoggerLog(logFile, entryTest, (sizeof(entryTest) - sizeof(NULL_CHAR)), ENTRY_TYPE_INFO, 1);
        }
        
        if (nimbleTimeHasPast(eventTimer))
        {
            const float movement = MOVEMENT_SPEED * (nimbleInputKeyDown[KEY_SPRINT] ? SPRINT_MULTIPLIER : 1);
            if (nimbleInputKeyDown[KEY_FORWARD])
            {
                glm_vec3_muladds(cameraRollAxis, -movement, cameraPosition);
            }
            
            if (nimbleInputKeyDown[KEY_BACKWARD])
            {
                glm_vec3_muladds(cameraRollAxis, movement, cameraPosition);
            }
            
            if (nimbleInputKeyDown[KEY_LEFT])
            {
                glm_vec3_muladds(cameraPitchAxis, -movement, cameraPosition);
            }
            
            if (nimbleInputKeyDown[KEY_RIGHT])
            {
                glm_vec3_muladds(cameraPitchAxis, movement, cameraPosition);
            }
            
            if (nimbleInputKeyDown[KEY_ROLL_LEFT])
            {
                cameraAngleDifference[2] -= 0.000025f;
                cameraAngles[2] -= 0.000025f;
            }
            
            if (nimbleInputKeyDown[KEY_ROLL_RIGHT])
            {
                cameraAngleDifference[2] += 0.000025f;
                cameraAngles[2] += 0.000025f;
            }
            
            if (cameraAngles[2] >= (360.0f * M_DEG_TO_RAD))
            {
                cameraAngles[2] -= (360.0f * M_DEG_TO_RAD);
            } else if (cameraAngles[2] <= 0.0f)
            {
                cameraAngles[2] += (360.0f * M_DEG_TO_RAD);
            }
            
            eventTimer = nimbleTimeSetTimerMillis(MILLIS_PER_SEC / GAME_MOVEMENT_EVENT_TIME);
        }
        sleep(0);
    }
    
    activeThreads--;
    return NULL;
}

// Sets the active texture to textureID.
static void useTexture(const uint32_t textureID)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

// Draws an object to the frame.
static void renderObject(nimbleWorldObject_t object)
{
    glm_translate_make(model, object.position);
    glm_quat_rotate(model, object.orientation, model);
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, (float *) model);
    
    useTexture(object.textureIDs[0]);
    
    glBindVertexArray(object.mesh.VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.mesh.IBO);
    glDrawElements(GL_TRIANGLES, object.mesh.indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Renders the frame.
static inline void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    
    
    versor rotatePitchQuat = {emptyVersor[0], emptyVersor[1], emptyVersor[2], emptyVersor[3]};
    versor rotateYawQuat   = {emptyVersor[0], emptyVersor[1], emptyVersor[2], emptyVersor[3]};
    versor rotateRollQuat  = {emptyVersor[0], emptyVersor[1], emptyVersor[2], emptyVersor[3]};
    
    if (cameraAngleDifference[0])
    {
        const float cameraPitchSin = sinf(cameraAngleDifference[0] / 2.0f);
        nimbleMathQuatInit(rotatePitchQuat, (cameraPitchAxis[0] * cameraPitchSin), (cameraPitchAxis[1] * cameraPitchSin),
                 (cameraPitchAxis[2] * cameraPitchSin), cosf(cameraAngleDifference[0] / 2.0f), NULL);
        cameraAngleDifference[0] = 0;
    }
    
    if (cameraAngleDifference[1])
    {
        const float cameraYawSin = sinf(cameraAngleDifference[1] / 2.0f);
        nimbleMathQuatInit(rotateYawQuat, (cameraYawAxis[0] * cameraYawSin), (cameraYawAxis[1] * cameraYawSin),
                 (cameraYawAxis[2] * cameraYawSin), cosf(cameraAngleDifference[1] / 2.0f), NULL);
        cameraAngleDifference[1] = 0;
    }
    
    if (cameraAngleDifference[2])
    {
        const float cameraRollSin = sinf(cameraAngleDifference[2] / 2.0f);
        nimbleMathQuatInit(rotateRollQuat, (cameraRollAxis[0] * cameraRollSin), (cameraRollAxis[1] * cameraRollSin),
                 (cameraRollAxis[2] * cameraRollSin), cosf(cameraAngleDifference[2] / 2.0f), NULL);
        cameraAngleDifference[2] = 0;
    }
    
    versor rotationQuat = {};
    glm_quat_mul(rotateYawQuat, rotatePitchQuat, rotationQuat);
    glm_quat_mul(rotationQuat, rotateRollQuat, rotationQuat);
    glm_quat_mul(rotationQuat, cameraOrientation, cameraOrientation);
    
    glm_quat_look(cameraPosition, cameraOrientation, view);
    
    // Update relative axes
    nimbleMathVec3Init(cameraPitchAxis, view[0][0], view[1][0], view[2][0], NULL);
    nimbleMathVec3Init(cameraYawAxis, view[0][1], view[1][1], view[2][1], NULL);
    nimbleMathVec3Init(cameraRollAxis, view[0][2], view[1][2], view[2][2], NULL);
    
    
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, (float *) view);
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, (float *) projection);
    
    // Render objects.
    for (uint32_t i = 0; i < objectCount; i++)
    {
        renderObject(worldObjects[i]);
    }
    
    
    glUseProgram(0);
    glfwSwapBuffers(window);
}


/* MAIN FUNCTION */

int main(int argc, char * argv[])
{
    signal(SIGSEGV, signalHandler);
    signal(SIGILL, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGFPE, signalHandler);
#   if !defined(WIN32)
    signal(SIGPIPE, signalHandler);
#   endif
    emergencyMemory = calloc(EMERGENCY_MEMORY, 1);
    activeThreads++; // Current thread
    
    
    initializeLogger();
    initializeOpenGL();
    logSystemInfo();
    
    // Get options.
    optionsFilePathLength = (executableDirectoryLength + (sizeof(optionsFileName) - sizeof(NULL_CHAR)));
    optionsFilePath = nimbleMemoryAllocate(optionsFilePathLength + sizeof(NULL_CHAR));
    snprintf(optionsFilePath, optionsFilePathLength + sizeof(NULL_CHAR), "%s%s", executableDirectory, optionsFileName);
    char * memoryAllocatedString = getVariable(optionsFilePath, "memoryAllocated");
    
    if (memoryAllocatedString)
    {
        memoryAllocated = atol(memoryAllocatedString);
        
        if (memoryAllocated < ALLOCATED_MEMORY_MINIMUM)
        {
            memoryAllocated = ALLOCATED_MEMORY_DEFAULT;
            const uint8_t memoryAllocatedStringLength = (nimbleMathDigits64u(ALLOCATED_MEMORY_DEFAULT) + sizeof(NULL_CHAR));
            char * memoryAllocatedStringOutput = realloc(memoryAllocatedString, (ptrSize + memoryAllocatedStringLength));
            snprintf(memoryAllocatedStringOutput, memoryAllocatedStringLength, "%lu", ALLOCATED_MEMORY_DEFAULT);
            writeVariable(optionsFilePath, "memoryAllocated", memoryAllocatedStringOutput, (memoryAllocatedStringLength - sizeof(NULL_CHAR)));
        }
        
    } else
    {
        memoryAllocated = ALLOCATED_MEMORY_DEFAULT;
        const uint8_t memoryAllocatedStringLength = (nimbleMathDigits64u(ALLOCATED_MEMORY_DEFAULT) + sizeof(NULL_CHAR));
        char * memoryAllocatedStringOutput = realloc(memoryAllocatedString, (ptrSize + memoryAllocatedStringLength));
        snprintf(memoryAllocatedStringOutput, memoryAllocatedStringLength, "%lu", ALLOCATED_MEMORY_DEFAULT);
        writeVariable(optionsFilePath, "memoryAllocated", memoryAllocatedStringOutput, (memoryAllocatedStringLength - sizeof(NULL_CHAR)));
    }
    
    char * volumeMasterString = getVariable(optionsFilePath, "volumeMaster");
    
    if (volumeMasterString)
    {
        volumeMaster = atof(volumeMasterString);
        
        if ((volumeMaster < 0.0f) || (volumeMaster > 1.0f))
        {
            volumeMaster = VOLUME_MASTER_DEFAULT;
            writeVariable(optionsFilePath, "volumeMaster", VOLUME_MASTER_DEFAULT_STRING, (sizeof(VOLUME_MASTER_DEFAULT_STRING) - sizeof(NULL_CHAR)));
        }
        
    } else
    {
        volumeMaster = VOLUME_MASTER_DEFAULT;
        writeVariable(optionsFilePath, "volumeMaster", VOLUME_MASTER_DEFAULT_STRING, (sizeof(VOLUME_MASTER_DEFAULT_STRING) - sizeof(NULL_CHAR)));
    }
    
    char * debugString = getVariable(optionsFilePath, "debug");
    
    if (debugString)
    {
        debug = atof(debugString);
        
        if (debug && (debug != 1))
        {
            debug = DEBUG_DEFAULT;
            writeVariable(optionsFilePath, "debug", DEBUG_DEFAULT_STRING, (sizeof(DEBUG_DEFAULT_STRING) - sizeof(NULL_CHAR)));
        }
        
    } else
    {
        debug = DEBUG_DEFAULT;
        writeVariable(optionsFilePath, "debug", DEBUG_DEFAULT_STRING, (sizeof(DEBUG_DEFAULT_STRING) - sizeof(NULL_CHAR)));
    }
    
    
    // Create objects // TODO Move to where world loading or finding what to render happens.
    uint32_t missingTexture = nimbleTextureLoad("/Users/avery/Downloads/missing.png");
    uint32_t obama = nimbleTextureLoad("/Users/avery/Downloads/obama.png");
    uint32_t obamiumFace = nimbleTextureLoad("/Users/avery/Downloads/obamium_face.png");
    uint32_t obamiumEar = nimbleTextureLoad("/Users/avery/Downloads/obamium_ear.png");
    uint32_t obamiumHair = nimbleTextureLoad("/Users/avery/Downloads/obamium_hair.png");
    
    
    #define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
    #define BYTE_TO_BINARY(byte)  \
      (byte & 0x80 ? '1' : '0'), \
      (byte & 0x40 ? '1' : '0'), \
      (byte & 0x20 ? '1' : '0'), \
      (byte & 0x10 ? '1' : '0'), \
      (byte & 0x08 ? '1' : '0'), \
      (byte & 0x04 ? '1' : '0'), \
      (byte & 0x02 ? '1' : '0'), \
      (byte & 0x01 ? '1' : '0')
    
    uint32_t error = 0;
    BigInt_t bigInt1 = nimbleBigIntFromString("1234567890123456789012345", &error);
    BigInt_t bigInt2 = nimbleBigIntFromString("-9876543210987654321098765", &error);
    BigDec_t bigDec1 = nimbleBigDecFromString("-01234567890123456789012345.00098765432109876543210987654321098765432100", &error);
    BigDec_t bigDec2 = nimbleBigDecFromString("00123456789012345678901234567890.0987654321098765432109876543210987654321000", &error);
    for (uint32_t i = 0; i < bigDec1.integer.size; i++)
    {
        printf(BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((bigDec1.integer.number[i] >> 24) & 0xff), BYTE_TO_BINARY((bigDec1.integer.number[i] >> 16) & 0xff), BYTE_TO_BINARY((bigDec1.integer.number[i] >> 8) & 0xff), BYTE_TO_BINARY(bigDec1.integer.number[i] & 0xff));
    }
    printf(".");
    for (uint32_t i = 0; i < bigDec1.decimal.size; i++)
    {
        printf(BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((bigDec1.decimal.number[i] >> 24) & 0xff), BYTE_TO_BINARY((bigDec1.decimal.number[i] >> 16) & 0xff), BYTE_TO_BINARY((bigDec1.decimal.number[i] >> 8) & 0xff), BYTE_TO_BINARY(bigDec1.decimal.number[i] & 0xff));
    }
    printf("\n%d\n%d\n", bigDec1.leadingZeros, nimbleBigDecTGT(bigDec1, bigDec2));
    nimbleBigIntFree(bigInt1);
    nimbleBigIntFree(bigInt2);
    nimbleBigDecFree(bigDec1);
    nimbleBigDecFree(bigDec2);
    
    
    vec3 object1pos = {};
    vec3 object2pos = {0.0f, 2.0f, 0.0f};
    //uint32_t object1Textures[] = {obamiumFace, obamiumEar, obamiumFace, obamiumEar, obamiumHair};
    uint32_t object1Textures[] = {obama, obama, obama, obama, obama};
    uint32_t object2Textures[] = {missingTexture, missingTexture, missingTexture, missingTexture, missingTexture};
    nimbleObjectCreate(object1pos, emptyVersor, 0, vertices, sizeof(vertices), indices, sizeof(indices), 5, object1Textures);
    nimbleObjectCreate(object2pos, emptyVersor, 0, vertices, sizeof(vertices), indices, sizeof(indices), 5, object2Textures);
    
    
    // Create threads.
    running = 1;
#   if defined(WIN32) // TODO Test
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) tick, 0, 0, (PDWORD) &tickThread);
    
    if (!tickThread)
    {
        crash("Failed to create tick thread.");
    }
    
    activeThreads++;
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) soundOff, 0, 0, (PDWORD) &soundThread);
    
    if (!soundThread)
    {
        crash("Failed to create sound thread.");
    }
    
    activeThreads++;
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) pollEvents, 0, 0, (PDWORD) &eventThread);
    
    if (!eventThread)
    {
        crash("Failed to create event thread.");
    }
    
    activeThreads++;
#   else
    
    if (pthread_create(&tickThread, NULL, tick, NULL))
    {
        crash("Failed to create tick thread.");
    }
    
    activeThreads++;
    
    if (pthread_create(&soundThread, NULL, soundOff, NULL))
    {
        crash("Failed to create sound thread.");
    }
    
    activeThreads++;
    
    if (pthread_create(&eventThread, NULL, pollEvents, NULL))
    {
        crash("Failed to create event thread.");
    }
    
    activeThreads++;
#   endif
    // TODO Networking thread, resource allocation thread, thread pool (for complex and/or background tasks)
    // TODO Use optional compute shader
    const char threadSuccessMessage[] = "Successfully created threads.";
    nimbleLoggerLog(logFile, threadSuccessMessage, (sizeof(threadSuccessMessage) - sizeof(NULL_CHAR)), ENTRY_TYPE_INFO, 1);
    
    clock_t        deltaTime         = 0;
    uint16_t       frameCount        = 0;
    float          frameRate         = 30.0f;
    struct timeval frameTime         = {};
    struct timeval previousFrameTime = {};
    
    if (gettimeofday(&previousFrameTime, NULL)) // Set to avoid errors.
    {
        catchFunctionError(FUNCTION_GETTIMEOFDAY);
    }
    
    // Render loop
    while (running)
    {
        glfwPollEvents();
        
        if (glfwWindowShouldClose(window))
        {
            closeGame();
        }
        
        if (windowShouldFullscreen)
        {
            setFullscreen(fullscreen);
            windowShouldFullscreen = 0;
        }
        
        gettimeofday(&frameTime, NULL);
        deltaTime += nimbleTimeSub(frameTime, previousFrameTime); // Get time since last end of main loop.
        frameCount++;
        
        if (deltaTime >= MICROS_PER_SEC) // Check if deltaTime is longer than one second.
        {
            deltaTime -= MICROS_PER_SEC;
            
            // Check to see if the program ran out of memory
            if (nimbleMemoryUsed > memoryAllocated)
            {
                crash("Ran out of allocated memory.");
            }
            
            if (frameRate <= FPS_MINIMUM)
            {
                //crash("Frame rate dropped below minimum.");
            }
            
            if (debug)
            {
                frameRate = (((float) frameCount * 0.45) + (frameRate * 0.55)); // NOTE: Stabilizes framerate to look more consistent.
                printf("x=%f, y=%f, z=%f, pitch=%f, yaw=%f, roll=%f\n", cameraPosition[0], cameraPosition[1], cameraPosition[2], cameraAngles[0] * M_RAD_TO_DEG, cameraAngles[1] * M_RAD_TO_DEG, cameraAngles[2] * M_RAD_TO_DEG);
                printf("%d frames, %.2f fps, %lluB\n", frameCount, frameRate, nimbleMemoryUsed);
            }
            
            frameCount = 0;
            if (glm_quat_norm(cameraOrientation) != 1.0f)
            {
                glm_quat_normalize(cameraOrientation);
            }
            
            nimbleObjectsNormalize();
        }
        
        render();
        
        previousFrameTime = frameTime;
    }
    
    activeThreads--;
    
    // Crashes from other threads will lead here, wait for crash to finish before closing.
    nimbleTimeSleepMillis(0); // Give up thread priority.
    nimbleTimeSleepMillis(CRASH_WAIT_TIME + 100); // Wait for the threads to close.
    crash("Unexpected exit from main thread.");
    return EXIT_FAILURE;
}

// Nimble Engine Example.c
