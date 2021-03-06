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
#include "bmic_api_io.h"

void bmic_api_io_read(
	bmic_handle_t *handle, const char *path, bmic_data_t *reply, gru_status_t *status) {
	bmic_endpoint_status_t epstatus = bmic_endpoint_status_new(status);

	gru_status_reset(status);
	bmic_endpoint_set_path(handle->ep, path, status);
	if (gru_status_error(status)) {
		return;
	}

	handle->transport.read(handle->ep, NULL, reply, &epstatus);
	bmic_endpoint_reset_path(handle->ep);
}