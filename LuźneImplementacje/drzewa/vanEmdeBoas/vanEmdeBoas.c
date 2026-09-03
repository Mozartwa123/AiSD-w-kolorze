#include <stdbool.h>

typedef struct {
    vanEmdeBoas* summary;
    vanEmdeBoas** children;
    unsigned long min;
    unsigned long max;
    unsigned long size;
    unsigned long sqrtSize;
    bool exist;
} vanEmdeBoas;
