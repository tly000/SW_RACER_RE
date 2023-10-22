#ifndef SWRCONFIG_H
#define SWRCONFIG_H

#include "types.h"
#include <stdbool.h>

#define swrConfig_WriteMappings_ADDR (0x00406080)

#define swrConfig_WriteVideoConfig_ADDR (0x00408880)

#define swrConfig_WriteForceFeedbackConfig_ADDR (0x0040ab80)

#define swrConfig_WriteAudioConfig_ADDR (0x00422140)
#define swrConfig_ReadAudioConfig_ADDR (0x00422440)

#define swrConfig_Open_ADDR (0x004877d0)
#define swrConfig_Close_ADDR (0x00487960)
#define swrConfig_Puts_ADDR (0x004879a0)
#define swrConfig_Printf_ADDR (0x004879f0)
#define swrConfig_Tokenizer_ADDR (0x00487a50)

int swrConfig_WriteMappings(char* dirname);

int swrConfig_WriteVideoConfig(char* dirname);

int swrConfig_WriteForceFeedbackConfig(char* filename);

int swrConfig_WriteAudioConfig(char* dirname);
int swrConfig_ReadAudioConfig(char* dirname);

int swrConfig_Open(char* filename);
void swrConfig_Close(void);
size_t swrConfig_Puts(char* string);
size_t swrConfig_Printf(char* format, ...);
size_t swrConfig_Tokenizer(char* line);

#endif // SWRCONFIG_H
