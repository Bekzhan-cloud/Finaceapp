#pragma once
#include <string>
#include "addTransaction.h"

class Analytics {
public:
    void showSummary(const TransactionManager& transactionMgr) const;
    void showCategoryStats(const TransactionManager& transactionMgr) const;
    void showSummaryPeriod(const TransactionManager& transactionMgr, const string& start, const string& end) const;
    void showCategoryStatsPeriod(const TransactionManager& transactionMgr, const string& start, const string& end) const;
};
