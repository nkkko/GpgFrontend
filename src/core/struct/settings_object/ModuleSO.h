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

namespace GpgFrontend {

struct ModuleSO {
  QString module_id;
  QString module_version;
  QString module_hash;
  bool auto_activate;

  ModuleSO() = default;

  explicit ModuleSO(const QJsonObject& j) {
    if (const auto v = j["module_id"]; v.isString()) {
      module_id = v.toString();
    }

    if (const auto v = j["module_version"]; v.isString()) {
      module_version = v.toString();
    }

    if (const auto v = j["module_hash"]; v.isString()) {
      module_hash = v.toString();
    }

    if (const auto v = j["auto_activate"]; v.isBool()) {
      auto_activate = v.toBool();
    }
  }

  [[nodiscard]] auto ToJson() const -> QJsonObject {
    QJsonObject j;
    j["module_id"] = module_id;
    j["module_version"] = module_version;
    j["module_hash"] = module_hash;
    j["auto_activate"] = auto_activate;
    return j;
  }
};
}  // namespace GpgFrontend