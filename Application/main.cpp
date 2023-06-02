#include <QtWidgets/QApplication>
#include <qdebug.h>

#include "GUI.h"
#include "TestingApp.h"
#include "AbstractRepo.h"
#include "Repository.h"
#include "FileRepository.h"
#include "DatabaseRepository.h"
#include "ProductValidator.h"
#include "CosCumparaturi.h"
#include "FileCosCumparaturi.h"
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
    // IN MEMORY REPOSITORY
    if (repo_type == REPO_TYPE::IN_MEMORY_REPO)
        return make_unique<RepoProducts>();

    // FILE REPOSITORY
    if (repo_type == REPO_TYPE::FILE_REPO)
    {
        const string filename{ "produse" };
        return make_unique<FileRepoProducts>(filename);
    }
    
    // DATABASE REPOSITORY
    const auto server_name{ DBConstants::server };
    const auto username{ DBConstants::username };
    const auto password{ DBConstants::password };
    const auto database_name{ DBConstants::database };
    const auto products_table_name{ DBConstants::table };
    const auto port_number{ DBConstants::port };
    return make_unique<DatabaseRepository>(server_name, username, password, database_name, products_table_name, port_number);
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
        
        // COS DE CUMPARATURI SALVAT IN MEMORIE (IN MEMORY SHOPPING CART)
        //CosCumparaturi cos{ *repo };
        // ~COS DE CUMPARATURI SALVAT IN MEMORIE (IN MEMORY SHOPPING CART)
        
        // COS DE CUMPARATURI SALVAT IN FISIER TEXT (FILE SHOPPING CART)
        const string filename_shopping_cart{ "shopping_cart" };
        FileCosCumparaturi cos{ *repo, filename_shopping_cart };
        // ~COS DE CUMPARATURI SALVAT IN FISIER TEXT (FILE SHOPPING CART)
        
        Service srv{ *repo, valid, cos };
        const auto gui{ new GUI{ srv } };
        gui->show();

        exit_code = a.exec();
    }

    return exit_code;
}