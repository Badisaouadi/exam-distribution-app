#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>
#include <QDateTime>
#include <QSerialPort>

class Distribution : public QObject {
    Q_OBJECT

public:
    Distribution(int idDistribution, int idCentreRegional, const QString& etat,
                 const QDateTime& dateDebut = QDateTime(),
                 const QDateTime& dateFin = QDateTime(),
                 QObject *parent = nullptr);

    QSqlQueryModel* afficher();
    static bool etatValide(const QString& etat);
    bool ajouter();
    bool supprimer(int id);
    bool mettreAJour(int id, const QString& etat, const QDateTime& dateDebut, const QDateTime& dateFin);

    QDateTime dateDebut() const;
    QDateTime dateFin() const;
    QString getLastError() const;  // Déclaration de la méthode
    static QList<QPair<int, QString>> getDistributionsEnRetard();
signals:
    void distributionEnRetard(int id, const QString& centre);
    //void activerBuzzer();

private:
    int idDistribution;
    int idCentreRegional;
    QString etat;
    QDateTime m_dateDebut;
    QDateTime m_dateFin;
    QString lastError;  // Variable membre pour stocker la dernière erreur
};

#endif // DISTRIBUTION_H
