#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TDirectoryFile.h"
#include "TStyle.h"
#include "TString.h"

#include "SANtuple.h"

#include <iostream>

#include "tdrstyle.C"
#include "CMS_lumi.C"

#include <boost/progress.hpp>


TCanvas *canvas_data_mc(TH1F * mc_xs, TH1F * cms_inclusive_xs, TString canvas, bool Logy, double minx, double maxx,double miny, double maxy, TString Labelx,TString RUN){

  TCanvas *data_mc_canvas = new TCanvas("DATA_MC_"+canvas,"DATA_MC_"+canvas,700,700);
  gStyle->SetPadBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TPad *pad1 = new TPad("pad1","This is pad1",0.,0.40,1.,1.);
  TPad *pad2 = new TPad("pad2","This is pad2",0.,0.,1.,0.40);
  pad1->SetFillColor(kWhite);
  pad2->SetFillColor(kWhite);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  gPad->SetBottomMargin(0);
  gPad->SetLeftMargin(0.15); gPad->SetRightMargin(0.03);
  gPad->SetTickx();
  if(Logy) gPad->SetLogy();
  cms_inclusive_xs->SetMarkerStyle(20);
  cms_inclusive_xs->SetMarkerColor(1);
  cms_inclusive_xs->SetLineColor(1);
  cms_inclusive_xs->SetMaximum(4000);
  cms_inclusive_xs->SetMinimum(0.5);
  cms_inclusive_xs->SetMarkerSize(0.4);
  mc_xs->SetMarkerSize(0.4);

  mc_xs->SetMarkerColor(kRed);
  mc_xs->SetLineColor(kRed);

  mc_xs->SetMarkerStyle(4);
  cms_inclusive_xs->SetMarkerStyle(2);

  //cms_inclusive_xs->GetYaxis()->SetTitle("#Events");

  cms_inclusive_xs->GetYaxis()->SetTitleOffset(1.5);
  cms_inclusive_xs->GetYaxis()->SetTitleOffset(1.5);

  cms_inclusive_xs->Draw("P");
  mc_xs->Draw("same");
  cms_inclusive_xs->Draw("Psame");
  mc_xs->SetAxisRange(-500,500,"X");
  cms_inclusive_xs->SetAxisRange(-500,500,"X");
  cms_inclusive_xs->GetXaxis()->SetRangeUser(minx,maxx);
  cms_inclusive_xs->GetYaxis()->SetRangeUser(miny,maxy);
  mc_xs->GetXaxis()->SetRangeUser(minx,maxx);

  cms_inclusive_xs->GetYaxis()->SetTitleSize(0.045);

   TLegend *leg;
   leg = new TLegend(0.62,0.62,0.95,0.82);
   leg->AddEntry(cms_inclusive_xs,"#font[62]{CMS Internal}", "");
   leg->AddEntry(mc_xs ,"Neutron Gun", "");
   leg->AddEntry(mc_xs ,"Anti-k_{T} = 0.4", "");
   leg->AddEntry(cms_inclusive_xs,"PFCHS (gen)", "p");
   leg->AddEntry(mc_xs ,"PFCHS", "p");
   leg->SetTextFont(42);
   leg->SetFillColor(kWhite);
   leg->SetLineColor(kWhite);
   leg->SetBorderSize(0);
   leg->Draw();


   pad2->cd();

     gPad->SetGrid(); gPad->SetTopMargin(0);gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.15); gPad->SetRightMargin(0.03);
   gPad->SetTickx(); gPad->SetGrid();

   //Ratio
   TH1F *ratio_histo=(TH1F*)cms_inclusive_xs->Clone();
   ratio_histo->SetTitle("PFCHS (gen)/PFCHS;"+Labelx+";PFCHS (gen)/PFCHS");
   ratio_histo->Divide(cms_inclusive_xs,mc_xs,1.,1.,"");

   ratio_histo->GetYaxis()->SetLabelSize(0.06);
   ratio_histo->GetYaxis()->SetTitleOffset(0.70);
   ratio_histo->GetYaxis()->SetTitleSize(0.06);

   //ratio_histo->SetMaximum(2.1);
   //ratio_histo->SetMinimum(-0.5);
   ratio_histo->SetMarkerStyle(2);
   ratio_histo->SetMarkerColor(kBlack);
   ratio_histo->SetLineColor(kBlack);
   ratio_histo->GetXaxis()->SetTitleSize(0.055);
   ratio_histo->GetYaxis()->SetTitleSize(0.055);

   ratio_histo->Draw("P");
   ratio_histo->GetXaxis()->SetRangeUser(minx,maxx);
   ratio_histo->GetYaxis()->SetRangeUser(0.02,2.5);

   return data_mc_canvas;
}

TCanvas *canvas_data_mc_2d(TH2F *h_2d, TString xlabel,TString ylabel, int minx, int maxx, bool bline){

    TLegend *leg;
    leg = new TLegend(0.18,0.83,0.43,0.90);
    leg->AddEntry(h_2d,"#font[62]{CMS Internal}", "");
    leg->AddEntry(h_2d,"Neutron Gun", "");

    leg->SetTextFont(42);
    leg->SetFillColor(kWhite);
    leg->SetLineColor(kWhite);
    leg->SetBorderSize(0);

    TCanvas *canvas = new TCanvas("canvas"+xlabel,"canvas"+xlabel,700,700);
    canvas->cd();
    gPad->SetRightMargin(0.15);

    h_2d->GetYaxis()->SetTitle(ylabel);
    h_2d->GetXaxis()->SetTitle(xlabel);
    h_2d->GetXaxis()->SetRangeUser(minx,maxx);
    h_2d->GetYaxis()->SetRangeUser(minx,maxx);
    h_2d->Draw("COLZ");
    leg->Draw();

    if(bline){
      TLine *l1 = new TLine(200,200,2500,2500);
      l1->SetLineColor(kRed);
      l1->SetLineWidth(2);
      l1->Draw("same");
    }
    return canvas;
}



