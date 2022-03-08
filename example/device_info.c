//
// Created by martijn on 24-11-21.
//

#include <glib.h>
#include "device_info.h"

static GHashTable *device_info_store;

struct device_info {
    char *address;
    char *manufacturer;
    char *model;
    char *serial_number;
    char *firmware_version;
    char *software_version;
    char *hardware_version;
    guint8 battery_level;
    GDateTime *device_time;
    GDateTime *created;
    GDateTime *last_observation_timestamp;
};

DeviceInfo *get_device_info(const char *address) {
    g_assert(address != NULL);

    if (device_info_store == NULL) {
        device_info_store = g_hash_table_new_full(g_str_hash, g_str_equal,
                                                  g_free, (GDestroyNotify) device_info_free);
    }

    DeviceInfo *result = g_hash_table_lookup(device_info_store, address);
    if (result == NULL) {
        result = g_new0(DeviceInfo, 1);
        result->address = g_strdup(address);
        result->created = g_date_time_new_now_local();
        g_hash_table_insert(device_info_store, g_strdup(address), result);
    }
    return result;
}

void device_info_free(DeviceInfo *deviceInfo) {
    if (deviceInfo->address != NULL) {
        g_free(deviceInfo->address);
        deviceInfo->address = NULL;
    }

    if (deviceInfo->manufacturer != NULL) {
        g_free(deviceInfo->manufacturer);
        deviceInfo->manufacturer = NULL;
    }

    if (deviceInfo->model != NULL) {
        g_free(deviceInfo->model);
        deviceInfo->model = NULL;
    }

    if (deviceInfo->serial_number != NULL) {
        g_free(deviceInfo->serial_number);
        deviceInfo->serial_number = NULL;
    }

    if (deviceInfo->firmware_version != NULL) {
        g_free(deviceInfo->firmware_version);
        deviceInfo->firmware_version = NULL;
    }

    if (deviceInfo->software_version != NULL) {
        g_free(deviceInfo->software_version);
        deviceInfo->software_version = NULL;
    }

    if (deviceInfo->hardware_version != NULL) {
        g_free(deviceInfo->hardware_version);
        deviceInfo->hardware_version = NULL;
    }

    if (deviceInfo->device_time != NULL) {
        g_date_time_unref(deviceInfo->device_time);
    }

    if (deviceInfo->created != NULL) {
        g_date_time_unref(deviceInfo->created);
    }

    if (deviceInfo->last_observation_timestamp != NULL) {
        g_date_time_unref(deviceInfo->last_observation_timestamp);
    }

    g_free(deviceInfo);
}

void device_info_close() {
    if (device_info_store != NULL) {
        g_hash_table_destroy(device_info_store);
        device_info_store = NULL;
    }
}

void device_info_set_manufacturer(DeviceInfo *deviceInfo, const char *manufacturer) {
    g_assert(manufacturer != NULL);
    if (deviceInfo->manufacturer != NULL) {
        g_free(deviceInfo->manufacturer);
    }
    deviceInfo->manufacturer = g_strdup(manufacturer);
}

void device_info_set_model(DeviceInfo *deviceInfo, const char *model) {
    g_assert(model != NULL);
    if (deviceInfo->model != NULL) {
        g_free(deviceInfo->model);
    }
    deviceInfo->model = g_strdup(model);
}

void device_info_set_serialnumber(DeviceInfo *deviceInfo, const char *serialnumber) {
    g_assert(serialnumber != NULL);
    if (deviceInfo->serial_number != NULL) {
        g_free(deviceInfo->serial_number);
    }
    deviceInfo->serial_number = g_strdup(serialnumber);
}

void device_info_set_firmware_version(DeviceInfo *deviceInfo, const char *firmware_version) {
    g_assert(firmware_version != NULL);
    if (deviceInfo->firmware_version != NULL) {
        g_free(deviceInfo->firmware_version);
    }
    deviceInfo->firmware_version = g_strdup(firmware_version);
}

void device_info_set_hardware_version(DeviceInfo *deviceInfo, const char *hardware_version) {
    g_assert(hardware_version != NULL);
    if (deviceInfo->hardware_version != NULL) {
        g_free(deviceInfo->hardware_version);
    }
    deviceInfo->hardware_version = g_strdup(hardware_version);
}

void device_info_set_software_version(DeviceInfo *deviceInfo, const char *software_version) {
    g_assert(software_version != NULL);
    if (deviceInfo->software_version != NULL) {
        g_free(deviceInfo->software_version);
    }
    deviceInfo->software_version = g_strdup(software_version);
}

void device_info_set_device_time(DeviceInfo *deviceInfo, GDateTime *device_time) {
    g_assert(deviceInfo != NULL);
    g_assert(device_time != NULL);

    if (deviceInfo->device_time != NULL) {
        g_date_time_unref(deviceInfo->device_time);
    }
    deviceInfo->device_time = g_date_time_ref(device_time);
}

void device_info_set_last_observation_timestamp(DeviceInfo *deviceInfo, GDateTime *timestamp) {
    g_assert(deviceInfo != NULL);
    g_assert(timestamp != NULL);

    if (deviceInfo->last_observation_timestamp == timestamp) return;

    if (deviceInfo->last_observation_timestamp != NULL) {
        g_date_time_unref(deviceInfo->last_observation_timestamp);
    }
    deviceInfo->last_observation_timestamp = g_date_time_new_from_unix_local(g_date_time_to_unix(timestamp));
}

const char *device_info_get_address(DeviceInfo *deviceInfo) {
    g_assert(deviceInfo != NULL);
    return deviceInfo->address;
}

const char *device_info_get_manufacturer(DeviceInfo *deviceInfo) {
    g_assert(deviceInfo != NULL);
    return deviceInfo->manufacturer;
}

const char *device_info_get_model(DeviceInfo *deviceInfo) {
    g_assert(deviceInfo != NULL);
    return deviceInfo->model;
}

const char *device_info_get_serialnumber(DeviceInfo *deviceInfo) {
    g_assert(deviceInfo != NULL);
    return deviceInfo->serial_number;
}

const char *device_info_get_firmware_version(DeviceInfo *deviceInfo) {
    g_assert(deviceInfo != NULL);
    return deviceInfo->firmware_version;
}

const char *device_info_get_hardware_version(DeviceInfo *deviceInfo) {
    g_assert(deviceInfo != NULL);
    return deviceInfo->hardware_version;
}

const char *device_info_get_software_version(DeviceInfo *deviceInfo) {
    g_assert(deviceInfo != NULL);
    return deviceInfo->software_version;
}

GDateTime *device_info_get_device_time(DeviceInfo *deviceInfo) {
    g_assert(deviceInfo != NULL);
    return deviceInfo->device_time;
}

GDateTime* device_info_get_last_observation_timestamp(const DeviceInfo *deviceInfo) {
    g_assert(deviceInfo != NULL);
    return deviceInfo->last_observation_timestamp;
}
