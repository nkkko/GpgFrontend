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

#ifndef GPGFRONTEND_FILEPAGE_H
#define GPGFRONTEND_FILEPAGE_H

#include <GpgFrontend.h>

class FilePage : public QWidget  {
Q_OBJECT
public:

    explicit FilePage(QWidget* parent = nullptr);

    void getSelected(QString &path);


private slots:

    void fileTreeViewItemClicked(const QModelIndex &index);
    void fileTreeViewItemDoubleClicked(const QModelIndex &index);

    void slotUpLevel();

private:
    QFileSystemModel *dirModel;
    QTreeView *dirTreeView;
    QString mPath;

    QPushButton *upLevelButton;

};


#endif //GPGFRONTEND_FILEPAGE_H