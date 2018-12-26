/** @file
 *
 *  A key generator for QUIC connection
 *
 *  @section license License
 *
 *  Licensed to the Apache Software Foundation (ASF) under one
 *  or more contributor license agreements.  See the NOTICE file
 *  distributed with this work for additional information
 *  regarding copyright ownership.  The ASF licenses this file
 *  to you under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in compliance
 *  with the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#pragma once

#include <openssl/evp.h>
#include "QUICTypes.h"
#include "QUICHKDF.h"

#ifdef OPENSSL_IS_BORINGSSL
typedef EVP_AEAD QUIC_EVP_CIPHER;
#else
typedef EVP_CIPHER QUIC_EVP_CIPHER;
#endif // OPENSSL_IS_BORINGSSL

struct KeyMaterial {
  // These constant sizes are not enough somehow
  // uint8_t key[EVP_MAX_KEY_LENGTH] = {0};
  // uint8_t iv[EVP_MAX_IV_LENGTH]   = {0};
  uint8_t key[512] = {0};
  uint8_t iv[512]  = {0};
  uint8_t pn[512]  = {0};
  size_t key_len   = 512;
  size_t iv_len    = 512;
  size_t pn_len    = 512;
};

class QUICKeyGenerator
{
public:
  enum class Context { SERVER, CLIENT };

  QUICKeyGenerator(Context ctx) : _ctx(ctx) {}

  /**
   * Generate keys for Initial encryption level
   * The keys for the remaining encryption level are derived by TLS stack with "quic " prefix
   */
  std::unique_ptr<KeyMaterial> generate(QUICConnectionId cid);

  std::unique_ptr<KeyMaterial> regenerate(const uint8_t *secret, size_t secret_len, const QUIC_EVP_CIPHER *cipher, QUICHKDF &hkdf);

private:
  Context _ctx = Context::SERVER;

  uint8_t _last_secret[256];
  size_t _last_secret_len = 0;

  int _generate(KeyMaterial &km, QUICHKDF &hkdf, const uint8_t *secret, size_t secret_len, const QUIC_EVP_CIPHER *cipher);
  int _generate_initial_secret(uint8_t *out, size_t *out_len, QUICHKDF &hkdf, QUICConnectionId cid, const char *label,
                               size_t label_len, size_t length);
  int _generate_key(uint8_t *out, size_t *out_len, QUICHKDF &hkdf, const uint8_t *secret, size_t secret_len,
                    size_t key_length) const;
  int _generate_iv(uint8_t *out, size_t *out_len, QUICHKDF &hkdf, const uint8_t *secret, size_t secret_len, size_t iv_length) const;
  int _generate_pn(uint8_t *out, size_t *out_len, QUICHKDF &hkdf, const uint8_t *secret, size_t secret_len, size_t pn_length) const;
  size_t _get_key_len(const QUIC_EVP_CIPHER *cipher) const;
  size_t _get_iv_len(const QUIC_EVP_CIPHER *cipher) const;
  const QUIC_EVP_CIPHER *_get_cipher_for_initial() const;
  const QUIC_EVP_CIPHER *_get_cipher_for_protected_packet(const SSL *ssl) const;
};
