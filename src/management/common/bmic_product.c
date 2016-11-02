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
#include "bmic_product.h"

static gru_list_t *registry = NULL;

bmic_product_t *bmic_product_init(const char *name, const char *version, 
                                  gru_status_t *status) {
    bmic_product_t *ret = gru_alloc(sizeof(bmic_product_t), status);
    gru_alloc_check(ret, NULL);
    
    ret->name = NULL;
    ret->version = NULL;
        
    asprintf(&ret->name, "%s", name);
    asprintf(&ret->version, "%s", version);
    
    return ret;
}


void bmic_product_destroy(bmic_product_t **product) {
    bmic_product_t *prod = *product;
    
    if (!prod) {
        return;
    }
    
    //free(prod->name);
    //free(prod->version);
    
    gru_dealloc((void **) product);
}

void bmic_product_registry_init(gru_status_t *status) {
    if (registry == NULL) {
        registry = gru_list_new(status);
        
        if (registry == NULL) {
            return;
        }
    }
    else {
        gru_status_set(status, GRU_FAILURE, 
                       "A product registry has already been initialized");
        
        return;
    }
}

void bmic_product_registry_destroy() {
    gru_list_destroy(&registry);
}


void bmic_product_registry_add(const bmic_product_t *product, gru_status_t *status) {
    gru_list_append(registry, product);
}


const gru_list_t *bmic_product_registry() {
    return (const gru_list_t *) registry;
}