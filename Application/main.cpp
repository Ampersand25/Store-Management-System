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

void testApp()
{
    const TestingApp testing_app;
    testing_app.runTestsApp();

    qDebug() << "\n--------------------All tests passed--------------------\n";
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
        //RepoProducts repo{};

        // FILE REPOSITORY
        const string filename{ "produse" };
        FileRepoProducts repo{ filename };
        
        // DATABASE REPOSITORY
        //const auto server{ DBConstants::server };
        //const auto username{ DBConstants::username };
        //const auto password{ DBConstants::password };
        //const auto database{ DBConstants::database };
        //const auto table{ DBConstants::table };
        //DatabaseRepository repo{ server, username, password, database, table };
        
        ProductValidator valid;
        CosCumparaturi cos{ repo };
        Service srv{ repo, valid, cos };
        const auto gui{ new GUI{ srv } };
        gui->show();

        exit_code = a.exec();
    }

    return exit_code;
}