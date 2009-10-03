#include "shoutcaststation.h"
#include <QDebug>

ShoutcastStation::ShoutcastStation(QString name, int id, int bitRate,
		QString genre, int listeners, QString mimeType, QString currentTrack, QString tuneIn)
: m_impl(new SCStationImpl(name, id, bitRate, genre, listeners, mimeType, currentTrack, tuneIn))
{
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
