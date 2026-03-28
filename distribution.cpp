#include "distribution.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

// Mettez à jour le constructeur pour inclure les dates
Distribution::Distribution(int idDistribution, int idCentreRegional,
                           const QString& etat, const QDateTime& dateDebut,
                           const QDateTime& dateFin, QObject *parent)
    : QObject(parent),
    idDistribution(idDistribution),
    idCentreRegional(idCentreRegional),
    etat(etat),
    m_dateDebut(dateDebut),
    m_dateFin(dateFin),
    lastError("") {}  // Initialisation de lastError

QString Distribution::getLastError() const {
    return lastError;
}

// Ajoutez les implémentations des getters
QDateTime Distribution::dateDebut() const {
    return m_dateDebut;
}

QDateTime Distribution::dateFin() const {
    return m_dateFin;
}

bool Distribution::etatValide(const QString& etat) {
    return etat == "pas encore" || etat == "en cours" || etat == "distribuée";
}

// Mettez à jour ajouter() pour inclure les dates
bool Distribution::ajouter() {
    if(!etatValide(etat)) {
        lastError = "Erreur: État invalide";
        qDebug() << lastError;
        return false;
    }
    /*if(idDistribution <= 0) {
        lastError = "Erreur: ID Distribution doit être > 0";
        qDebug() << lastError;
        return false;
    }*/

    QSqlQuery query;
    query.prepare("INSERT INTO BADIS.DISTRIBUTION (ID_DISTRIBUTION, ID_CENTREREGIONAL, ETAT, DATE_DEBUT, DATE_FIN) "
                  "VALUES (:idDistribution, :idCentreRegional, :etat, :dateDebut, :dateFin)");

    query.bindValue(":idDistribution", idDistribution);
    query.bindValue(":idCentreRegional", idCentreRegional);
    query.bindValue(":etat", etat);
    query.bindValue(":dateDebut", m_dateDebut);
    query.bindValue(":dateFin", m_dateFin);

    if(!query.exec()) {
        lastError = query.lastError().text();
        qDebug() << "Erreur insertion Distribution:" << lastError;
        return false;
    }
    return true;
}

bool Distribution::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM DISTRIBUTION WHERE ID_DISTRIBUTION = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur de suppression :" << query.lastError().text();
        return false;
    }
    return true;
}

bool Distribution::mettreAJour(int id, const QString& etat, const QDateTime& dateDebut, const QDateTime& dateFin) {
    if(!etatValide(etat)) {
        qDebug() << "Erreur: État invalide";
        return false;
    }
    QSqlQuery query;
    query.prepare("UPDATE DISTRIBUTION SET ETAT = :etat, DATE_DEBUT = :dateDebut, DATE_FIN = :dateFin WHERE ID_DISTRIBUTION = :id");
    query.bindValue(":id", id);
    query.bindValue(":etat", etat);
    query.bindValue(":dateDebut", dateDebut);
    query.bindValue(":dateFin", dateFin);

    if (!query.exec()) {
        qDebug() << "Erreur de mise à jour :" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Distribution::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();

    QString sql = "SELECT d.ID_DISTRIBUTION, c.NOM, d.ETAT, "
                  "TO_CHAR(d.DATE_DEBUT, 'DD/MM/YYYY HH24:MI') as DATE_DEBUT, "
                  "TO_CHAR(d.DATE_FIN, 'DD/MM/YYYY HH24:MI') as DATE_FIN, "
                  "CASE "
                  "  WHEN d.ETAT = 'distribuée' THEN 'Terminé' "
                  "  WHEN d.DATE_FIN < SYSDATE AND d.ETAT != 'distribuée' THEN 'En retard' "
                  "  ELSE TO_CHAR(TRUNC((d.DATE_FIN - SYSDATE) * 24 * 60)) || ' minutes' "
                  "END as TEMPS_RESTANT "
                  "FROM BADIS.DISTRIBUTION d "
                  "JOIN BADIS.CENTRE c ON d.ID_CENTREREGIONAL = c.ID_CENTRE "
                  "ORDER BY d.ID_DISTRIBUTION";

    model->setQuery(sql);

    if(model->lastError().isValid()) {
        qDebug() << "Erreur requête Distribution:" << model->lastError().text();
    }

    model->setHeaderData(0, Qt::Horizontal, "ID Distribution");
    model->setHeaderData(1, Qt::Horizontal, "Nom du Centre");
    model->setHeaderData(2, Qt::Horizontal, "État");
    model->setHeaderData(3, Qt::Horizontal, "Date début");
    model->setHeaderData(4, Qt::Horizontal, "Date fin");
    model->setHeaderData(5, Qt::Horizontal, "Temps restant");

    return model;
}
QList<QPair<int, QString>> Distribution::getDistributionsEnRetard() {
    QList<QPair<int, QString>> result;

    QSqlQuery query;
    query.prepare("SELECT d.ID_DISTRIBUTION, c.NOM "
                  "FROM DISTRIBUTION d "
                  "JOIN CENTRE c ON d.ID_CENTREREGIONAL = c.ID_CENTRE "
                  "WHERE d.DATE_FIN < SYSDATE AND d.ETAT != 'distribuée'");

    if(query.exec()) {
        while(query.next()) {
            result.append(qMakePair(query.value(0).toInt(),
                                    query.value(1).toString()));
        }
    } else {
        qDebug() << "Erreur requête distributions en retard:" << query.lastError();
    }

    return result;
}
/*void Distribution::activerBuzzer()
{
    QSerialPort serial;
    serial.setPortName("COM3");
    if (!serial.open(QIODevice::WriteOnly)) {
        qDebug() << "Erreur d'ouverture du port série.";
        return;
    }
    serial.write("1"); // Envoie le signal pour activer le buzzer
    serial.flush(); // Vide le buffer d'écriture
    serial.waitForBytesWritten(100); // Attend que l'envoi soit terminé (100 ms)
    serial.close();
}
*/
