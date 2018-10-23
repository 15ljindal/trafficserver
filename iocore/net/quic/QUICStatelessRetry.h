/** @file
 *
 *  Callbacks for Stateless Retry
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

#include "tscore/ink_inet.h"

class QUICStatelessRetry
{
public:
  static constexpr size_t MAX_TOKEN_LEN = EVP_MAX_MD_SIZE;

  static void init();
  static int generate_cookie(unsigned char *cookie, size_t *cookie_len, IpEndpoint src);
  static int verify_cookie(const unsigned char *cookie, size_t cookie_len, IpEndpoint src);
};
