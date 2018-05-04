#include "Statistics.h"

Statistics::Statistics()
{
    clearStats();
}

void Statistics::clearStats(){
    nbReceivedRequests = 0;
    nbTreatedRequests  = 0;
    nb404Errors        = 0;
    nb503Errors        = 0;
    nbConnectedClients = 0;
    nbTransmittedBytes = 0;
    nbReceivedBytes    = 0;
    receivedRequests.clear();
    downloadedFiles.clear();
}
