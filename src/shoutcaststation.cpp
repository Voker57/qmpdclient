#include "shoutcaststation.h"
#include <QDebug>
#include <QMetaType>

ShoutcastStation::ShoutcastStation(QString name, int id, int bitRate,
		QString genre, int listeners, QString mimeType, QString currentTrack, QString tuneIn)
: m_impl(new SCStationImpl(name, id, bitRate, genre, listeners, mimeType, currentTrack, tuneIn))
{
	qRegisterMetaType<ShoutcastStation>("ShoutcastStation");
}

ShoutcastStation::ShoutcastStation()
: m_impl(0)
{
	qRegisterMetaType<ShoutcastStation>("ShoutcastStation");
}

bool ShoutcastStation::isValid() const
{
	return m_impl;
}

QString ShoutcastStation::name() const
{
	return m_impl->name();
}

int ShoutcastStation::id() const
{
	return m_impl->id();
}

int ShoutcastStation::bitRate() const
{
	return m_impl->bitRate();
}

QString ShoutcastStation::genre() const
{
	return m_impl->genre();
}

int ShoutcastStation::listeners() const
{
	return m_impl->listeners();
}

QString ShoutcastStation::mimeType() const
{
	return m_impl->mimeType();
}

QString ShoutcastStation::currentTrack() const
{
	return m_impl->currentTrack();
}

QString ShoutcastStation::tuneIn() const
{
	return m_impl->tuneIn();
}

bool ShoutcastStation::operator==(const ShoutcastStation & other) const
{
	return other.id() == id();
}

bool operator<(const ShoutcastStation & lhs, const ShoutcastStation & rhs)
{
	return lhs.id() < rhs.id();
}
