// Copyright 2020 IOTA Stiftung
// SPDX-License-Identifier: Apache-2.0

/**
 * @brief A simple example for checking balances.
 *
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_config.h"
#include "byte_buffer.h"
#include "wallet.h"

void show_address(iota_wallet_t *w, uint32_t index) {
  byte_t addr_wit_version[IOTA_ADDRESS_BYTES];
  memset(addr_wit_version, 0, sizeof(addr_wit_version));
  char tmp_bech32_addr[100];
  memset(tmp_bech32_addr, 0, sizeof(tmp_bech32_addr));

  addr_wit_version[0] = ADDRESS_VER_ED25519;
  wallet_address_by_index(w, index, addr_wit_version + 1);
  address_2_bech32(addr_wit_version, "atoi", tmp_bech32_addr);
  printf("Addr[%" PRIu32 "]\n", index);
  // print ed25519 address without version filed.
  printf("\t");
  dump_hex_str(addr_wit_version + 1, ED25519_ADDRESS_BYTES);
  // print out
  printf("\t%s\n", tmp_bech32_addr);
}

int wallet_get_balance(void) {
  byte_t seed[IOTA_SEED_BYTES];
  memset(seed, 0, sizeof(seed));
  iota_wallet_t *wallet = NULL;

  random_seed(seed);
  if ((wallet = wallet_create(seed, ACCOUNT_PATH)) == NULL) {
    printf("create wallet failed\n");
  }

  // set connected node
  wallet_set_endpoint(wallet, TEST_NODE_ENDPOINT, TEST_NODE_PORT);

  for (uint32_t idx = 0; idx < 5; idx++) {
    uint64_t value = 0;
    if (wallet_balance_by_index(wallet, idx, &value) != 0) {
      printf("wallet get balance [%" PRIu32 "]failed\n", idx);
      goto done;
    }
    show_address(wallet, idx);
    printf("balance: %" PRIu64 "\n", value);
  }

done:
  wallet_destroy(wallet);
  return 0;
}
