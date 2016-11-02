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
#include "bmic_artemis.h"
#include "management/discovery/bmic_discovery.h"
#include "management/common/bmic_handle.h"
#include "transport/bmic_endpoint_http.h"

bmic_product_t *bmic_artemis_product(gru_status_t *status) {
    bmic_product_t *ret = bmic_product_init("artemis", "1.x.x", status);

    ret->base_url = bmic_artemis_base_url;
    ret->product_init = bmic_artemis_init;
    
    return ret;
}

const char *bmic_artemis_base_url(bmic_discovery_hint_t *hint) {
    char *ret = NULL; 
    
    if (hint->hint_type == URL) {
        asprintf(&ret, "%s/jolokia/list/org.apache.activemq.artemis", 
                 hint->content.url);
    }
    else {
        asprintf(&ret, "http://%s:%i/jolokia/list/org.apache.activemq.artemis", 
                 hint->content.addressing.hostname, 8161);
    }
    
    return ret;
}

bmic_handle_t *bmic_artemis_init(const char *base_url, 
                                 bmic_credentials_t *credentials, 
                                 gru_status_t *status) {
    bmic_handle_t *handle = NULL;
    
    handle = gru_alloc(sizeof(bmic_handle_t), status);
    gru_alloc_check(handle, NULL);
    
    handle->ep = bmic_endpoint_init(base_url, NULL, NULL, status);
    if (handle->ep == NULL) {
        // bmic_artemis_destroy(&handle);
        
        return NULL;
    }
    
    bmic_endpoint_set_credentials(handle->ep, credentials, status);
    bmic_endpoint_http_begin(handle->ep, status);
    
    handle->transport.read = bmic_endpoint_http_read;
    handle->transport.write = bmic_endpoint_http_write;
    
    return handle;
}