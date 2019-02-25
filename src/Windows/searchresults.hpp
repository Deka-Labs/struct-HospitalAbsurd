#ifndef SEARCHRESULTS_HPP
#define SEARCHRESULTS_HPP

#include "ui_searchresults.h"
#include <QAbstractTableModel>
#include <QDialog>

class SearchResults : public QDialog {
    Q_OBJECT
private:
    Ui::SearchResultForm* m_ui;

public:
    SearchResults(const QString& title, QAbstractTableModel* model, QWidget* parent = nullptr);
    SearchResults(const SearchResults&) = delete;
    ~SearchResults();
};

#endif // SEARCHRESULTS_HPP
