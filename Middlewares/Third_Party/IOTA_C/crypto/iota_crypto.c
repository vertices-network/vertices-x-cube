// Copyright 2020 IOTA Stiftung
// SPDX-License-Identifier: Apache-2.0

#ifdef CRYPTO_USE_SODIUM
#include "sodium.h"
#else
#include <stdint.h>
#include <string.h>
#include "ecc/cmox_eddsa.h"
#include "mac/cmox_hmac.h"
#include "blake2.h"
#endif

#include "iota_crypto.h"

extern struct __RNG_HandleTypeDef hrng;
int iota_rng_raw(void *data, uint8_t *output, size_t len);

void iota_crypto_randombytes(uint8_t *const buf, const size_t len) {
  iota_rng_raw(&hrng, buf, len);
}

// get ed25519 public and private key from address
void iota_crypto_keypair(uint8_t const seed[], iota_keypair_t *keypair) {
#ifdef CRYPTO_USE_SODIUM
  crypto_sign_seed_keypair(keypair->pub, keypair->priv, seed);
#else
  cmox_ecc_handle_t ctx; /* ECC context */
  uint8_t membuf[548]; /* minimum memory necessary to generate keys */

  /* set the memory buffer and the mathematical engine */
  cmox_ecc_construct(&ctx, CMOX_MATH_FUNCS_SUPERFAST256, membuf, sizeof(membuf));

  /* call the EdDSA key-pair generation routine */
  (void)cmox_eddsa_keyGen(&ctx, CMOX_ECC_ED25519_OPT_HIGHMEM,
                          seed, ED_SEED_BYTES,
                          keypair->priv, NULL,
                          keypair->pub, NULL);

  /* clean & destroy the context */
  cmox_ecc_cleanup(&ctx);
#endif
}

int iota_crypto_sign(uint8_t const priv_key[], uint8_t msg[], size_t msg_len, uint8_t signature[]) {
#ifdef CRYPTO_USE_SODIUM
  unsigned long long sign_len = ED_SIGNATURE_BYTES;
  return crypto_sign_ed25519_detached(signature, &sign_len, msg, msg_len, priv_key);
#else
  cmox_ecc_retval_t rv; /* CMOX return value */
  int retval = 1; /* final return value */
  cmox_ecc_handle_t ctx; /* ECC context */
  uint8_t membuf[1388]; /* minimum memory necessary to sign 1kB of data */

  /* set the memory buffer and the mathematical engine */
  cmox_ecc_construct(&ctx, CMOX_MATH_FUNCS_SUPERFAST256, membuf, sizeof(membuf));

  /* call the EdDSA signature generation routine */
  rv = cmox_eddsa_sign(&ctx, CMOX_ECC_ED25519_OPT_HIGHMEM,
                       priv_key, ED_PRIVATE_KEY_BYTES,
                       msg, msg_len,
                       signature, NULL);

  /* clean & destroy the context */
  cmox_ecc_cleanup(&ctx);

  /* set the proper return value */
  if (rv == CMOX_ECC_SUCCESS)
  {
    retval = 0;
  }

  return retval;
#endif
}

int iota_crypto_hmacsha256(uint8_t const secret_key[], uint8_t msg[], size_t msg_len, uint8_t auth[]) {
#ifdef CRYPTO_USE_SODIUM
  return crypto_auth_hmacsha256(auth, msg, msg_len, secret_key);
#else
  cmox_mac_retval_t rv; /* CMOX return value */
  int retval = 1; /* final return value */

  rv = cmox_mac_compute(CMOX_HMAC_SHA256_ALGO, /* algorithm */
                        msg, msg_len,          /* input */
                        secret_key, 32u,       /* key */
                        NULL, 0u,              /* custom data */
                        auth, 32u, NULL);      /* tag, expected length, output length */
  /* set the proper return value */
  if (rv == CMOX_MAC_SUCCESS)
  {
    retval = 0;
  }

  return retval;
#endif
}

int iota_crypto_hmacsha512(uint8_t const secret_key[], uint8_t msg[], size_t msg_len, uint8_t auth[]) {
#ifdef CRYPTO_USE_SODIUM
  return crypto_auth_hmacsha512(auth, msg, msg_len, secret_key);
#else
  cmox_mac_retval_t rv; /* CMOX return value */
  int retval = 1; /* final return value */

  rv = cmox_mac_compute(CMOX_HMAC_SHA512_ALGO, /* algorithm */
                        msg, msg_len,          /* input */
                        secret_key, 32u,       /* key */
                        NULL, 0u,              /* custom data */
                        auth, 64u, NULL);      /* tag, expected length, output length */
  /* set the proper return value */
  if (rv == CMOX_MAC_SUCCESS)
  {
    retval = 0;
  }

  return retval;
#endif
}

int iota_blake2b_sum(uint8_t const msg[], size_t msg_len, uint8_t out[], size_t out_len) {
  return crypto_generichash_blake2b(out, out_len, msg, msg_len, NULL, 0);
}
