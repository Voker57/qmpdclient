#ifndef SHOUTCASTSTATION_H_
#define SHOUTCASTSTATION_H_

#include <QString>
#include <QSharedPointer>
#include <QMetaType>
template<typename T> class QList;

class SCStationImpl
{
public:
	SCStationImpl(QString name, int id, int bitRate,
			QString genre, int listeners, QString mimeType, QString currentTrack, QString tuneIn)
	: m_name(name), m_id(id), m_bitRate(bitRate), m_genre(genre), m_listeners(listeners),
	  m_mimeType(mimeType), m_currentTrack(currentTrack), m_tuneIn(tuneIn) {}
	QString name() const { return m_name; }
	int id() const { return m_id; }
	int bitRate() const { return m_bitRate; }
	QString genre() const { return m_genre; }
	int listeners() const { return m_listeners; }
	QString mimeType() const { return m_mimeType; }
	QString currentTrack() const { return m_currentTrack; }
	QString tuneIn() const { return m_tuneIn; }
private:
	QString m_name;
	int m_id;
	int m_bitRate;
	QString m_genre;
	int m_listeners;
	QString m_mimeType;
	QString m_currentTrack;
	QString m_tuneIn;
};

class ShoutcastStation {
public:
	ShoutcastStation(QString name, int id, int bitRate,
			QString genre, int listeners, QString mimeType, QString currentTrack,
			QString tuneIn);
	ShoutcastStation();
	QString name() const;
	int id() const;
	int bitRate() const;
	QString genre() const;
	int listeners() const;
	QString mimeType() const;
	QString currentTrack() const;
	QString tuneIn() const;
	bool isValid() const;
	bool operator==(const ShoutcastStation & other) const;
private:
	QSharedPointer<const SCStationImpl> m_impl;
};

Q_DECLARE_METATYPE(ShoutcastStation);

bool operator<(const ShoutcastStation & lhs, const ShoutcastStation & rhs);

typedef QList<ShoutcastStation> ShoutcastStationList;

#endif /* SHOUTCASTSTATION_H_ */
