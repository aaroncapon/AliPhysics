
void AddTask_LMeeCocktailMC(Int_t CollisionSystem = 200,
                            Float_t MaxEta = 0.8,
                            Float_t MinPt  = 0.2,
                            Float_t MaxPt  = 8.0,
                            Bool_t useCustomBinning = kFALSE,
                            Bool_t WriteTTree = kFALSE,
                            Int_t ResolType = 2 ,
                            Int_t ALTweightType = 1,
                            TString resFileName = "") {

  // ================= Load Librariers =================================
  gSystem->Load("libCore");
  gSystem->Load("libTree");
  gSystem->Load("libGeom");
  gSystem->Load("libVMC");
  gSystem->Load("libPhysics");
  gSystem->Load("libMinuit");
  gSystem->Load("libSTEERBase");
  gSystem->Load("libESD");
  gSystem->Load("libAOD");
  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");  
  gSystem->Load("libCDB");
  gSystem->Load("libSTEER");
  gSystem->Load("libSTEERBase");
  gSystem->Load("libTender");
  gSystem->Load("libTenderSupplies");
  gSystem->Load("libPWGflowBase");
  gSystem->Load("libPWGflowTasks");
  gSystem->Load("libPWGGAGammaConv");

  // ================== GetAnalysisManager ===============================
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    Error("AddTask_LMeeCocktailMC", "No analysis manager found.");
    return ;
  }

  // ================== GetInputEventHandler =============================
  AliVEventHandler *inputHandler=mgr->GetInputEventHandler();
  //            find input container
  AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();

  //================================================
  //========= Add task to the ANALYSIS manager =====
  //================================================

  AliAnalysisTaskLMeeCocktailMC* task = new AliAnalysisTaskLMeeCocktailMC(Form("LMeeCocktailMC_%1.2f",MaxEta));
  task->SetCollisionSystem(CollisionSystem);
  task->SetMaxEta(MaxEta);
  task->SetMinPt(MinPt);
  task->SetMaxPt(MaxPt);
  task->SetWriteTTree(WriteTTree);
  task->SetResolType(ResolType);
  task->SetALTweight(ALTweightType);
  if(resFileName != ""){
    Printf("Set resolution file name to %s",resFileName.Data());
    task->SetResFileName(resFileName);
  }

  // Get binning from central file
  /* TString configBasePath("$ALICE_PHYSICS/PWGDQ/dielectron/macrosLMEE/"); */
  /* TString configFile = "Config_acapon.C"; */
  /* if(!gROOT->GetListOfGlobalFunctions()->FindObject(configFile.Data())){ */
  /*   gROOT->LoadMacro(configFilePath.Data()); */
  /* } */
  if(useCustomBinning){
    std::vector<Float_t> massBins = {"0.00, 0.02, 0.04, 0.10, 0.14, 0.18, 0.24, 0.28, 0.34, 0.38,"
                                      "0.44, 0.50, 0.60, 0.70, 0.76, 0.80, 0.86, 0.90, 0.96, 1.00,"
                                      "1.04, 1.10, 1.40, 1.70, 2.00, 2.40, 2.70, 2.80, 2.90, 3.00,"
                                      "3.10, 3.30, 3.50, 4.00, 5.00"};
    std::vector<Float_t> pairPtBins = {"0.00, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45,"
                                      "0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.85, 0.90, 0.95,"
                                      "1.00, 1.10, 1.20, 1.30, 1.40, 1.50, 1.60, 1.70, 1.80, 1.90,"
                                      "2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90,"
                                      "3.00, 3.10, 3.20, 3.30, 3.40, 3.50, 3.60, 3.70, 3.80, 3.90,"
                                      "4.00, 4.10, 4.20, 4.30, 4.40, 4.50, 5.00, 5.50, 6.00, 6.50,"
                                      "7.00, 8.00, 10.0"};
    task->UseCustomBinning(kTRUE);
    task->SetCustomMassBins(massBins);
    task->SetCustomPairPtBins(pairPtBins);
  }
  
  //connect containers
  AliAnalysisDataContainer *coutput =
  mgr->CreateContainer(Form("LMeeCocktailMC_%1.2f",MaxEta), TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s:LMeeCocktailMC",AliAnalysisManager::GetCommonFileName()));
    
  mgr->AddTask(task);
  mgr->ConnectInput(task,0,cinput);
  mgr->ConnectOutput(task,1,coutput);
  
  return;
}
