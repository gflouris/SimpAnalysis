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

#include "../classes/SANtuple.h"

#include <iostream>

#include "../classes/tdrstyle.C"
#include "../classes/CMS_lumi.C"

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



int conversions(){




   setTDRStyle();

   writeExtraText = true;       // if extra text
   extraText  = "Preliminary";  // default extra text is "Preliminary"
   lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

   TString Label = "_7001000";
   TFile* fzvvinc = new TFile("../../test/output_tree_SPV_QCD"+Label+".root");
   TTree* treepfjet = (TTree*)fzvvinc->Get("treeCorr/SimpAnalysis");
   SANtuple ctuple;
   ctuple.Init(treepfjet);

   TTree* treepfjetspv = (TTree*)fzvvinc->Get("treeSPV/SimpAnalysis");
   SANtuple ctuplespv;
   ctuplespv.Init(treepfjetspv);


   int passed_eta_cut = 0;
 	int passed_pt_cut = 0;
 	int passed_dphi_cut = 0;
 	int passed_photon_cut = 0;
  int passed_conv_cut = 0;
  int passed_spv_cut = 0;

  TH1F *h_pass_chf = new TH1F("h_pass_chf", "h_pass_chf", 200, -1, 10 );
  TH2F *h2_pass_chf = new TH2F("h2_pass_chf", "h2_pass_chf", 100, 0, 1,  100, 0, 1);

  TH1F *h_dis_chf = new TH1F("h_dis_chf", "h_dis_chf", 100, 0, 1 );


  int nentriesp = ctuple.fChain->GetEntries();

     for(int i=0; i<nentriesp; i++){

      ctuple.GetEntry(i);
      ctuplespv.GetEntry(i);

      if(ctuple.jet_pt[0]>250. && ctuple.jet_pt[1]>250.)     passed_pt_cut++;
  		else continue;

      if(fabs(ctuple.jet_eta[0])<2. and fabs(ctuple.jet_eta[1])<2.)     passed_eta_cut++;
  		else continue;

  		double deltajet_phi = deltaPhi(ctuple.jet_phi[0], ctuple.jet_phi[1]);
  		if(fabs(deltajet_phi) > 2.0) passed_dphi_cut++;
  		else continue;

      double lphoton_pt = 0, lphoton_eta = -100, lphoton_phi = -100;
      int lphoton_id;
      for(int p=0; p<4; p++){
        if(ctuple.photon_pt[p]>lphoton_pt) {
          lphoton_pt = ctuple.photon_pt[p];
          lphoton_eta = ctuple.photon_eta[p];
          lphoton_phi = ctuple.photon_phi[p];
          lphoton_id = p;
        }
      }

  		double dR1 = deltaR(lphoton_eta, lphoton_phi, ctuple.jet_eta[0], ctuple.jet_phi[0]);
      double dR2 = deltaR(lphoton_eta, lphoton_phi, ctuple.jet_eta[1], ctuple.jet_phi[1]);

      if(ctuple.photon_passLooseId[lphoton_id] == 0 or (ctuple.photon_passLooseId[lphoton_id] == 1 && dR1 > 0.1 && dR2 > 0.1)) passed_photon_cut++;
  		else continue;

      bool pass_conv_1 = true;
      bool pass_conv_2 = true;

      if(ctuple.jet_efrac_photon[0]>0.8 and ctuple.convtracks_pt[lphoton_id]/ctuple.photon_pt[lphoton_id] > 0.3 and dR1<0.2) pass_conv_1 = false;
      if(ctuple.jet_efrac_photon[1]>0.8 and ctuple.convtracks_pt[lphoton_id]/ctuple.photon_pt[lphoton_id] > 0.3 and dR2<0.2) pass_conv_2 = false;

      //if(ctuple.jet_efrac_photon[0]>0.8) {
      if(!pass_conv_1){
        cout<<"Leading"<<endl;
        cout<<ctuple.convtracks_pt[lphoton_id]/ctuple.photon_pt[lphoton_id]<<"\t"<<dR1<<endl;
        cout<<ctuple.genjet_efrac_ch[0]<<"\t"<<(ctuple.jet_efrac_ch_EM[0]+ctuple.jet_efrac_ch_Had[0]+ctuple.jet_efrac_ch_Mu[0])<<endl<<endl;
      }
      //if(ctuple.jet_efrac_photon[1]>0.8) {
      if(!pass_conv_2){
        cout<<"Sub-Leading"<<endl;
        cout<<ctuple.convtracks_pt[lphoton_id]/ctuple.photon_pt[lphoton_id]<<"\t"<<dR2<<endl;
        cout<<ctuple.genjet_efrac_ch[1]<<"\t"<<(ctuple.jet_efrac_ch_EM[1]+ctuple.jet_efrac_ch_Had[1]+ctuple.jet_efrac_ch_Mu[1])<<endl<<endl;
      }

      if(pass_conv_1 and pass_conv_2) passed_conv_cut++;
      else continue;

      double pfr = (ctuple.jet_efrac_ch_EM[0]+ctuple.jet_efrac_ch_Had[0]+ctuple.jet_efrac_ch_Mu[0]);

      for(int j=0; j<2; j++){
        for(int g=0; g<8; g++){
          if(ctuple.genjet_pt[g]==0) continue;

          if(deltaR(ctuple.jet_eta[j], ctuple.jet_phi[j], ctuple.genjet_eta[g], ctuple.genjet_phi[g] ) < 0.2 ){
            double gfr = ctuple.genjet_efrac_ch[g];
            double pfr = (ctuple.jet_efrac_ch_EM[j]+ctuple.jet_efrac_ch_Had[j]+ctuple.jet_efrac_ch_Mu[j]);
            double pfr_spv = (ctuplespv.jet_efrac_ch_EM[j]+ctuplespv.jet_efrac_ch_Had[j]+ctuplespv.jet_efrac_ch_Mu[j]);
            //if(pfr==0){
            if(pfr_spv>pfr) continue;

            passed_spv_cut++;
            if(pfr/gfr>30 or pfr/gfr<0.2) {

              cout<<"event "<<ctuple.nEvent<<"   lumi "<<ctuple.nLumi<<endl;
              cout<<"reco: "<<ctuple.jet_eta[j]<<"\t"<<ctuple.jet_phi[j]<<"\t"<<ctuple.jet_pt[j]<<"\t"<<ctuple.jet_efrac_photon[j]<<endl;
              cout<<"gen: "<<ctuple.genjet_eta[g]<<"\t"<<ctuple.genjet_phi[g]<<"\t"<<ctuple.genjet_pt[g]<<endl;
              cout<<gfr<<"\t"<<pfr<<"\t"<<pfr_spv<<"\t"<<pfr/gfr<<endl<<endl;
              h_dis_chf->Fill(pfr);
            }
            h_pass_chf->Fill(pfr/gfr);
            h2_pass_chf->Fill(pfr, gfr);
          //  h_dis_chf->Fill(ctuple.jet_e[j]/ctuple.jet_pt[j]);

          }
        }
      }


    }

    cout<<"Total = "<<nentriesp<<endl;
  	cout<<"passed_pt_cut = "<<passed_pt_cut<<endl;
    cout<<"passed_eta_cut = "<<passed_eta_cut<<endl;
  	cout<<"passed_dphi_cut = "<<passed_dphi_cut<<endl;
  	cout<<"passed_photon_cut = "<<passed_photon_cut<<endl;
    cout<<"passed_conv_cut = "<<passed_conv_cut<<endl;
    cout<<"passed_spv_cut = "<<passed_spv_cut<<endl;



  //     cout<<"==========jets==========="<<endl;
   //
  //     for(int j=0; j<8; j++){
  //       cout<<ctuple.jet_pt[j]<<"\t"<<ctuple.jet_eta[j]<<"\t"<<ctuple.jet_phi[j]<<endl;
  //     }
  //     cout<<"========photons============="<<endl;
   //
  //     for(int p=0; p<4; p++){
  //       cout<<ctuple.photon_pt[p]<<"\t"<<ctuple.photon_eta[p]<<"\t"<<ctuple.photon_phi[p]<<"\t"<<ctuple.photon_passLooseId[p]<<endl;
  //       cout<<ctuple.pc_matched[p]<<"\t"<<ctuple.convtracks_pt[p]<<endl;
  //       cout<<"+++++++++++++"<<endl;
  //     }
   //
  //    }
   //
   //
  //  cout<<"====================="<<endl;

    TCanvas *c1 = canvas_data_mc_2d(h2_pass_chf, "PF ChF", "GEN ChF", 200,2, true);
    c1->SaveAs("./h2_chf_"+Label+".png");
    // c1->SaveAs("./Plots/NeutronGun/Smeared/pt_neutron_gun_p2pf_th2f_"+Label+".pdf");
    // TCanvas *c2 = canvas_data_mc_2d(h_pt_st, "GENJet p_{T} ", "Jet p_{T,PF}", 200,2500, true);
    // c2->SaveAs("./Plots/NeutronGun/Smeared/pt_neutron_gun_th2f_"+Label+".png");
    // c2->SaveAs("./Plots/NeutronGun/Smeared/pt_neutron_gun_th2f_"+Label+".pdf");
    //
    TCanvas *c4 = new TCanvas("h_dpt0_pf","h_dpt0_pf",700,700);
    gStyle->SetPadBorderMode(0);
    gStyle->SetOptStat(11111);
    gStyle->SetOptTitle(0);
    c4->cd();
    c4->SetLogy();
    h_pass_chf->GetXaxis()->SetTitle("ChF PF/GEN");
    h_pass_chf->Draw();
    c4->SaveAs("./h_chf"+Label+".png");


    TCanvas *c5 = new TCanvas("h","h",700,700);
    gStyle->SetPadBorderMode(0);
    gStyle->SetOptStat(11111);
    gStyle->SetOptTitle(0);
    c5->cd();
    //h_pass_chf->GetXaxis()->SetTitle("(p_{T,GEN}-p_{T,PF})/p_{T PF}");
    h_dis_chf->Draw();

  return 0;
}
