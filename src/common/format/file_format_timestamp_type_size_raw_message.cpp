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
#include <QString>
#include <QByteArray>

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

    if (QString::fromLatin1(name) == QLatin1String("SSL_LOG_FILE") && version == this->version()) {
        return true;
    }

    return false;
}

void FileFormatTimestampTypeSizeRawMessage::writeMessageToStream(QDataStream& stream, const QByteArray& data, qint64 time, MessageType type)
{
    stream << time;
    stream << (qint32) type;
    stream << static_cast<qint32>(data.size());
    if (!data.isEmpty()) {
        stream.writeRawData(data.constData(), data.size());
    }
}

bool FileFormatTimestampTypeSizeRawMessage::readMessageFromStream(QDataStream& stream, QByteArray& data, qint64& time, MessageType& type)
{
    stream >> time;
    qint32 typeValue;
    stream >> typeValue;
    type = (MessageType) typeValue;
    qint32 size = 0;
    stream >> size;
    data.clear();
    if (size > 0) {
        data.resize(size);
        int readBytes = stream.readRawData(data.data(), size);
        if (readBytes != size) {
            return false;
        }
    }
    return true;
}
