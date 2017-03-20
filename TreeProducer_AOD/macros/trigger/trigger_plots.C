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


#include "../classes/SANtuple.h"




int trigger_plots(){

   //TString Label="XXTo4J_ctau100_M700";
   TString Label="QCD";
   TFile *fin = TFile::Open("Efficiency_"+Label+".root");
   fin->cd();


    TEfficiency *pt_eff = new TEfficiency("pt_eff_05","pt_eff_05",80,400,800);
    pt_eff->SetPassedHistogram(*(TH1F*)fin->Get("h_pt_05"),"f");
    pt_eff->SetTotalHistogram(*(TH1F*)fin->Get("h_pt_05_den"),"f");
    TCanvas *c1 = new TCanvas("c1","c1",800,600);
    c1->cd();
    pt_eff->SetTitle("HLT_DiCentralPFJet330_CFMax0p5; Jet p_{T2}; Efficiency");
    pt_eff->Draw();



    TEfficiency *pt_eff03 = new TEfficiency("pt_eff_03","pt_eff_03",80,400,800);
    pt_eff03->SetPassedHistogram(*(TH1F*)fin->Get("h_pt_03"),"f");
    pt_eff03->SetTotalHistogram(*(TH1F*)fin->Get("h_pt_03_den"),"f");
    TCanvas *c2 = new TCanvas("c2","c2",800,600);
    c2->cd();
    pt_eff03->SetTitle("HLT_DiCentralPFJet220_CFMax0p3; Jet p_{T2}; Efficiency");
    pt_eff03->Draw();

    TEfficiency *pt_eff_01 = new TEfficiency("pt_eff_01","pt_eff_01",80,400,800);
    pt_eff_01->SetPassedHistogram(*(TH1F*)fin->Get("h_pt_01"),"f");
    pt_eff_01->SetTotalHistogram(*(TH1F*)fin->Get("h_pt_01_den"),"f");
    TCanvas *c3 = new TCanvas("c3","c3",800,600);
    c3->cd();
    pt_eff_01->SetTitle("HLT_DiCentralPFJet170_CFMax0p1; Jet p_{T2}; Efficiency");
    pt_eff_01->Draw();





    TEfficiency *chf_eff_01 = new TEfficiency("chf_eff_01","chf_eff_01;Max ChF;#epsilon;",20,0,1);
    chf_eff_01->SetPassedHistogram(*(TH1F*)fin->Get("h_chf_01"),"f");
    chf_eff_01->SetTotalHistogram(*(TH1F*)fin->Get("h_chf_01_den"),"f");
    TCanvas *c4 = new TCanvas("c4","c4",800,600);
    c4->cd();
    chf_eff_01->SetTitle("HLT_DiCentralPFJet170_CFMax0p1; Max ChF; Efficiency");
    chf_eff_01->Draw();


    TEfficiency *chf_eff_03 = new TEfficiency("chf_eff_03","chf_eff_03;Max ChF;#epsilon;",20,0,1);
    chf_eff_03->SetPassedHistogram(*(TH1F*)fin->Get("h_chf_03"),"f");
    chf_eff_03->SetTotalHistogram(*(TH1F*)fin->Get("h_chf_03_den"),"f");
    TCanvas *c5 = new TCanvas("c5","c5",800,600);
    c5->cd();
    chf_eff_03->SetTitle("HLT_DiCentralPFJet220_CFMax0p3; Max ChF; Efficiency");
    chf_eff_03->Draw();

    TEfficiency *chf_eff_05 = new TEfficiency("chf_eff_05","chf_eff_05;Max ChF;#epsilon;",20,0,1);
    chf_eff_05->SetPassedHistogram(*(TH1F*)fin->Get("h_chf_05"),"f");
    chf_eff_05->SetTotalHistogram(*(TH1F*)fin->Get("h_chf_05_den"),"f");
    TCanvas *c6 = new TCanvas("c6","c6",800,600);
    c6->cd();
    chf_eff_05->SetTitle("HLT_DiCentralPFJet330_CFMax0p5; Max ChF; Efficiency");
    chf_eff_05->Draw();


    c1->SaveAs("pt_eff_05_"+Label+".png");
    c1->SaveAs("pt_eff_05_"+Label+".pdf");
    c2->SaveAs("pt_eff_03_"+Label+".png");
    c2->SaveAs("pt_eff_03_"+Label+".pdf");
    c3->SaveAs("pt_eff_01_"+Label+".png");
    c3->SaveAs("pt_eff_01_"+Label+".pdf");

    c4->SaveAs("chf_eff_01_"+Label+".png");
    c4->SaveAs("chf_eff_01_"+Label+".pdf");
    c5->SaveAs("chf_eff_03_"+Label+".png");
    c5->SaveAs("chf_eff_03_"+Label+".pdf");
    c6->SaveAs("chf_eff_05_"+Label+".png");
    c6->SaveAs("chf_eff_05_"+Label+".pdf");


    // TCanvas *c7 = new TCanvas("c7","c7",800,600);
    // c7->cd();
    // h_chf_01_den->Draw();
    //


    return 0;
}
