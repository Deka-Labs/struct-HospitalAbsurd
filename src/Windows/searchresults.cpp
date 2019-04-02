#include "searchresults.hpp"

SearchResults::SearchResults(const QString& title, QAbstractTableModel* model, QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr) {
    m_ui = new Ui::SearchResultForm;
    m_ui->setupUi(this);

    this->setWindowTitle(title);
    m_ui->tableView->setModel(model);
    m_ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

SearchResults::~SearchResults() {
    delete m_ui;
}
