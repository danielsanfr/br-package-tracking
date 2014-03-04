#ifndef PACKAGEINFOMODEL_H
#define PACKAGEINFOMODEL_H

#include <QObject>
#include <QString>

namespace brpackagetracking {
namespace model {
class Information : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged FINAL)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged FINAL)
    Q_PROPERTY(QString situation READ situation WRITE setSituation NOTIFY situationChanged FINAL)
public:
    explicit Information(QString date, QString location, QString situation, QObject *parent = 0);
    Information(const Information &other);
    explicit Information(QObject *parent = 0);
    Q_INVOKABLE QString date() const;
    Q_INVOKABLE void setDate(QString newDate);
    Q_INVOKABLE QString location() const;
    Q_INVOKABLE void setLocation(QString newLocation);
    Q_INVOKABLE QString situation() const;
    Q_INVOKABLE void setSituation(QString newSituation);
    Information &operator=(const Information &other);
signals:
    void dateChanged();
    void locationChanged();
    void situationChanged();
public slots:
private:
    QString m_date;
    QString m_location;
    QString m_situation;
};
}
}

#endif // PACKAGEINFOMODEL_H
