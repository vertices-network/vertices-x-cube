// Copyright 2020 IOTA Stiftung
// SPDX-License-Identifier: Apache-2.0

/**
 * @brief A simple example of sending an indexation message containing the
 * sensor data to the Tangle directly.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "test_config.h"
#include "send_message.h"
#include "sensors_data.h"

int send_sensor_index(void)
{
  int err = 0;
  iota_client_conf_t ctx = {.url = TEST_NODE_ENDPOINT, .port = TEST_NODE_PORT};
  res_send_message_t res;
  memset(&res, 0, sizeof(res_send_message_t));
  char jsonData[128] = {0};

  // send out sensor index
  int rc = SensorDataToJSON(jsonData, sizeof(jsonData));
  printf("%s\n", jsonData);
  if (0 == rc) {
    err = send_indexation_msg(&ctx, "iota_sensor_data", jsonData, &res);
    
    if (res.is_error) {
      printf("Err response: %s\n", res.u.error->msg);
      res_err_free(res.u.error);
    }
    
    if (err) {
      printf("send sensor indexation failed\n");
    } else {
      printf("message ID: %s\n", res.u.msg_id);
    }
  } else {
    printf("sensor data JSON formatting failed\n");
  }

  return 0;
}
