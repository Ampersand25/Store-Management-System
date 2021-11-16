#include "TestingApp.h"
#include "TestingDomain.h"
#include "TestingRepo.h"
#include "TestingFileRepo.h"
#include "TestingExceptionRepo.h"
#include "TestingValidation.h"
#include "TestingUtils.h"
#include "TestingService.h"
#include "TestingCosCumparaturi.h"
#include "TestingUndo.h"

void TestingApp::runTestsApp() const
{
	// Testarea layerului/stratului Domain (domeniul aplicatiei, unde sunt definite entitatile modelate de aplicatie)
	{
		TestingDomain testing_domain;
		testing_domain.runTestsDomain();
	}

	// Testarea layerului/stratului Infrastructure/Repository (leyerul/stratul de persistenta a datelor, unde sunt stocate inregistrarile din aplicatie)
	{
		// Testare repository (repozitoriu) fara fisiere (cu salvare in memorie)
		{
			TestingRepo testing_repo;
			testing_repo.runTestsRepo();
		}

		// Testare repository (repozitoriu) cu fisiere text
		{
			TestingFileRepo testing_file_repo;
			testing_file_repo.runTestsFileRepo();
		}

		// Testare repository (repozitoriu) de exceptii (arunca exceptie cu o anumita probabilitate data in constructor)
		{
			TestingExceptionRepo testing_exception_repo;
			testing_exception_repo.runTestsExceptionRepo();
		}
	}

	// Testarea layerului/stratului Validation (leyerul/stratul de validare a datelor)
	{
		ProductValidator valid;

		const TestingValidation testing_validation{ valid };
		testing_validation.runTestsProductValidator();
	}

	// Testarea layerului/stratului Utils (leyerul/stratul unde sunt declarate si definite functii utilitare/generice)
	{
		Utils utils;

		const TestingUtils testing_utils{ utils };
		testing_utils.runTestsUtils();
	}

	// Testarea layerului/stratului Business/Service (leyerul/stratul unde se valideaza datele introduse de utilizator in UI si se executa comenzi, adica GRASP Controllerul aplicatiei)
	{
		ProductValidator valid;

		const TestingService testing_service{ valid };
		testing_service.runTestsService();
	}

	// Testarea clasei CosCumparaturi si a metodelor aferente (metode publice)
	{
		RepoProducts repo;
		CosCumparaturi cos_cumparaturi{ repo };
		
		const TestingCosCumparaturi testing_cos_cumparaturi{ cos_cumparaturi, repo };
		testing_cos_cumparaturi.runTestsCosCumparaturi();
	}

	// Testarea claselor care fac undo (clase derivate din clasa de baza ActiuneUndo)
	{
		TestingUndo testing_undo;
		testing_undo.runTestsUndo();
	}
}