/** @file
 *
 *  Stubs for QUICConfig
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
#include "ts/ink_assert.h"

#include "P_SSLConfig.h"

bool
SSLParseCertificateConfiguration(const SSLConfigParams *, SSL_CTX *)
{
  return false;
}

SSLConfigParams *
SSLConfig::acquire()
{
  return nullptr;
}

void
SSLConfig::release(SSLConfigParams *)
{
  return;
}

#include "P_SSLNextProtocolSet.h"

bool
SSLNextProtocolSet::advertiseProtocols(const unsigned char **out, unsigned *len) const
{
  return true;
}

#include "InkAPIInternal.h"
int
APIHook::invoke(int, void *)
{
  ink_assert(false);
  return 0;
}

APIHook *
APIHook::next() const
{
  ink_assert(false);
  return nullptr;
}

APIHook *
APIHooks::get() const
{
  ink_assert(false);
  return nullptr;
}

void
APIHooks::clear()
{
}

void
APIHooks::prepend(INKContInternal *cont)
{
}

void
APIHooks::append(INKContInternal *cont)
{
}
