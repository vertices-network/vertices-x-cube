// Copyright 2021 IOTA Stiftung
// SPDX-License-Identifier: Apache-2.0

#include <stdio.h>
#include <stdlib.h>

#include "json_utils.h"
#include "get_node_info.h"
#include "http_lib.h"
#include "iota_str.h"

res_node_info_t *res_node_info_new(void) {
  res_node_info_t *res = malloc(sizeof(res_node_info_t));
  if (res == NULL) {
    printf("[%s:%d]: OOM\n", __func__, __LINE__);
    return NULL;
  }
  res->is_error = false;
  res->u.error = NULL;
  res->u.output_node_info = NULL;
  return res;
}

void res_node_info_free(res_node_info_t *res) {
  if (res) {
    if (res->is_error) {
      res_err_free(res->u.error);
    } else {
      if (res->u.output_node_info) {
        if (res->u.output_node_info->features) {
          utarray_free(res->u.output_node_info->features);
        }
        free(res->u.output_node_info);
      }
    }
    free(res);
  }
}

char *get_node_features_at(res_node_info_t *info, int idx) {
  if (info == NULL) {
    printf("[%s:%d]: get_features failed (null parameter)\n", __func__, __LINE__);
    return NULL;
  }

  int len = utarray_len(info->u.output_node_info->features);
  if (idx < 0 || idx >= len) {
    printf("[%s:%d]: get_features failed (invalid index)\n", __func__, __LINE__);
    return NULL;
  }

  return *(char **)utarray_eltptr(info->u.output_node_info->features, idx);
}

size_t get_node_features_num(res_node_info_t *info) {
  if (info == NULL) {
    printf("[%s:%d]: get_features failed (null parameter)\n", __func__, __LINE__);
    return 0;
  }

  return utarray_len(info->u.output_node_info->features);
}

int get_node_info(iota_client_conf_t const *conf, res_node_info_t *res) {
  int ret = 0;
  char const *const cmd_info = "api/v1/info";
  http_handle_t http_handle;
  http_response_t http_res;
  memset(&http_res, 0, sizeof(http_response_t));

  if (conf == NULL || res == NULL) {
    printf("[%s:%d]: get_node_info failed (null parameter)\n", __func__, __LINE__);
    return -1;
  }

  // compose restful api command
  iota_str_t *cmd = iota_str_new(conf->url);
  if (cmd == NULL) {
    printf("[%s:%d]: OOM\n", __func__, __LINE__);
    return -1;
  }

  if (iota_str_append(cmd, cmd_info)) {
    printf("[%s:%d]: string append failed\n", __func__, __LINE__);
    iota_str_destroy(cmd);
    return -1;
  }

  // http open
  if (http_open(&http_handle, cmd->buf) != HTTP_OK) {
    printf("[%s:%d]: Can not open HTTP connection\n", __func__, __LINE__);
    ret = -1;
    goto done;
  }

  http_res.body = byte_buf_new();
  if (http_res.body == NULL) {
    printf("[%s:%d]: OOM\n", __func__, __LINE__);
    ret = -1;
    goto done;
  }
  http_res.code = 0;

  // send request via http client
  if ( http_read(http_handle,
                 &http_res,
                 "Content-Type: application/json",
                 NULL) < 0 ) {

    printf("[%s:%d]: HTTP read problem\n", __func__, __LINE__);
    ret = -1;
  }

  // http close
  if (http_close(http_handle) != HTTP_OK )
  {
    printf("[%s:%d]: Can not close HTTP connection\n", __func__, __LINE__);
    ret = -1;
  }

  if (http_res.code == 200 && ret == 0) {
    byte_buf2str(http_res.body);
    
    // json deserialization
    ret = deser_node_info((char const *)http_res.body->data, res);
  } else {
    ret = -1;
  }

done:
  // cleanup command
  iota_str_destroy(cmd);
  byte_buf_free(http_res.body);

  return ret;
}

