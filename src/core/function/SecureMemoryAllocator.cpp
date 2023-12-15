/**
 * Copyright (C) 2021 Saturneric <eric@bktus.com>
 *
 * This file is part of GpgFrontend.
 *
 * GpgFrontend is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GpgFrontend is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GpgFrontend. If not, see <https://www.gnu.org/licenses/>.
 *
 * The initial version of the source code is inherited from
 * the gpg4usb project, which is under GPL-3.0-or-later.
 *
 * All the source code of GpgFrontend was modified and released by
 * Saturneric <eric@bktus.com> starting on May 12, 2021.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "SecureMemoryAllocator.h"

#include <mimalloc.h>

namespace GpgFrontend {

auto SecureMemoryAllocator::Allocate(std::size_t size) -> void* {
  auto* addr = mi_malloc(size);
  SPDLOG_TRACE("secure memory allocator trys to alloc memory, address: {}",
               static_cast<void*>(addr));
  return addr;
}

auto SecureMemoryAllocator::Reallocate(void* ptr, std::size_t size) -> void* {
  auto* addr = mi_realloc(ptr, size);
  SPDLOG_TRACE(
      "secure memory allocator trys to realloc memory, "
      "old address: {}, new address: {}",
      static_cast<void*>(ptr), static_cast<void*>(addr));
  return addr;
}

void SecureMemoryAllocator::Deallocate(void* p) { mi_free(p); }

}  // namespace GpgFrontend