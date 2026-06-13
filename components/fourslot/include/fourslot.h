#include <stdint.h>

#define DECLARE_FOURSLOT(NAME, TYPE)                                  \
    typedef struct {                                                  \
        TYPE             slot[2][2];                                   \
        volatile uint8_t reading;                                     \
        volatile uint8_t latest;                                      \
        volatile uint8_t slot_idx[2];                                 \
    } NAME##_fourslot_t;                                              \
                                                                      \
    static inline void NAME##_write(NAME##_fourslot_t *fs, const TYPE *value) { \
        uint8_t pair = !fs->reading;                                  \
        uint8_t s    = !fs->slot_idx[pair];                           \
        fs->slot[pair][s] = *value;                                   \
        __sync_synchronize();                                         \
        fs->slot_idx[pair] = s;                                       \
        __sync_synchronize();                                         \
        fs->latest = pair;                                            \
    }                                                                 \
                                                                      \
    static inline void NAME##_read(NAME##_fourslot_t *fs, TYPE *out) { \
        uint8_t pair = fs->latest;                                    \
        fs->reading = pair;                                           \
        __sync_synchronize();                                         \
        uint8_t s = fs->slot_idx[pair];                               \
        __sync_synchronize();                                         \
        *out = fs->slot[pair][s];                                     \
    }