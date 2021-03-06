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
#include "bmic_artemis_json.h"
#include "bmic_artemis_mi.h"

/**
 * Sets the mbean part of the exec call
 * @param op
 * @note The first part of exec call is: "type":"EXEC",
 */
static void bmic_artemis_json_op_mbean(const bmic_object_t *op, bmic_json_t *json) {
	char *mbean_value = NULL;

	// TODO: inadequate handling of asprintf result.
	if (asprintf(&mbean_value, "%s:%s", ARTEMIS_BASE_PKG, op->name) == -1) {
		logger_t logger = gru_logger_get();

		logger(FATAL, "Not enough memory to set json value 'mbean'");

		return;
	}
	json_object *mbean = json_object_new_string(mbean_value);
	free(mbean_value);

	json_object_object_add(json->obj, "mbean", mbean);
}

/**
 * Sets the first part of the exec call
 * @param op
 * @note The first part of exec call is: "type":"EXEC",
 */
static void bmic_artemis_json_op_exec(const bmic_object_t *op, bmic_json_t *json) {
	json_object *op_type = json_object_new_string("EXEC");
	json_object_object_add(json->obj, "type", op_type);
}

/*
 curl -u admin:admin -H "Content-Type: application/json" -X POST
 *  -d '{
 *       "type":"EXEC",
 *
 "mbean":"org.apache.activemq.artemis:brokerName=\"0.0.0.0\",module=Core,serviceType=Server,type=Broker",
 *        "operation": "createQueue(java.lang.String,java.lang.String)",
 *        "arguments": ["name", "address"]
 *      }'
 *
 *      http://localhost:8161/jolokia/
 */

void bmic_artemis_json_create_queue(
	const bmic_object_t *op, bmic_json_t *json, const char *name) {
	bmic_artemis_json_op_exec(op, json);

	bmic_artemis_json_op_mbean(op, json);

	json_object *create_queue = json_object_new_string(ARTEMIS_CREATE_CORE_QUEUE_SIG);
	json_object_object_add(json->obj, "operation", create_queue);

	// Arguments
	json_object *arguments = json_object_new_array();
	json_object *arg_name = json_object_new_string(name);
	json_object *address = json_object_new_string(name);
	json_object *rtype = json_object_new_string("ANYCAST");
	json_object_array_add(arguments, arg_name);
	json_object_array_add(arguments, address);
	json_object_array_add(arguments, rtype);
	json_object_object_add(json->obj, "arguments", arguments);
}

void bmic_artemis_json_destroy_queue(
	const bmic_object_t *op, bmic_json_t *json, const char *name) {
	bmic_artemis_json_op_exec(op, json);

	bmic_artemis_json_op_mbean(op, json);

	json_object *operation = json_object_new_string(ARTEMIS_DESTROY_CORE_QUEUE_SIG);
	json_object_object_add(json->obj, "operation", operation);

	// Arguments
	json_object *arguments = json_object_new_array();
	json_object *arg_name = json_object_new_string(name);
	json_object_array_add(arguments, arg_name);
	json_object_object_add(json->obj, "arguments", arguments);
}

void bmic_artemis_json_purge_queue(const bmic_object_t *op, bmic_json_t *json) {
	bmic_artemis_json_op_exec(op, json);

	bmic_artemis_json_op_mbean(op, json);

	json_object *operation = json_object_new_string(ARTEMIS_PURGE_CORE_QUEUE_SIG);
	json_object_object_add(json->obj, "operation", operation);

	// Arguments
	json_object *arguments = json_object_new_array();
	json_object *arg_name = json_object_new_string("");
	json_object_array_add(arguments, arg_name);
	json_object_object_add(json->obj, "arguments", arguments);
}

void bmic_artemis_json_reset_ack_queue(const bmic_object_t *op, bmic_json_t *json) {
	bmic_artemis_json_op_exec(op, json);

	bmic_artemis_json_op_mbean(op, json);

	json_object *operation = json_object_new_string(ARTEMIS_RESET_ACK_CORE_QUEUE_SIG);
	json_object_object_add(json->obj, "operation", operation);

	// Arguments
	json_object *arguments = json_object_new_array();
	json_object_object_add(json->obj, "arguments", arguments);
}

void bmic_artemis_json_reset_exp_queue(const bmic_object_t *op, bmic_json_t *json) {
	bmic_artemis_json_op_exec(op, json);

	bmic_artemis_json_op_mbean(op, json);

	json_object *operation = json_object_new_string(ARTEMIS_RESET_EXP_CORE_QUEUE_SIG);
	json_object_object_add(json->obj, "operation", operation);

	// Arguments
	json_object *arguments = json_object_new_array();
	json_object_object_add(json->obj, "arguments", arguments);
}