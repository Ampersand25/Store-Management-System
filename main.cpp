#include <QtWidgets/QApplication>
#include <qdebug.h>

#include "GUI.h"
#include "TestingApp.h"
#include "AbstractRepo.h"
#include "FileRepository.h"
#include "ProductValidator.h"
#include "Service.h"

void testApp()
{
    const TestingApp testing_app;
    testing_app.runTestsApp();

    qDebug() << "\n--------------------All tests passed--------------------\n";
}

int main(int argc, char* argv[])
{
    // Testarea aplicatiei
    testApp();

    int exit_code;

    // Asamblarea si rularea aplicatiei
    {
        QApplication a(argc, argv);

        const string filename{ "produse" };
        FileRepoProducts repo{ filename };
        ProductValidator valid;
        CosCumparaturi cos{ repo };
        Service srv{ repo, valid, cos };
        const auto gui{ new GUI{ srv } };
        gui->show();

        exit_code = a.exec();
    }

    return exit_code;
}