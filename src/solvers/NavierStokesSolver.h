#if !defined(NAVIER_STOKES_SOLVER_H)
#define NAVIER_STOKES_SOLVER_H

#include "FlowDescription.h"
#include "CartesianMesh.h"
#include "SimulationParameters.h"
//#include "FractionalStepMethod.h"
#include <petscdmda.h>
#include <petscksp.h>

template <PetscInt dim>
class NavierStokesSolver
{
protected:
	// classes
	FlowDescription      *flowDesc;
	SimulationParameters *simParams;
	CartesianMesh        *mesh;
	//FractionalStepMethod FSM;
	
	PetscInt timeStep, iteratonCount1, iterationCount2;
	
	DM  uda, vda, wda, pack;
	Vec qxLocal, qyLocal, qzLocal;
	Vec H, rn;
	Vec RInv, M;

	Mat A;
	Mat QT, BNQ;
	Mat QTBNQ;
	Vec BN;
	Vec bc1, rhs1, rhs2;
	Vec q, qStar, phi;
	KSP ksp1, ksp2;

	void createDMs();
	void createVecs();
	void initialiseFluxes();
	void updateBoundaryGhosts();
	void calculateExplicitTerms();
	void generateMAndRInv();
	void generateA();
	
public:
	void initialise();
	void stepTime();
	void writeData();
	bool finished();
	
	// Factory methods are static (not entirely sure why)
	static NavierStokesSolver<dim>* createSolver(FlowDescription *FD, SimulationParameters *SP, CartesianMesh *CM);
	
	/**
	* @brief Give the name of the current solver 
	* @return String that describes the type of solver
	*/
	virtual std::string name()
	{
		return "Navier-Stokes";
	}
	
	NavierStokesSolver(FlowDescription *FD=NULL, SimulationParameters *SP=NULL, CartesianMesh *CM=NULL)
	{
		timeStep = 0;
		// classes
		flowDesc  = FD;
		simParams = SP;
		mesh      = CM;
		// DMs
		uda  = PETSC_NULL;
		vda  = PETSC_NULL;
		wda  = PETSC_NULL;
		pack = PETSC_NULL;
		// Vecs
		qxLocal = PETSC_NULL;
		qyLocal = PETSC_NULL;
		qzLocal = PETSC_NULL;
		q       = PETSC_NULL;
		qStar   = PETSC_NULL;
		H       = PETSC_NULL;
		rn      = PETSC_NULL;
		bc1     = PETSC_NULL;
		rhs1    = PETSC_NULL;
		RInv    = PETSC_NULL;
		M       = PETSC_NULL;
		// Mats
		A       = PETSC_NULL;
		BN      = PETSC_NULL;
		QT      = PETSC_NULL;
		BNQ     = PETSC_NULL;
		QTBNQ   = PETSC_NULL;
	}
	virtual ~NavierStokesSolver()
	{
		PetscErrorCode ierr;
		// DMs
		if(!uda)
		{
			ierr = DMDestroy(&uda); CHKERRV(ierr);
		}
		if(!vda)
		{
			ierr = DMDestroy(&vda); CHKERRV(ierr);
		}
		if(!wda)
		{
			ierr = DMDestroy(&wda); CHKERRV(ierr);
		}
		if(!pack)
		{
			ierr = DMDestroy(&pack); CHKERRV(ierr);
		}
		// Vecs
		if(!q)
		{
			ierr = VecDestroy(&q); CHKERRV(ierr);
		}
		if(!qStar)
		{
			ierr = VecDestroy(&qStar); CHKERRV(ierr);
		}
		if(!qxLocal)
		{
			ierr = VecDestroy(&qxLocal); CHKERRV(ierr);
		}
		if(!qyLocal)
		{
			ierr = VecDestroy(&qyLocal); CHKERRV(ierr);
		}
		if(!qzLocal)
		{
			ierr = VecDestroy(&qzLocal); CHKERRV(ierr);
		}
		if(!H)
		{
			ierr = VecDestroy(&H); CHKERRV(ierr);
		}
		if(!rn)
		{
			ierr = VecDestroy(&rn); CHKERRV(ierr);
		}
		if(!M)
		{
			ierr = VecDestroy(&M); CHKERRV(ierr);
		}
		if(!RInv)
		{
			ierr = VecDestroy(&RInv); CHKERRV(ierr);
		}
		if(!flowDesc)
			delete flowDesc;
		if(!simParams)
			delete simParams;
		if(!mesh)
			delete mesh;
	}
};

#endif
