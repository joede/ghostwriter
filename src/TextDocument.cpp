/***********************************************************************
 *
 * Copyright (C) 2014, 2015 wereturtle
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

#include <QString>
#include <QTextDocument>
#include <QPlainTextDocumentLayout>
#include <QFileInfo>

#include "TextDocument.h"

TextDocument::TextDocument(QObject* parent)
    : QTextDocument(parent)
{
    QPlainTextDocumentLayout* documentLayout =
        new QPlainTextDocumentLayout(this);
    this->setDocumentLayout(documentLayout);

    filePath = QString();
    readOnlyFlag = false;
    displayName = tr("untitled");
    timestamp = QDateTime::currentDateTime();
}

TextDocument::~TextDocument()
{

}

QString TextDocument::getDisplayName() const
{
    return displayName;
}

QString TextDocument::getFilePath() const
{
    return filePath;
}

void TextDocument::setFilePath(const QString& path)
{
    if (!path.isNull() && !path.isEmpty())
    {
        QFileInfo fileInfo(path);
        if (fileInfo.exists())
        {
            filePath = fileInfo.absoluteFilePath();
            displayName = fileInfo.fileName();
        }
        else
        {
            // TODO: how do I get the basename and full path of an not existing file?
        }
    }
    else
    {
        filePath = QString();
        this->setReadOnly(false);
        this->setModified(false);
        displayName = tr("untitled");
    }

    emit filePathChanged();
}

/* Check if a file is "new". We call a file "new", if the given path is empty, or the referenced
 * file (path) does not exist.
 */
bool TextDocument::isNew() const
{
    return filePath.isNull() || filePath.isEmpty() || !existsOnDisk();
}

bool TextDocument::isReadOnly() const
{
    return readOnlyFlag;
}

bool TextDocument::existsOnDisk() const
{
    QFileInfo fileInfo(filePath);
    return fileInfo.exists();
}

void TextDocument::setReadOnly(bool readOnly)
{
    readOnlyFlag = readOnly;
}

QDateTime TextDocument::getTimestamp() const
{
    return timestamp;
}

void TextDocument::setTimestamp(const QDateTime& timestamp)
{
    this->timestamp = timestamp;
}
