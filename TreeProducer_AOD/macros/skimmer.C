#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TDirectoryFile.h"
#include "TDirectory.h"
#include "TCut.h"
#include "TBranch.h"
#include "TString.h"
#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include <algorithm>
#include "TH1F.h"
#include "TMath.h"

#include <vector>


#include "classes/SANtuple.h"




int skimmer(){


  TChain *oldtree = new TChain("treeCorr/SimpAnalysis");
  TChain *oldspvtree = new TChain("treeSPV/SimpAnalysis");

  for(int f=1; f<320; f++){

   stringstream a;
   //a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT500To700_ext_PUMoriond17_AOD/170304_204358/0000/QCD_PUMoriond17_AOD_test_";
   //a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT500To700_ext_PUMoriond17_AOD/170304_204358/0001/QCD_PUMoriond17_AOD_test_";

//a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT300To500_ext_PUMoriond17_AOD/170304_203936/0000/QCD_PUMoriond17_AOD_test_";
   //a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT300To500_ext_PUMoriond17_AOD/170304_203936/0001/QCD_PUMoriond17_AOD_test_";
//a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT2000ToInf_ext_PUMoriond17_AOD/170304_205523/0000/QCD_PUMoriond17_AOD_test_";
a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT1500To2000_ext_PUMoriond17_AOD/170305_211505/0000/QCD_PUMoriond17_AOD_test_";
//a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT700To1000_ext_PUMoriond17_AOD/170304_204556/0000/QCD_PUMoriond17_AOD_test_";
//a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT1000To1500_ext_PUMoriond17_AOD/170304_204853/0000/QCD_PUMoriond17_AOD_test_";

//a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT2000ToInf_PUMoriond17_AOD/170304_213629/0000/QCD_PUMoriond17_AOD_test_";
//a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT1500To2000_PUMoriond17_AOD/170305_211927/0000/QCD_PUMoriond17_AOD_test_";
//a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT1000To1500_PUMoriond17_AOD/170304_211150/0000/QCD_PUMoriond17_AOD_test_";
//a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT700To1000_PUMoriond17_AOD/170305_212329/0000/QCD_PUMoriond17_AOD_test_";
     //a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT500To700_PUMoriond17_AOD/170304_210449/0000/QCD_PUMoriond17_AOD_test_";
   //a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT300To500_PUMoriond17_AOD/170304_210059/0000/QCD_PUMoriond17_AOD_test_";


   //a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT2000ToInf_PUMoriond17_AOD/170304_213629/0000/QCD_PUMoriond17_AOD_test_";
//   a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT2000ToInf_PUMoriond17/170115_224959/0000/QCD_PUMoriond17_test_";
    //a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT1500To2000_PUMoriond17/170115_224939/0000/QCD_PUMoriond17_test_";
		//a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT1000To1500_PUMoriond17/170115_224913/0000/QCD_PUMoriond17_test_";
		//a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT700To1000_PUMoriond17/170115_224853/0000/QCD_PUMoriond17_test_";

    a<<f; a<<".root";
    //cout<<a.str()<<endl;
    oldtree->Add((a.str()).c_str());
    oldspvtree->Add((a.str()).c_str());

  }

  SANtuple c_tree, c_spvtree;
  c_tree.Init(oldtree);
  c_spvtree.Init(oldspvtree);

  Long64_t nentries = oldtree->GetEntries();
  cout<<nentries<<endl;


  oldtree->SetBranchStatus("*",1);
  oldspvtree->SetBranchStatus("*",1);

  const double eta_cut = 2.0, dphi_cut= 2.0, pt_cut = 200.;

   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile("SIMPs_QCD_HT1500To2000_PUMoriond17_ext.root","recreate");
   TDirectory *dir1 = newfile->mkdir("treeCorr");
   dir1->cd();
   TTree *newtree = oldtree->CloneTree(0);

   TDirectory *dir2 = newfile->mkdir("treeSPV");
   dir2->cd();
   TTree *newspvtree = oldspvtree->CloneTree(0);



   for (Long64_t i=0;i<nentries; i++) {
   //for (Long64_t i=0;i<1; i++) {

    c_tree.GetEntry(i);
    c_spvtree.GetEntry(i);

    if(i%100000 == 0) cout<<i<<" / "<<nentries<<"\r"<<flush;
      ///Object Selection

      double deltajet_phi = c_tree.jet_phi[0] - c_tree.jet_phi[1];
      if(deltajet_phi > TMath::Pi()) deltajet_phi -= 2*TMath::Pi();
      if(deltajet_phi < -TMath::Pi()) deltajet_phi += 2*TMath::Pi();



    if(c_tree.jet_pt[0]>pt_cut && c_tree.jet_pt[1]>pt_cut && fabs(c_tree.jet_eta[0])<eta_cut && fabs(c_tree.jet_eta[1])<eta_cut && fabs(deltajet_phi)>dphi_cut){
      newtree->Fill();
	    newspvtree->Fill();
    }

   }






   newtree->Print();
   newfile->Write("", TObject::kOverwrite);
   newfile->Close();
   //delete oldfile;
   //delete newfile;


   return 0;
}
