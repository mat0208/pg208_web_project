#ifndef STATISTICS_H
#define STATISTICS_H

#include <QStringList>


class Statistics
{
public:
    Statistics();

    unsigned int nbReceivedRequests;
    unsigned int nbTreatedRequests;
    unsigned int nb404Errors;
    unsigned int nb503Errors;
    unsigned int nbConnectedClients;
    unsigned int nbTransmittedBytes;
    unsigned int nbReceivedBytes;
    QStringList receivedRequests;
    QStringList downloadedFiles;

    void clearStats();
};

#endif // STATISTICS_H
