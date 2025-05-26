#pragma once
#include <string>
#include "addTransaction.h"

class ExportReport {
public:
    static bool exportTransactionsToCSV(const TransactionManager& transactionMgr, 
                                        const string& filename = "transactions_export.csv",
                                        const string& startDate = "0000-00-00",
                                        const string& endDate = "9999-99-99");
};
