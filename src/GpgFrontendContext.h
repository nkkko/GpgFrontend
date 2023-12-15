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

#pragma once

#include <qapplication.h>
#include <qcoreapplication.h>

#include "core/function/SecureMemoryAllocator.h"

namespace GpgFrontend {

struct GpgFrontendContext;

using GFCxtWPtr = std::weak_ptr<GpgFrontendContext>;
using GFCxtSPtr = std::shared_ptr<GpgFrontendContext>;

struct GpgFrontendContext {
  int argc;
  char** argv;
  spdlog::level::level_enum log_level;

  bool load_ui_env;
  bool gather_external_gnupg_info;
  bool load_default_gpg_context;

  GpgFrontendContext(int argc, char** argv);

  ~GpgFrontendContext();

  /**
   * @brief
   *
   */
  void InitApplication(bool);

  /**
   * @brief Get the App object
   *
   * @return QCoreApplication*
   */
  auto GetApp() -> QCoreApplication*;

  /**
   * @brief Get the Gui App object
   *
   * @return QApplication*
   */
  auto GetGuiApp() -> QApplication*;

 private:
  QCoreApplication* app_ = nullptr;
};

}  // namespace GpgFrontend