#include "valuespacesubscriber.h"
#include <QDebug>
ValueSpaceSubscriber::ValueSpaceSubscriber(QObject *parent) :
    QObject(parent)
{
    m_subscriber = new QtMobility::QValueSpaceSubscriber( this );
}


ValueSpaceSubscriber::~ValueSpaceSubscriber()
{
    delete m_subscriber;
}

void ValueSpaceSubscriber::setPath(const QString path)
{
    QString tpath = path.trimmed();
    if (!m_path.isEmpty() && m_path == tpath) {
        return;
    }
    m_path = tpath;
    m_subscriber->setPath(m_path);

    disconnect(m_subscriber, SIGNAL(contentsChanged()),this,0);
    connect(m_subscriber, SIGNAL(contentsChanged()), this, SIGNAL(contentsChanged()));
    connect(m_subscriber,SIGNAL(contentsChanged()), this, SLOT(onContentsChanged()));
    emit pathChanged();
}

QVariant ValueSpaceSubscriber::value() const
{
    return getValue(QString() );
}

QVariant ValueSpaceSubscriber::getValue(QString subPath ) const
{
    if(!m_subscriber->isConnected()) {
        return QVariant();
    }
    return m_subscriber->value(subPath);
}

void ValueSpaceSubscriber::onContentsChanged()
{
    if (m_value != getValue(QString()))
    {
        m_value = value();
        emit valueChanged();
    }
}
