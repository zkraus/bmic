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
#ifndef BMIC_OBJECT_H
#define BMIC_OBJECT_H

#include <stdbool.h>

#include <common/gru_alloc.h>
#include <common/gru_status.h>

#include <collection/gru_list.h>
#include <collection/gru_tree.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef enum bmic_value_type_t_ {
    INTEGER,
    STRING,
    BOOLEAN,
    DOUBLE,
    NULL_TYPE,
    ARRAY,
    OBJECT,
} bmic_value_type_t;

typedef union bmic_value_t_ {
    int64_t number;
    char *str;
    bool value;
    double d;
    gru_list_t *list;
    gru_tree_node_t *object;
} bmic_value_t;

typedef struct bmic_object_t_ {
    bmic_value_type_t type;
    bmic_value_t data;
} bmic_object_t;

bmic_object_t *bmic_object_new(gru_status_t *status);
void bmic_object_destroy(bmic_object_t **ptr);

void bmic_object_set_string(bmic_object_t *obj, const char *value);
void bmic_object_set_integer(bmic_object_t *obj, int64_t value);
void bmic_object_set_boolean(bmic_object_t *obj, bool value);
void bmic_object_set_double(bmic_object_t *obj, double value);
void bmic_object_set_null(bmic_object_t *obj);


#ifdef __cplusplus
}
#endif

#endif /* BMIC_OBJECT_H */
