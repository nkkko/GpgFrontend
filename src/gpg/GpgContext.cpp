/**
 * This file is part of GPGFrontend.
 *
 * GPGFrontend is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 *
 * The initial version of the source code is inherited from gpg4usb-team.
 * Their source code version also complies with GNU General Public License.
 *
 * The source code version of this software was modified and released
 * by Saturneric<eric@bktus.com> starting on May 12, 2021.
 *
 */

#include "gpg/GpgContext.h"
#include "GpgConstants.h"

#include <functional>

#ifdef _WIN32
#include <windows.h>
#endif

#define INT2VOIDP(i) (void *)(uintptr_t)(i)

namespace GpgFrontend {

/**
 * Constructor
 *  Set up gpgme-context, set paths to app-run path
 */
GpgContext::GpgContext() {

  static bool _first = true;

  if (_first) {
    /* Initialize the locale environment. */
    setlocale(LC_ALL, "");
    gpgme_check_version(nullptr);
    gpgme_set_locale(nullptr, LC_CTYPE, setlocale(LC_CTYPE, nullptr));
#ifdef LC_MESSAGES
    gpgme_set_locale(nullptr, LC_MESSAGES, setlocale(LC_MESSAGES, nullptr));
#endif
    _first = false;
  }

  gpgme_ctx_t _p_ctx;
  check_gpg_error(gpgme_new(&_p_ctx));
  _ctx_ref = CtxRefHandler(_p_ctx);

  LOG(INFO) << "GpgContext _ctx_ref Created";

  auto engineInfo = gpgme_ctx_get_engine_info(*this);

  LOG(INFO) << "GpgContext gpgme_ctx_get_engine_info Called";

  // Check ENV before running
  bool check_pass = false, find_openpgp = false, find_gpgconf = false,
       find_assuan = false, find_cms = false;
  while (engineInfo != nullptr) {
    LOG(INFO) << gpgme_get_protocol_name(engineInfo->protocol) << " "
              << engineInfo->file_name << " " << engineInfo->version;

    if (engineInfo->protocol == GPGME_PROTOCOL_GPGCONF &&
        strcmp(engineInfo->version, "1.0.0") != 0)
      find_gpgconf = true;
    if (engineInfo->protocol == GPGME_PROTOCOL_OpenPGP &&
        strcmp(engineInfo->version, "1.0.0") != 0)
      find_openpgp = true, info.appPath = engineInfo->file_name;
    if (engineInfo->protocol == GPGME_PROTOCOL_CMS &&
        strcmp(engineInfo->version, "1.0.0") != 0)
      find_cms = true;
    if (engineInfo->protocol == GPGME_PROTOCOL_ASSUAN)
      find_assuan = true;
    engineInfo = engineInfo->next;
  }

  if (find_gpgconf && find_openpgp && find_cms && find_assuan)
    check_pass = true;

  LOG(INFO) << "GpgContext check_pass " << check_pass;
  if (!check_pass) {
    good_ = false;
    return;
  } else {
    /** Setting the output type must be done at the beginning */
    /** think this means ascii-armor --> ? */
    gpgme_set_armor(*this, 1);
    // Speed up loading process
    gpgme_set_offline(*this, 1);

    check_gpg_error(gpgme_set_keylist_mode(
        *this, GPGME_KEYLIST_MODE_LOCAL | GPGME_KEYLIST_MODE_WITH_SECRET |
                   GPGME_KEYLIST_MODE_SIGS | GPGME_KEYLIST_MODE_SIG_NOTATIONS |
                   GPGME_KEYLIST_MODE_WITH_TOFU));
    good_ = true;
  }
}

bool GpgContext::good() const { return good_; }

void GpgContext::SetPassphraseCb(decltype(test_passphrase_cb) cb) const {
  gpgme_set_passphrase_cb(*this, cb, nullptr);
}

std::string GpgContext::getGpgmeVersion() {
  return {gpgme_check_version(nullptr)};
}

} // namespace GpgFrontend