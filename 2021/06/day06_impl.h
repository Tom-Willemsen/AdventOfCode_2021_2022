#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "file_loading.h"

static const int64_t REPRO_DAYS = 7;
static const int64_t MAX_DAYS = 9;

int64_t simulate(list_i64* initialstate, int64_t days);
