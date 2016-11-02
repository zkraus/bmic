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
#include <stdio.h>
#include <stdlib.h>

#include <common/gru_status.h>

#include <json-c/json.h>

#include "transport/bmic_endpoint.h"
#include "transport/bmic_endpoint_http.h"
#include "format/bmic_json.h"


#include "management/common/bmic_product.h"
#include "management/common/bmic_discovery_hint.h"
#include "product/bmic_product_register.h"

int main(int argc, char** argv)
{
    gru_status_t status = {0};
    bmic_discovery_hint_t *hint = NULL; 
    bmic_credentials_t *credentials = NULL;
    
    bmic_product_registry_init(&status);
    
    bmic_product_register(&status);
    bmic_product_unregister();
    
    /*
    credentials = bmic_credentials_init((char *) argv[1], (char *) argv[2], 
                                        &status); 
             
    
    hint = bmic_discovery_hint_eval_addressing(argv[3], BMIC_PORT_UNKNOWN, 
                                               &status);
    
    
    
    
    
    bmic_product_t *product = bmic_discovery_run(hint, credentials, &status);
    */
    bmic_product_registry_destroy();
    
    return (EXIT_SUCCESS);
}