int neutron_gun_sme(){




   setTDRStyle();

   writeExtraText = true;       // if extra text
   extraText  = "Preliminary";  // default extra text is "Preliminary"
   lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

   TString Label = "1520";
   TFile* fzvvinc = new TFile("./SIMPs_PUMoriond17_AOD_NG_"+Label+".root");
   TTree* treepfjet = (TTree*)fzvvinc->Get("tree0/SimpAnalysis");
   SANtuple c_stpfjet;
   c_stpfjet.Init(treepfjet);


   TTree* treepfjetparton = (TTree*)fzvvinc->Get("tree/SimpAnalysis");
   SANtuple c_stp2pfjet;
   c_stp2pfjet.Init(treepfjetparton);

   TH2F* h_pt = new TH2F("h_pt","h_pt",200,0,4000,200,0,4000);
   TH2F* h_pt_st = new TH2F("h_pt_st","h_pt_st",200,0,4000,200,0,4000);
   TH1F* h_dpt0_p      = new TH1F("h_dpt0_p_"+Label,"h_dpt0_p_"+Label,100,-2,2);
   TH1F* h_dpt0_pf      = new TH1F("h_dpt0_pf_"+Label,"h_dpt0_pf"+Label,100,-2,2);
 
  int nentriesp = c_stp2pfjet.fChain->GetEntries();

     for(int i=0; i<nentriesp; i++){

      c_stp2pfjet.GetEntry(i);
      c_stpfjet.GetEntry(i);

      h_pt->Fill(c_stp2pfjet.genjet_pt[0], c_stp2pfjet.jet_pt[0]);
      h_pt->Fill(c_stp2pfjet.genjet_pt[1], c_stp2pfjet.jet_pt[1]);

      h_dpt0_p->Fill((c_stp2pfjet.genjet_pt[0]-c_stp2pfjet.jet_pt[0])/c_stp2pfjet.jet_pt[0]);
      h_dpt0_p->Fill((c_stp2pfjet.genjet_pt[0]-c_stp2pfjet.jet_pt[1])/c_stp2pfjet.jet_pt[1]);

      h_dpt0_pf->Fill((c_stpfjet.genjet_pt[0]-c_stpfjet.jet_pt[0])/c_stpfjet.jet_pt[0]);
      h_dpt0_pf->Fill((c_stpfjet.genjet_pt[0]-c_stpfjet.jet_pt[1])/c_stpfjet.jet_pt[1]);

      h_pt_st->Fill(c_stpfjet.genjet_pt[0], c_stpfjet.jet_pt[0]);
      h_pt_st->Fill(c_stpfjet.genjet_pt[1], c_stpfjet.jet_pt[1]);

     }




    TCanvas *c1 = canvas_data_mc_2d(h_pt, "GENJet p_{T}", "Jet p_{T,P2PF}", 200,2500, true);
    c1->SaveAs("./Plots/NeutronGun/Smeared/pt_neutron_gun_p2pf_th2f_"+Label+".png");
    c1->SaveAs("./Plots/NeutronGun/Smeared/pt_neutron_gun_p2pf_th2f_"+Label+".pdf");
    TCanvas *c2 = canvas_data_mc_2d(h_pt_st, "GENJet p_{T} ", "Jet p_{T,PF}", 200,2500, true);
    c2->SaveAs("./Plots/NeutronGun/Smeared/pt_neutron_gun_th2f_"+Label+".png");
    c2->SaveAs("./Plots/NeutronGun/Smeared/pt_neutron_gun_th2f_"+Label+".pdf");

    TCanvas *c3 = new TCanvas("h_dpt0_p","h_dpt0_p",700,700);
    gStyle->SetPadBorderMode(0);
    gStyle->SetOptStat(11111);
    gStyle->SetOptTitle(0);
    c3->cd();
    h_dpt0_p->GetXaxis()->SetTitle("(p_{T,GEN}-p_{T,P2PF})/p_{TP2PF}");
    h_dpt0_p->Draw("");
    c3->SaveAs("./Plots/NeutronGun/Smeared/pt_neutron_gun_p2pf_res_"+Label+".png");
    c3->SaveAs("./Plots/NeutronGun/Smeared/pt_neutron_gun_p2pf_res_"+Label+".pdf");


    TCanvas *c4 = new TCanvas("h_dpt0_pf","h_dpt0_pf",700,700);
    gStyle->SetPadBorderMode(0);
    gStyle->SetOptStat(11111);
    gStyle->SetOptTitle(0);
    c4->cd();
    h_dpt0_pf->GetXaxis()->SetTitle("(p_{T,GEN}-p_{T,PF})/p_{T PF}");
    h_dpt0_pf->Draw("");
    c4->SaveAs("./Plots/NeutronGun/Smeared/pt_neutron_gun_res_"+Label+".png");
    c4->SaveAs("./Plots/NeutronGun/Smeared/pt_neutron_gun_res_"+Label+".pdf");



  return 0;
}
