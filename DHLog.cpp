#include "DHLog.h"
#include "MessageLog/Public/MessageLogModule.h"

DEFINE_LOG_CATEGORY(DHhan);
void CreateLog(FName logName)
{
    static bool bCreatedLogMessage = false;
    if (!bCreatedLogMessage) {
        FMessageLogModule& messageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
        FMessageLogInitializationOptions initOptions;
        initOptions.bShowPages = true;
        initOptions.bShowFilters = true;
        FText logListingName = LOCTEXT("DHLogMassege", "DHLogMassege");
        messageLogModule.RegisterLogListing(logName, logListingName, initOptions);
        bCreatedLogMessage = true;
    }
}