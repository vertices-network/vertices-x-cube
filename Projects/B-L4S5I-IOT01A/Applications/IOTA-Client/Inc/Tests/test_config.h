// Copyright 2021 IOTA Stiftung
// SPDX-License-Identifier: Apache-2.0

#ifndef TEST_CLIENT_API_CONFIG_H
#define TEST_CLIENT_API_CONFIG_H

/** @addtogroup PROJECTS
 * @{
 */
 
/** @addtogroup B-L4S5I-IOT01A
 * @{
 */

/** @addtogroup APPLICATIONS
 * @}
 */

/** @addtogroup IOTA_Client
 * @{
 */

/** @defgroup IOTA_TEST IOTA Test
 * @{
 */

/** @defgroup IOTA_TEST_EXPORTED_CONSTANTS Exported Constants
 * @{
 */

// enable or disable test cases use the Tangle network.
// We don't enable it by default but enable it for a local test is recommended.
#define TEST_TANGLE_ENABLE 0

#define TEST_NODE_ENDPOINT "https://api.lb-0.testnet.chrysalis2.com/"
#define TEST_NODE_PORT 0

#define MY_SEED "seed_with_64_char"
#define ACCOUNT_PATH "m/44'/4218'/0'/0'"

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#endif /* TEST_CLIENT_API_CONFIG_H */
