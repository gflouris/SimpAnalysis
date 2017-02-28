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


#include "SANtuple.h"




int skimmer(){


  TChain *oldtree = new TChain("tree/SimpAnalysis");

  for(int i=1; i<30; i++){

   stringstream a;
   a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT2000ToInf_PUMoriond17/170115_224959/0000/QCD_PUMoriond17_test_";
    //a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT1500To2000_PUMoriond17/170115_224939/0000/QCD_PUMoriond17_test_";
		//a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT1000To1500_PUMoriond17/170115_224913/0000/QCD_PUMoriond17_test_";
		//a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT700To1000_PUMoriond17/170115_224853/0000/QCD_PUMoriond17_test_";

    a<<i; a<<".root";
    oldtree->Add((a.str()).c_str());
  }


  SANtuple c_tree;
  c_tree.Init(oldtree);

  Long64_t nentries = oldtree->GetEntries();

  oldtree->SetBranchStatus("*",1);

  const double eta_cut = 2.0, dphi_cut= 2.0, pt_cut = 250.;


   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile("ROOTFiles/SIMPs_QCD_HT2000ToInf_PUMoriond17.root","recreate");
   TDirectory *dir1 = newfile->mkdir("tree");
   dir1->cd();
   TTree *newtree = oldtree->CloneTree(0);

   for (Long64_t i=0;i<nentries; i++) {

    c_tree.GetEntry(i);
    if(i%100000 == 0) cout<<i<<" / "<<nentries<<"\r"<<flush;
      ///Object Selection

      double deltajet_phi = c_tree.jet_phi[0] - c_tree.jet_phi[1];
      if(deltajet_phi > TMath::Pi()) deltajet_phi -= 2*TMath::Pi();
      if(deltajet_phi < -TMath::Pi()) deltajet_phi += 2*TMath::Pi();


    if(c_tree.jet_pt[0]>pt_cut && c_tree.jet_pt[1]>pt_cut && fabs(c_tree.jet_eta[0])<eta_cut && fabs(c_tree.jet_eta[1])<eta_cut && deltajet_phi>dphi_cut){
            newtree->Fill();
    }

   }






   newtree->Print();
   newfile->Write("", TObject::kOverwrite);
   newfile->Close();
   //delete oldfile;
   //delete newfile;


   return 0;
}
