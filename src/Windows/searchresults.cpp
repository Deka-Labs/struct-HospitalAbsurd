#include "searchresults.hpp"

SearchResults::SearchResults(const QString& title, QAbstractTableModel* model, QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr) {
    m_ui = new Ui::SearchResultForm;
    m_ui->setupUi(this);

    this->setWindowTitle(title);
    m_ui->tableView->setModel(model);
}

SearchResults::~SearchResults() {
    delete m_ui;
}
