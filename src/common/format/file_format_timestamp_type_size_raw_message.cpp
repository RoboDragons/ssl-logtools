/***************************************************************************
 *   Copyright (c) 2013 Robotics Erlangen e.V.                             *
 *   http://www.robotics-erlangen.de/                                      *
 *   info@robotics-erlangen.de                                             *
 *                                                                         *
 *   This file may be licensed under the terms of the GNU General Public   *
 *   License Version 3, as published by the Free Software Foundation.      *
 *   You can find it here: http://www.gnu.org/licenses/gpl.html            *
 *                                                                         *
 ***************************************************************************/

#include "file_format_timestamp_type_size_raw_message.h"
#include <QtCore/QDataStream> // 修正: QDataStreamのインクルードを追加
#include <QtCore/QString>     // 修正: QStringのインクルードを追加
#include <QtCore/QByteArray>  // 修正: QByteArrayのインクルードを追加

FileFormatTimestampTypeSizeRawMessage::FileFormatTimestampTypeSizeRawMessage() :
    FileFormat(1)
{

}

FileFormatTimestampTypeSizeRawMessage::~FileFormatTimestampTypeSizeRawMessage()
{

}

void FileFormatTimestampTypeSizeRawMessage::writeHeaderToStream(QDataStream& stream)
{
    stream.writeRawData("SSL_LOG_FILE", 12);
    stream << (qint32) version();
}

bool FileFormatTimestampTypeSizeRawMessage::readHeaderFromStream(QDataStream& stream)
{
    char name[13];
    name[12] = '\0';
    stream.readRawData(name, sizeof(name) - 1);

    qint32 version;
    stream >> version;

    if (QString(name) == "SSL_LOG_FILE" && version == this->version()) { // 修正: QStringの使用
        return true;
    }

    return false;
}

void FileFormatTimestampTypeSizeRawMessage::writeMessageToStream(QDataStream& stream, const QByteArray& data, qint64 time, MessageType type)
{
    stream << time;
    stream << (qint32) type;
    stream.writeRawData(data.data(), data.size()); // 修正: QByteArrayのデータを直接書き込む
}

bool FileFormatTimestampTypeSizeRawMessage::readMessageFromStream(QDataStream& stream, QByteArray& data, qint64& time, MessageType& type)
{
    stream >> time;
    qint32 typeValue;
    stream >> typeValue;
    type = (MessageType) typeValue;

    qint32 dataSize;
    stream >> dataSize;
    data.resize(dataSize);
    stream.readRawData(data.data(), dataSize); // 修正: QByteArrayのデータを直接読み込む

    return true;
}