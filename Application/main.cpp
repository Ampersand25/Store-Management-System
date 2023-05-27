#include <QtWidgets/QApplication>
#include <qdebug.h>

#include "GUI.h"
#include "TestingApp.h"
#include "AbstractRepo.h"
#include "Repository.h"
#include "FileRepository.h"
#include "DatabaseRepository.h"
#include "ProductValidator.h"
#include "Service.h"
#include "Constants.h"

#include <memory>

using std::unique_ptr;
using std::make_unique;

// VARIANTA I
//typedef enum {
//    IN_MEMORY_REPO = 0,
//    FILE_REPO = 1,
//    DATABASE_REPO = 2
//} REPO_TYPE;

// VARIANTA II
enum REPO_TYPE {
    IN_MEMORY_REPO,
    FILE_REPO,
    DATABASE_REPO
};

void testApp()
{
    const TestingApp testing_app;
    testing_app.runTestsApp();

    qDebug() << "\n--------------------All tests passed--------------------\n";
}

unique_ptr<AbstractRepo> repoFactory(REPO_TYPE repo_type) {
    if (repo_type == REPO_TYPE::IN_MEMORY_REPO)
        return make_unique<RepoProducts>();

    if (repo_type == REPO_TYPE::FILE_REPO)
    {
        const string filename{ "produse" };
        return make_unique<FileRepoProducts>(filename);
    }
    
    // VARIANTA I
    /*if (repo_type == REPO_TYPE::DATABASE_REPO)
    {
        const auto server{ DBConstants::server };
        const auto username{ DBConstants::username };
        const auto password{ DBConstants::password };
        const auto database{ DBConstants::database };
        const auto table{ DBConstants::table };
        return make_unique<DatabaseRepository>(server, username, password, database, table);
    }*/

    // VARIANTA II
    const auto server{ DBConstants::server };
    const auto username{ DBConstants::username };
    const auto password{ DBConstants::password };
    const auto database{ DBConstants::database };
    const auto table{ DBConstants::table };
    return make_unique<DatabaseRepository>(server, username, password, database, table);
}

int main(int argc, char* argv[])
{
    // Testarea aplicatiei
    //testApp();

    int exit_code;

    // Asamblarea si rularea aplicatiei
    {
        QApplication a(argc, argv);
        
        // IN MEMORY REPOSITORY
        //const auto repo_type{ REPO_TYPE::IN_MEMORY_REPO };
        // ~IN MEMORY REPOSITORY

        // FILE REPOSITORY
        //const auto repo_type{ REPO_TYPE::FILE_REPO };
        // ~FILE REPOSITORY

        // DATABASE REPOSITORY
        const auto repo_type{ REPO_TYPE::DATABASE_REPO };
        // ~DATABASE REPOSITORY

        auto repo{ repoFactory(repo_type) }; // <=> unique_ptr<AbstractRepo> repo{ repoFactory(repo_type) };

        ProductValidator valid;
        CosCumparaturi cos{ *repo };
        Service srv{ *repo, valid, cos };
        const auto gui{ new GUI{ srv } };
        gui->show();
        gui->disableInfoTipuri(repo_type == REPO_TYPE::DATABASE_REPO);

        exit_code = a.exec();
    }

    return exit_code;
}