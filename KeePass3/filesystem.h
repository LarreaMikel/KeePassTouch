#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <vector>

#include "treenode.h"
#include "passwordentry.h"
#include "salsa20.h"

using namespace std;

class Filesystem : public QObject
{
    Q_OBJECT    

public:
    explicit Filesystem(QObject *parent = 0);
    ~Filesystem();
    Q_INVOKABLE void openFile(QString, QString, QString);
    Q_INVOKABLE void closeFile();    
    Q_INVOKABLE void selectBranch(QString);
    Q_INVOKABLE QString reloadBranch(QString, int);
    PasswordEntryModel* createModel();

Q_SIGNALS:
    void error(QString msg);
    void success(QVariantList vl);

protected:
    bool equal(char*, char*, uint);
    uint loadByte(char*, int);
    uint readHeaderField(char*, int, bool*);
    uint readBytes(char*, int, uint);    
    bool fileExists(const char *);
    std::string generateSHA256Hash(char*, uint);
    bool getChildBranch(QString, vector<TreeNode*>);
    bool getMyBranch(QString, vector<TreeNode*>);
    char* readFile(QString, std::streampos&);

private:
    QVariantList m_vl;
    Salsa20* salsa;
};

#endif // FILESYSTEM_H

