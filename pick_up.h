#ifndef PICK_UP_H
#define PICK_UP_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlQueryModel>

class PickUp : public QObject
{
    Q_OBJECT

public:
    explicit PickUp(int idDistribution, const QString &matiere, int idEpreuve,
                    const QDateTime& deadline = QDateTime(), QObject *parent = nullptr);

    // CRUD Operations
    bool ajouter();
    bool supprimer(int idDistribution, int idEpreuve);
    bool mettreAJour(int idDistribution, const QString &matiere, int idEpreuve, const QDateTime& deadline);
    QSqlQueryModel* afficher();

    // Getters
    int getIdDistribution() const { return m_idDistribution; }
    QString getMatiere() const { return m_matiere; }
    int getIdEpreuve() const { return m_idEpreuve; }
    QDateTime getDeadline() const { return m_deadline; }
    QString getLastError() const { return m_lastError; }

    // Setters
    void setDeadline(const QDateTime& deadline) { m_deadline = deadline; }
    static QList<QPair<int, QString>> getPickUpsEnRetard();
    static bool estMatiereValide(const QString& matiere);

private:
    bool validerDonnees() const;
    bool distributionExiste(int idDistribution) const;
    bool pickUpExiste(int idDistribution, int idEpreuve) const;

    int m_idDistribution;
    QString m_matiere;
    int m_idEpreuve;
    QDateTime m_deadline;
    QString m_lastError;
};

#endif // PICK_UP_H