int deser_node_info(char const *const j_str, res_node_info_t *res) {
  int ret = 0;
  cJSON *json_obj = cJSON_Parse(j_str);
  if (json_obj == NULL) {
    return -1;
  }

  res_err_t *res_err = deser_error(json_obj);
  if (res_err) {
    // got an error response
    res->is_error = true;
    res->u.error = res_err;
    ret = 0;
    goto end;
  } else {

    cJSON *data_obj = cJSON_GetObjectItemCaseSensitive(json_obj, JSON_KEY_DATA);
    if (data_obj) {
      res->u.output_node_info = malloc(sizeof(get_node_info_t));
      if (res->u.output_node_info == NULL) {
        printf("[%s:%d] OOM\n", __func__, __LINE__);
        ret = -1;
        goto end;
      }
      // gets name
      if ((ret = json_get_string(data_obj, JSON_KEY_NAME, res->u.output_node_info->name, sizeof(res->u.output_node_info->name))) != 0) {
        printf("[%s:%d]: gets %s json string failed\n", __func__, __LINE__, JSON_KEY_NAME);
        goto end;
      }
      
      // gets version
      if ((ret = json_get_string(data_obj, JSON_KEY_VER, res->u.output_node_info->version, sizeof(res->u.output_node_info->version))) != 0) {
        printf("[%s:%d]: gets %s json string failed\n", __func__, __LINE__, JSON_KEY_VER);
        goto end;
      }
      
      // gets isHealthy
      if ((ret = json_get_boolean(data_obj, JSON_KEY_IS_HEALTHY, &res->u.output_node_info->is_healthy)) != 0) {
        printf("[%s:%d]: gets %s json boolean failed\n", __func__, __LINE__, JSON_KEY_IS_HEALTHY);
        goto end;
      }
      
      // gets networkId
      if ((ret = json_get_string(data_obj, JSON_KEY_NET_ID, res->u.output_node_info->network_id, sizeof(res->u.output_node_info->network_id))) != 0) {
        printf("[%s:%d]: gets %s json string failed\n", __func__, __LINE__, JSON_KEY_NET_ID);
        goto end;
      }

      // parsing bech32HRP
      if ((ret = json_get_string(data_obj, JSON_KEY_BECH32HRP, res->u.output_node_info->bech32hrp, sizeof(res->u.output_node_info->bech32hrp))) != 0) {
        printf("[%s:%d]: gets %s json string failed\n", __func__, __LINE__, JSON_KEY_BECH32HRP);
        goto end;
      }

      // gets minPowScore
      if ((ret = json_get_uint64(data_obj, JSON_KEY_MIN_POW, &res->u.output_node_info->min_pow_score)) != 0) {
        printf("[%s:%d]: gets %s json string failed\n", __func__, __LINE__, JSON_KEY_MIN_POW);
        goto end;
      }
      
      // gets latestMilestoneIndex
      if ((ret = json_get_uint64(data_obj, JSON_KEY_LM_IDX, &res->u.output_node_info->latest_milestone_index)) != 0) {
        printf("[%s:%d]: gets %s json string failed\n", __func__, __LINE__, JSON_KEY_LM_IDX);
        goto end;
      }

      // gets confirmedMilestoneIndex
      if ((ret = json_get_uint64(data_obj, JSON_KEY_CM_IDX, &res->u.output_node_info->confirmed_milestone_index)) != 0) {
        printf("[%s:%d]: gets %s json string failed\n", __func__, __LINE__, JSON_KEY_CM_IDX);
        goto end;
      }

      // gets pruningIndex
      if ((ret = json_get_uint64(data_obj, JSON_KEY_PRUNING_IDX, &res->u.output_node_info->pruning_milestone_index)) != 0) {
        printf("[%s:%d]: gets %s json string failed\n", __func__, __LINE__, JSON_KEY_PRUNING_IDX);
        goto end;
      }

      // features
      utarray_new(res->u.output_node_info->features, &ut_str_icd);
      if ((ret = json_string_array_to_utarray(data_obj, JSON_KEY_FEATURES, res->u.output_node_info->features)) != 0) {
        printf("[%s:%d]: gets %s json string failed\n", __func__, __LINE__, JSON_KEY_FEATURES);
        goto end;
      }
    } else {
      ret = -1;
    }
  }

end:
  cJSON_Delete(json_obj);
  return ret;
}
