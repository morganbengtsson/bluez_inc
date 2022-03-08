//
// Created by martijn on 09-11-21.
//

#ifndef TEST_OBSERVATION_H
#define TEST_OBSERVATION_H

#include <glib.h>
#include "observation_type.h"
#include "observation_units.h"
#include "observation_location.h"

typedef struct observation {
    float value;
    ObservationUnit unit;
    ObservationType type;
    int duration_msec;
    GDateTime *timestamp;
    GDateTime *received;
    ObservationLocation location;
    int sensor;
} Observation;

const char *observation_get_display_str(Observation *observation);
void observation_list_free(GList *observation_list);


#endif //TEST_OBSERVATION_H
