/**
 Copyright 2016 Otavio Rodolfo Piske

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
#include "bmic_java.h"


static void bmic_java_read_mem_value(bmic_object_t *root, const char *name, 
                                     const char *path, uint64_t *dest,
                                     gru_status_t *status) 
{
    bmic_object_t *mem = bmic_object_find_by_path(root, path);
    if (!mem) {
        gru_status_set(status, GRU_FAILURE, "Unable to find %s memory value", name);
        return;
    }
    
    if (mem->type != INTEGER)  {
        gru_status_set(status, GRU_FAILURE, "Invalid data type for %s memory value", 
                       name);
        return;
    }
    
    *dest = mem->data.number;
}

/**
 * Read a single an attribute from the MI
 * @param handle
 * @param capabilities
 * @param name
 * @param status
 * @return 
 */
static bmic_java_mem_info_t bmic_java_read_mem_info_any(bmic_handle_t *handle,
                                                        bmic_object_t *usage, 
                                                        gru_status_t *status) {
    bmic_java_mem_info_t ret = {0};
   
    if (!usage) {
        return ret;
    }
    
    bmic_jolokia_translate_status(usage, status);
    if (status->code != GRU_SUCCESS) {
        return ret;
    }
    
    const bmic_object_t *init = bmic_object_find_by_path(usage, "/value/init");
    if (!init) {
        gru_status_set(status, GRU_FAILURE, "Unable to find initial memory value");
        return ret;
    }
    
    if (init->type != INTEGER)  {
        gru_status_set(status, GRU_FAILURE, "Invalid data type for initial memory value");
        return ret;
    }
    
    bmic_java_read_mem_value(usage, "init", "/value/init", &ret.init, status);
    if (status->code != GRU_SUCCESS) {
        return ret;
    }
    
    bmic_java_read_mem_value(usage, "committed", "/value/committed", &ret.committed, 
                             status);
    if (status->code != GRU_SUCCESS) {
        return ret;
    }
    
    bmic_java_read_mem_value(usage, "max", "/value/max", &ret.max, 
                             status);
    if (status->code != GRU_SUCCESS) {
        return ret;
    }
    
    bmic_java_read_mem_value(usage, "used", "/value/used", &ret.used, 
                             status);
    if (status->code != GRU_SUCCESS) {
        return ret;
    }
    
    return ret;
}

bmic_java_mem_info_t bmic_java_mem_eden_info(bmic_handle_t *handle, gru_status_t *status) {
    const bmic_object_t *usage = bmic_jolokia_io_read_attribute(handle, "java.lang", 
                                                        "name=PS Eden Space,type=MemoryPool", 
                                                        "Usage", 
                                                        status);
    
    return bmic_java_read_mem_info_any(handle, usage, status);
}

bmic_java_mem_info_t bmic_java_mem_survivor_info(bmic_handle_t *handle, gru_status_t *status) {
    const bmic_object_t *usage = bmic_jolokia_io_read_attribute(handle, "java.lang", 
                                                        "name=PS Survivor Space,type=MemoryPool", 
                                                        "Usage", 
                                                        status);
    
    return bmic_java_read_mem_info_any(handle, usage, status);
}

bmic_java_mem_info_t bmic_java_mem_tenured_info(bmic_handle_t *handle, gru_status_t *status) {
    const bmic_object_t *usage = bmic_jolokia_io_read_attribute(handle, "java.lang", 
                                                        "name=PS Old Gen,type=MemoryPool", 
                                                        "Usage", 
                                                        status);
    
    return bmic_java_read_mem_info_any(handle, usage, status);
}

bmic_java_mem_info_t bmic_java_mem_code_cache_info(bmic_handle_t *handle, gru_status_t *status) {
    const bmic_object_t *usage = bmic_jolokia_io_read_attribute(handle, "java.lang", 
                                                        "name=CodeCache,type=MemoryPool", 
                                                        "Usage", 
                                                        status);
    
    return bmic_java_read_mem_info_any(handle, usage, status);
}


bmic_java_mem_info_t bmic_java_mem_metaspace_info(bmic_handle_t *handle, gru_status_t *status) {
    const bmic_object_t *usage = bmic_jolokia_io_read_attribute(handle, "java.lang", 
                                                        "name=Metaspace,type=MemoryPool", 
                                                        "Usage", 
                                                        status);
    
    return bmic_java_read_mem_info_any(handle, usage, status);
}

bmic_java_mem_info_t bmic_java_mem_permgen_info(bmic_handle_t *handle, gru_status_t *status) {
    const bmic_object_t *usage = bmic_jolokia_io_read_attribute(handle, "java.lang", 
                                                        "name=PermGen,type=MemoryPool", 
                                                        "Usage", 
                                                        status);
    
    return bmic_java_read_mem_info_any(handle, usage, status);
}

/*
 typedef struct bmic_complements_java_api_t_ {
    bmic_complement_api_java_info_fn java_info;
        
    bmic_complement_api_java_os_info_fn os_info;
    
} bmic_complements_java_api_t;
 */

bmic_java_info_t bmic_java_read_info(bmic_handle_t *handle, gru_status_t *status) {
    bmic_java_info_t ret = {0};
    bmic_object_t *runtime = bmic_jolokia_io_read_attribute(handle, "java.lang", 
                                                        "type=Runtime", 
                                                        "", 
                                                        status);
    
    if (!runtime) {
        return ret;
    }
    
    bmic_jolokia_translate_status(runtime, status);
    if (status->code != GRU_SUCCESS) {
        return ret;
    }
    
    bmic_object_t *jvmname = bmic_object_find_by_path(runtime, "/value/VmName");
    if (!jvmname) {
        gru_status_set(status, GRU_FAILURE, "Unable to find JVM name");
        return ret;
    }
    if (jvmname->type != STRING) {
        gru_status_set(status, GRU_FAILURE, "Invalid data type for JVM name");
        return ret;
    }
    
    ret.name = jvmname->data.str;
    
    
    bmic_object_t *version = bmic_object_find_by_path(runtime, "/value/SpecVersion");
    if (!version) {
        gru_status_set(status, GRU_FAILURE, "Unable to find JVM version");
        return ret;
    }
    if (version->type != STRING) {
        gru_status_set(status, GRU_FAILURE, "Invalid data type for JVM name");
        return ret;
    }
    
    ret.version = version->data.str;

    return ret;
}