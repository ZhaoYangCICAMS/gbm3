//------------------------------------------------------------------------------
//
 //  File:       gbmDataContainer.h
//
//  Description:   Header file for a class that stores the data and dist for gbm.
//
//------------------------------------------------------------------------------


#ifndef GBMDATACONTAINER_H
#define GBMDATACONTAINER_H

//------------------------------
// Includes
//------------------------------
#include "buildinfo.h"
#include "configStructs.h"
#include "dataset.h"
#include "distribution.h"
#include "distributionFactory.h"
#include "gbmTreeComps.h"
#include <Rcpp.h>
#include <vector>
#include <memory>

//------------------------------
// Class definition
//------------------------------
class CGBMDataContainer
{
public:
	//----------------------
	// Public Constructors
	//----------------------
    CGBMDataContainer(DataDistParams& dataDistConfig);

	//---------------------
	// Public destructor
	//---------------------
    ~CGBMDataContainer();

    //---------------------
	// Public Functions
	//---------------------
    void Initialize();
    double InitialFunctionEstimate();
    void ComputeResiduals(const double* adF, double* adZ);
    void ComputeBestTermNodePreds(const double* adF, double* adZ, CTreeComps& pTreeComp);
    double ComputeDeviance(const double *adF, bool isValidationSet=false);
    double ComputeBagImprovement(const double* adF, const double shrinkage, const double* adFadj);
    void BagData();
    CDistribution* getDist();
    
    const CDataset& getData() const {
      return data;
    }

    CDataset& getData() { return data; }

private:
	//-------------------
	// Private Variables
	//-------------------
    CDataset data;
    CDistribution* pDist;
    DistributionFactory* DistFactory;
    std::multimap<int, int> patIdToRow; // Map from patientID to row
};

#endif // GBMDATACONTAINER_H
