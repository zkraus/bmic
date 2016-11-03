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
#ifndef BMIC_HANDLE_H
#define BMIC_HANDLE_H

#include "base/transport/bmic_transport.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bmic_handle_t_ {
    bmic_endpoint_t *ep;
    bmic_transport_t transport;
} bmic_handle_t;


#ifdef __cplusplus
}
#endif

#endif /* BMIC_HANDLE_H */

