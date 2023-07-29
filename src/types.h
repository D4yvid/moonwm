#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef char i8;
typedef short i16;
typedef int i32;
typedef long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

#define LOGI(f,...) fprintf(stdout, "[%s:%d] [INFO ]: " f "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGW(f,...) fprintf(stdout, "[%s:%d] [WARN ]: " f "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGE(f,...) fprintf(stderr, "[%s:%d] [ERROR]: " f "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define Stack(T)		struct { T *pTop; T *pItems; u32 uSize; }

#define StackPush(s, i)	do {																							\
							(s)->pItems = realloc((s)->pItems, sizeof(__typeof__(*(s)->pItems)) * ((s)->uSize + 1));	\
							(s)->pItems[(s)->uSize] = i;																\
							(s)->pTop = &(s)->pItems[(s)->uSize++];														\
						} while (0)

#define StackPop(s, r)	do {																							\
							if (!(s)->uSize) break;																		\
							(r) = *(s)->pTop;																			\
							(s)->pItems = realloc((s)->pItems, sizeof(__typeof__(*(s)->pItems)) * ((s)->uSize - 1));	\
							(s)->pTop = &(s)->pItems[--(s)->uSize];														\
						} while (0);

#define StackFree(s)	do {																							\
							free((s)->pItems);																			\
							(s)->pTop = NULL;																			\
							(s)->pItems = NULL;																			\
							(s)->uSize = 0;																				\
						} while (0)

#endif // !TYPES_H
