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

#ifndef BMIC_PRINT_SIMPLE_H
#define BMIC_PRINT_SIMPLE_H

#include <common/gru_colors.h>

#include "base/common/bmic_cap_value.h"
#include "base/common/bmic_object.h"

#include "management/common/bmic_product.h"

#ifdef __cplusplus
extern "C" {
#endif

void print_returned_object(const char *capname, const bmic_object_t *obj);
void print_product_info(bmic_api_interface_t *api, bmic_product_info_t *info);

#ifdef __cplusplus
}
#endif

#endif /* BMIC_PRINT_SIMPLE_H */
