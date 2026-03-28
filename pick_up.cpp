#include "pick_up.h"
#include <QDebug>
#include <QSqlError>

PickUp::PickUp(int idDistribution, const QString &matiere, int idEpreuve,
               const QDateTime& deadline, QObject *parent)
    : QObject(parent),
    m_idDistribution(idDistribution),
    m_matiere(matiere.trimmed()),
    m_idEpreuve(idEpreuve),
    m_deadline(deadline),
    m_lastError("")
{
}

bool PickUp::validerDonnees() const
{
    if(m_idDistribution <= 0) {
        m_lastError == "ID Distribution invalide";
        return false;
    }

    if(m_idEpreuve <= 0) {
        m_lastError == "ID Épreuve invalide";
        return false;
    }
    if(!m_deadline.isValid()) {
        m_lastError == "Deadline invalide";
        return false;
    }
    if(!estMatiereValide(m_matiere)) {
        m_lastError == "Matière invalide";
        return false;
    }
    return true;
    return true;
}

bool PickUp::distributionExiste(int idDistribution) const
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM BADIS.DISTRIBUTION WHERE ID_DISTRIBUTION = :id");
    query.bindValue(":id", idDistribution);

    if(!query.exec()) {
        m_lastError == "Erreur vérification distribution: " + query.lastError().text();
        return false;
    }

    return query.next();
}

bool PickUp::pickUpExiste(int idDistribution, int idEpreuve) const
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM BADIS.PICK_UP WHERE ID_DISTRIBUTION = :idDist AND ID_EPREUVE = :idEpreuve");
    query.bindValue(":idDist", idDistribution);
    query.bindValue(":idEpreuve", idEpreuve);

    if(!query.exec()) {
        m_lastError == "Erreur vérification pick-up: " + query.lastError().text();
        return false;
    }

    return query.next();
}

bool PickUp::ajouter()
{
    if(!validerDonnees()) {
        return false;
    }

    if(!distributionExiste(m_idDistribution)) {
        return false;
    }

    if(pickUpExiste(m_idDistribution, m_idEpreuve)) {
        m_lastError = "Un pick-up existe déjà pour cette distribution et épreuve";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO BADIS.PICK_UP (ID_DISTRIBUTION, MATIERE, ID_EPREUVE, DEADLINE) "
                  "VALUES (:idDist, :matiere, :idEpreuve, TO_DATE(:deadline, 'YYYY-MM-DD HH24:MI:SS'))");

    query.bindValue(":idDist", m_idDistribution);
    query.bindValue(":matiere", m_matiere);
    query.bindValue(":idEpreuve", m_idEpreuve);
    query.bindValue(":deadline", m_deadline.toString("yyyy-MM-dd HH:mm:ss"));

    if(!query.exec()) {
        m_lastError = "Erreur d'insertion: " + query.lastError().text();
        return false;
    }

    return true;
}

bool PickUp::supprimer(int idDistribution, int idEpreuve)
{
    if(idDistribution <= 0 || idEpreuve <= 0) {
        m_lastError = "IDs invalides";
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM BADIS.PICK_UP WHERE ID_DISTRIBUTION = :idDist AND ID_EPREUVE = :idEpreuve");
    query.bindValue(":idDist", idDistribution);
    query.bindValue(":idEpreuve", idEpreuve);

    if(!query.exec()) {
        m_lastError = "Erreur de suppression: " + query.lastError().text();
        return false;
    }

    if(query.numRowsAffected() == 0) {
        m_lastError = "Aucun pick-up trouvé avec ces identifiants";
        return false;
    }

    return true;
}

bool PickUp::mettreAJour(int idDistribution, const QString &matiere, int idEpreuve, const QDateTime& deadline)
{
    QString matiereTrimmed = matiere.trimmed();

    if(idDistribution <= 0 || matiereTrimmed.isEmpty() || idEpreuve <= 0 || !deadline.isValid()) {
        m_lastError = "Données invalides";
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE BADIS.PICK_UP SET "
                  "MATIERE = :matiere, "
                  "DEADLINE = TO_DATE(:deadline, 'YYYY-MM-DD HH24:MI:SS') "
                  "WHERE ID_DISTRIBUTION = :idDist AND ID_EPREUVE = :idEpreuve");

    query.bindValue(":matiere", matiereTrimmed);
    query.bindValue(":deadline", deadline.toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":idDist", idDistribution);
    query.bindValue(":idEpreuve", idEpreuve);

    if(!query.exec()) {
        m_lastError = "Erreur de mise à jour: " + query.lastError().text();
        return false;
    }

    if(query.numRowsAffected() == 0) {
        m_lastError = "Aucun pick-up trouvé avec ces identifiants";
        return false;
    }

    return true;
}

QSqlQueryModel* PickUp::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();

    QString req = "SELECT p.ID_DISTRIBUTION, p.MATIERE, p.ID_EPREUVE, "
                  "TO_CHAR(p.DEADLINE, 'DD/MM/YYYY HH24:MI') as DATE_LIMITE, "
                  "CASE "
                  "  WHEN p.DEADLINE < SYSDATE THEN 'Expiré' "
                  "  ELSE FLOOR((p.DEADLINE - SYSDATE) * 24 * 60) || ' minutes' "
                  "END as TEMPS_RESTANT "
                  "FROM BADIS.PICK_UP p "
                  "ORDER BY p.DEADLINE";

    model->setQuery(req);

    if(model->lastError().isValid()) {
        qDebug() << "Erreur requête PICK_UP:" << model->lastError().text();
    }

    // Debug: Afficher les noms des colonnes
    for(int i = 0; i < model->columnCount(); ++i) {
        qDebug() << "Colonne" << i << ":" << model->headerData(i, Qt::Horizontal).toString();
    }

    return model;
}

QList<QPair<int, QString>> PickUp::getPickUpsEnRetard() {
    QList<QPair<int, QString>> result;

    QSqlQuery query;
    query.prepare("SELECT p.ID_DISTRIBUTION, p.MATIERE "
                  "FROM PICK_UP p "
                  "WHERE p.DEADLINE < SYSDATE");

    if(query.exec()) {
        while(query.next()) {
            result.append(qMakePair(query.value(0).toInt(),
                                    query.value(1).toString()));
        }
    } else {
        qDebug() << "Erreur requête pick-ups en retard:" << query.lastError();
    }

    return result;
}

bool PickUp::estMatiereValide(const QString& matiere)
{
    static const QStringList matieresValides = {
        "Arabe", "Français", "Anglais",
        "Mathématiques", "Physique", "SVT"
    };
    return matieresValides.contains(matiere);
}
