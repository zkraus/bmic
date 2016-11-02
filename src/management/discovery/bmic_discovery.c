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
#include "bmic_discovery.h"
#include "transport/bmic_endpoint.h"


// typedef void(*handle_function_t)(const gru_node_t *, void *);

void bmic_try_init(const gru_node_t *node, void *data) {
    bmic_product_t *product = gru_node_get_data(bmic_product_t *, node);
    
    
    printf("Name: %s\n", product->name);
}

bmic_product_t *bmic_discovery_run(const bmic_discovery_hint_t *hint,
                                   bmic_credentials_t *credentials,
        gru_status_t *status) 
{
    const gru_list_t *list = bmic_product_registry();
    
    gru_list_for_each(list, bmic_try_init, credentials);
    
    return NULL;
}