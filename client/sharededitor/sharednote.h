/*
    Cahoots is a crossplatform real-time collaborative text editor.

    Copyright (C) 2010 Chris Dimpfl, Anandi Hira, David Vega

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTextStream>

#include "document.h"
#include "finddialog.h"
#include "findtoolbar.h"
//#include "preferencesdialog.h"

class Player;
class NetworkMessageReader;
class NetworkMessageWriter;

namespace Ui
{
    class SharedNote;
}

class SharedNote : public QMainWindow
{
    Q_OBJECT

public:
    SharedNote(QWidget* parent= nullptr);
    ~SharedNote();

    bool saveFileAsText(QTextStream& out);
    bool loadFileAsText(QTextStream& out, bool md);

    bool saveFile(QDataStream& out);
    bool loadFile(QDataStream& fileName);

    void setCurrentFile(const QString& fileName);
    QString strippedName(const QString& fullFileName);

    void readSettings();
    void writeSettings();

    void displaySharingPanel();
    void setOwnerId(const QString& id);

    QString id() const;
    void setId(const QString& id);

    void readFromMsg(NetworkMessageReader* msg);
    void runUpdateCmd(QString cmd);

    QString fileName() const;
    void setFileName(const QString& fileName);

public slots:
    void updateDocumentToAll(NetworkMessageWriter* msg);
    void textHasChanged(int pos, int charsRemoved, int charsAdded);

    void playerPermissionsChanged(QString, int);
    void writeToAll(QString string);
    void populateDocumentForUser(QString id);
    void closeEditorFor(QString idplayer);

protected:
    void closeEvent(QCloseEvent* event);
    bool eventFilter(QObject*, QEvent* event);

    void updateWindowTitle();
private slots:
    //  bool fileSaveAs();

    void on_actionFile_Print_triggered();

    void on_actionEdit_Undo_triggered();
    void on_actionEdit_Redo_triggered();
    void on_actionEdit_Cut_triggered();
    void on_actionEdit_Copy_triggered();
    void on_actionEdit_Paste_triggered();
    void on_actionEdit_Find_All_triggered();
    void on_actionEdit_Find_triggered();

    void on_actionView_Line_Wrap_triggered();
    void on_actionView_Hide_Show_Participants_triggered();
    void on_actionTools_Preview_as_Html_triggered();
    void on_actionText_Shift_Left_triggered();
    void on_actionText_Shift_Right_triggered();
    void on_actionText_Comment_Line_triggered();

    void setUndoability(bool b);
    void setRedoability(bool b);

    void documentChanged();
    void tabCloseClicked();

    void findNextTriggered(QString str, Qt::CaseSensitivity, bool wrapAround, Enu::FindMode mode);
    void findPrevTriggered(QString str, Qt::CaseSensitivity, bool wrapAround, Enu::FindMode mode);
    void replaceAllTriggered(QString find, QString replace, Qt::CaseSensitivity sensitivity, Enu::FindMode mode);
    void replaceTriggered(QString replace);
    void findReplaceTriggered(
        QString find, QString replace, Qt::CaseSensitivity sensitivity, bool wrapAround, Enu::FindMode mode);

    void setEditorFont(QFont font);
    void setParticipantsFont(QFont font);

    void setMarkdownAsHighlight();

private:
    Ui::SharedNote* ui = nullptr;
    FindDialog* findDialog = nullptr;
    QString m_fileName;
    Document* m_document = nullptr;
    bool m_networkEditing= false;
    QString m_id; // global name used for connecting to documents
};

#endif // MAINWINDOW_H
