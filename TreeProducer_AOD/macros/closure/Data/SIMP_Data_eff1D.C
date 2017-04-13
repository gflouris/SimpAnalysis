  #include <map>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <TMath.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TROOT.h>
#include <TChain.h>



TCanvas *canvas_eff(TString label, int bins, double eff_pt[][11], double err_eff_pt[][11]){

  double chf_cuts[11] = {0.5, 0.4, 0.3, 0.2, 0.15, 0.1, 0.05, 0.04, 0.03, 0.02, 0.01};
  double zero[11] = {0};


	TCanvas *c1 = new TCanvas(label, label);
	c1->cd();
	TGraphErrors *firstptbin = new TGraphErrors(11, chf_cuts, eff_pt[0], zero, err_eff_pt[0]);
	firstptbin->GetXaxis()->SetTitle("CHF cut");
	firstptbin->SetTitle("CHF cut efficiency");
	firstptbin->GetYaxis()->SetTitle("efficiency");
	firstptbin->SetMarkerStyle(20);
	firstptbin->Draw("AP");
	for (int i = 1; i < bins; i++){
		TGraphErrors *otherptbin = new TGraphErrors(11, chf_cuts, eff_pt[i], zero, err_eff_pt[i]);
		otherptbin->SetMarkerStyle(20);
		otherptbin->SetMarkerColor(i+1);
		otherptbin->Draw("P");
	}

return c1;
}

void SIMP_Data_eff1D(){

  TChain * chain = new TChain("treeCorr/SimpAnalysis");

  for(int f=1; f<100; f++){

   stringstream a;
   a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016D_rereco_AOD/170323_130420/0000/Data_AOD_test_";

    a<<f; a<<".root";
    chain->Add((a.str()).c_str());

  }


	std::cout<<"TChains ready"<<std::endl;

  double jet_pt[8], jet_eta[8], jet_phi[8],  jet_efrac_ch_Had[8], jet_efrac_ch_EM[8], jet_efrac_ch_Mu[8], CHEF_jet[8];
	int dijet_170, vtx_N;
	double pswgt_dijet_170;

	double total_pt[9] = {0};
	double total_eta[4] = {0};
  double total_vtx[9] = {0};

	double chf_cuts[11] = {0.5, 0.4, 0.3, 0.2, 0.15, 0.1, 0.05, 0.04, 0.03, 0.02, 0.01};
  double vtx_bins[10] = {0, 10, 15, 20, 25, 30, 35, 40, 50, 60};
	double pt_bins[10] = {250, 275, 300, 350, 400, 450, 550, 700, 900, 10000};
	double eta_bins[5] = {0, 0.5, 1.0, 1.5, 2.0};

	double passed_pt[9][11] = {{0}};
	double passed_eta[4][11] = {{0}};
  double passed_vtx[9][11] = {{0}};

	double err_pt_passed[9][11] = {{0}};
	double err_eta_passed[4][11] = {{0}};
  double err_vtx_passed[9][11] = {{0}};

	double eff_pt[9][11], eff_eta[4][11], eff_vtx[9][11];
	double err_eff_pt[9][11], err_eff_eta[9][11], err_eff_vtx[9][11];
	double zero[11] = {0};



  TFile *output = new TFile("eff1D_Data_Rereco.root", "RECREATE");

	chain->SetBranchAddress("jet_pt", &jet_pt);
	chain->SetBranchAddress("jet_eta", &jet_eta);
	chain->SetBranchAddress("jet_phi", &jet_phi);
  chain->SetBranchAddress("vtx_N", &vtx_N);
	chain->SetBranchAddress("jet_efrac_ch_Had", &jet_efrac_ch_Had);
	chain->SetBranchAddress("jet_efrac_ch_EM", &jet_efrac_ch_EM);
	chain->SetBranchAddress("jet_efrac_ch_Mu", &jet_efrac_ch_Mu);
  chain->SetBranchAddress("HLT_DiCentralPFJet170", &dijet_170);
  chain->SetBranchAddress("pswgt_dijet_170", &pswgt_dijet_170);

	Int_t Nentries = chain->GetEntries();
	std::cout<<"Processing "<<Nentries<<"entries"<<std::endl;

	for(Int_t entry = 0; entry < Nentries; ++entry){
		if(entry%1000000==0) std::cout<<"processed "<<entry/1000000<<"M events"<<std::endl;
		chain->GetEntry(entry);





		double deltajet_phi = jet_phi[0] - jet_phi[1];
		if(deltajet_phi > TMath::Pi()) deltajet_phi -= 2*TMath::Pi();
		if(deltajet_phi < -TMath::Pi()) deltajet_phi += 2*TMath::Pi();
		deltajet_phi = fabs(deltajet_phi);

		for (int i = 0; i < 8; i++){
			CHEF_jet[i] = jet_efrac_ch_Had[i]+jet_efrac_ch_EM[i]+jet_efrac_ch_Mu[i];
		}

		output->cd();

		if (dijet_170 == 1 && jet_pt[0] > 250 && jet_pt[1] > 250 && fabs(jet_eta[0]) < 2.0 && fabs(jet_eta[1]) < 2.0 && deltajet_phi > 2.0){

			if(CHEF_jet[0] > 0.5){
				for (int i = 0; i < 9; i++){
					if (jet_pt[1]>pt_bins[i] && jet_pt[1]<pt_bins[i+1]){
						total_pt[i] += pswgt_dijet_170;
						for(int j = 0; j < 11; j++){
							if (CHEF_jet[1]<chf_cuts[j]){
								passed_pt[i][j] += pswgt_dijet_170;
								err_pt_passed[i][j] += pswgt_dijet_170*pswgt_dijet_170;
							}else err_pt_failed[i][j] += pswgt_dijet_170*pswgt_dijet_170;
						}
					}
				}
				for (int i = 0; i < 4; i++){
					if (jet_eta[1]>eta_bins[i] && jet_eta[1]<eta_bins[i+1]){
						total_eta[i] += pswgt_dijet_170;
						for(int j = 0; j < 11; j++){
							if (CHEF_jet[1]<chf_cuts[j]){
								passed_eta[i][j] += pswgt_dijet_170;
								err_eta_passed[i][j] += pswgt_dijet_170*pswgt_dijet_170;
							}else err_eta_failed[i][j] += pswgt_dijet_170*pswgt_dijet_170;
						}
					}
				}
        for (int i = 0; i < 9; i++){
          //cout<<vtx_N<<"\t"<<vtx_bins[i]<<"\t"<<vtx_bins[i+1]<<endl;
					if (vtx_N>=vtx_bins[i] && vtx_N<vtx_bins[i+1]){
						total_vtx[i] += pswgt_dijet_170;
						for(int j = 0; j < 11; j++){
							if (CHEF_jet[1]<chf_cuts[j]){
								passed_vtx[i][j] += pswgt_dijet_170;
								err_vtx_passed[i][j] += pswgt_dijet_170*pswgt_dijet_170;
							}else err_vtx_failed[i][j] += pswgt_dijet_170*pswgt_dijet_170;
						}
					}
				}
			}///if(CHEF_jet[0] > 0.5)
			else if(CHEF_jet[1] > 0.5){
				for (int i = 0; i < 9; i++){
					if (jet_pt[0]>pt_bins[i] && jet_pt[0]<pt_bins[i+1]){
						total_pt[i] += pswgt_dijet_170;
						for(int j = 0; j < 11; j++){
							if (CHEF_jet[0]<chf_cuts[j]){
								passed_pt[i][j] += pswgt_dijet_170;
								err_pt_passed[i][j] += pswgt_dijet_170*pswgt_dijet_170;
							}else err_pt_failed[i][j] += pswgt_dijet_170*pswgt_dijet_170;
						}
					}
				}
				for (int i = 0; i < 4; i++){
					if (jet_eta[0]>eta_bins[i] && jet_eta[0]<eta_bins[i+1]){
						total_eta[i] += pswgt_dijet_170;
						for(int j = 0; j < 11; j++){
							if (CHEF_jet[0]<chf_cuts[j]){
								passed_eta[i][j] += pswgt_dijet_170;
								err_eta_passed[i][j] += pswgt_dijet_170*pswgt_dijet_170;
							}else err_eta_failed[i][j] += pswgt_dijet_170*pswgt_dijet_170;
						}
					}
				}
        for (int i = 0; i < 9; i++){
					if (vtx_N>=vtx_bins[i] && vtx_N<vtx_bins[i+1]){
						total_vtx[i] += pswgt_dijet_170;
						for(int j = 0; j < 11; j++){
							if (CHEF_jet[0]<chf_cuts[j]){
								passed_vtx[i][j] += pswgt_dijet_170;
								err_vtx_passed[i][j] += pswgt_dijet_170*pswgt_dijet_170;
							}else err_vtx_failed[i][j] += pswgt_dijet_170*pswgt_dijet_170;
						}
					}
				}
			}//if(CHEF_jet[1] > 0.5){
		}
	}

	for (int j = 0; j < 11; j++){
		for (int i = 0; i < 9; i++){
			double tot = (double)total_pt[i];
			double passed = (double)passed_pt[i][j];
			err_pt_passed[i][j] = TMath::Sqrt(err_pt_passed[i][j]);
			err_pt_failed[i][j] = TMath::Sqrt(err_pt_failed[i][j]);
			eff_pt[i][j] = passed/tot;
			err_eff_pt[i][j] = pow(tot, -2)*TMath::Sqrt(pow(tot - passed, 2)*pow(err_pt_passed[i][j], 2) + (pow(passed, 2)*pow(err_pt_failed[i][j], 2)));
			if (passed_pt[i][j] != 0){
				red_pt[i][j] = tot/(double)passed;
				err_red_pt[i][j] = pow(passed, -2)*TMath::Sqrt(pow(tot - passed, 2)*pow(err_pt_passed[i][j], 2) + (pow(passed, 2)*pow(err_pt_failed[i][j], 2)));
			}
			else{
				red_pt[i][j] = 0;
				err_red_pt[i][j] = 0;
			}
		}
	}
  for (int j = 0; j < 11; j++){
		for (int i = 0; i < 9; i++){
			double tot = (double)total_vtx[i];
			double passed = (double)passed_vtx[i][j];
			err_vtx_passed[i][j] = TMath::Sqrt(err_vtx_passed[i][j]);
			err_vtx_failed[i][j] = TMath::Sqrt(err_vtx_failed[i][j]);
			eff_vtx[i][j] = passed/tot;
			err_eff_vtx[i][j] = pow(tot, -2)*TMath::Sqrt(pow(tot - passed, 2)*pow(err_vtx_passed[i][j], 2) + (pow(passed, 2)*pow(err_vtx_failed[i][j], 2)));

		}
	}
		for (int j = 0; j < 11; j++){
		for (int i = 0; i < 4; i++){
			double tot = (double)total_eta[i];
			double passed = (double)passed_eta[i][j];
      if(tot==0) continue;
			err_eta_passed[i][j] = TMath::Sqrt(err_eta_passed[i][j]);
			err_eta_failed[i][j] = TMath::Sqrt(err_eta_failed[i][j]);
			eff_eta[i][j] = passed/tot;
			err_eff_eta[i][j] = pow(tot, -2)*TMath::Sqrt(pow(tot - passed, 2)*pow(err_eta_passed[i][j], 2) + (pow(passed, 2)*pow(err_eta_failed[i][j], 2)));
		}
	}

	TCanvas *c1 = canvas_eff("efficiency_pt", 11, eff_pt,err_eff_pt);
  TCanvas *c2 = canvas_eff("efficiency_eta", 4,  eff_eta, err_eff_eta);
  TCanvas *c3 = canvas_eff("efficiency_vtx", 9,  eff_vtx, eff_vtx);

    //
    // new TCanvas("efficiency_pt", "efficiency_pt");
  	// c1->cd();
  	// TGraphErrors *firstptbin = new TGraphErrors(11, chf_cuts, eff_pt[0], zero, err_eff_pt[0]);
    // firstptbin->GetXaxis()->SetTitle("CHF cut");
  	// firstptbin->SetTitle("CHF cut efficiency");
  	// firstptbin->GetYaxis()->SetTitle("efficiency");
  	// firstptbin->SetMarkerStyle(20);
  	// firstptbin->Draw("AP");
  	// for (int i = 1; i < 9; i++){
  	// 	TGraphErrors *otherptbin = new TGraphErrors(11, chf_cuts, eff_pt[i], zero, err_eff_pt[i]);
  	// 	otherptbin->SetMarkerStyle(20);
  	// 	otherptbin->SetMarkerColor(i+1);
  	// 	otherptbin->Draw("P");
  	// }
  //
	// TCanvas *c2 = new TCanvas("rejection_pt", "rejection_pt");
	// c2->cd();
	// TGraphErrors *firstptbin2 = new TGraphErrors(11, chf_cuts, red_pt[0], zero, err_red_pt[0]);
	// firstptbin2->SetTitle("CHF cut rejection factor");
	// firstptbin2->GetXaxis()->SetTitle("CHF cut");
	// firstptbin2->GetYaxis()->SetTitle("rejection factor");
	// firstptbin2->SetMarkerStyle(20);
	// firstptbin2->Draw("AP");
	// for (int i = 1; i < 9; i++){
	// 	TGraphErrors *otherptbin2 = new TGraphErrors(11, chf_cuts, red_pt[i], zero, err_red_pt[i]);
	// 	otherptbin2->SetMarkerStyle(20);
	// 	otherptbin2->SetMarkerColor(i+1);
	// 	otherptbin2->Draw("P");
	// }
  //
	// TCanvas *c3 = new TCanvas("efficiency_eta", "efficiency_eta");
	// c3->cd();
	// TGraphErrors *firstetabin = new TGraphErrors(11, chf_cuts, eff_eta[0], zero, err_eff_eta[0]);
	// firstetabin->SetTitle("CHF cut efficiency");
	// firstetabin->GetXaxis()->SetTitle("CHF cut");
	// firstetabin->GetYaxis()->SetTitle("efficiency");
	// firstetabin->SetMarkerStyle(20);
	// firstetabin->Draw("AP");
	// for (int i = 1; i < 4; i++){
	// 	TGraphErrors *otheretabin = new TGraphErrors(11, chf_cuts, eff_eta[i], zero, err_eff_eta[i]);
	// 	otheretabin->SetMarkerStyle(20);
	// 	otheretabin->SetMarkerColor(i+1);
	// 	otheretabin->Draw("P");
	// }
  //
	// TCanvas *c4 = new TCanvas("rejection_eta", "rejection_eta");
	// c4->cd();
	// TGraphErrors *firstetabin2 = new TGraphErrors(11, chf_cuts, red_eta[0], zero, err_red_eta[0]);
	// firstetabin2->SetTitle("CHF cut rejection factor");
	// firstetabin2->GetXaxis()->SetTitle("CHF cut");
	// firstetabin2->GetYaxis()->SetTitle("rejection factor");
	// firstetabin2->SetMarkerStyle(20);
	// firstetabin2->Draw("AP");
	// for (int i = 1; i < 4; i++){
	// 	TGraphErrors *otheretabin2 = new TGraphErrors(11, chf_cuts, red_eta[i], zero, err_red_eta[i]);
	// 	otheretabin2->SetMarkerStyle(20);
	// 	otheretabin2->SetMarkerColor(i+1);
	// 	otheretabin2->Draw("P");
	// }
  //
  //
  //
  // TCanvas *c5 = new TCanvas("efficiency_vtx", "efficiency_vtx");
	// c5->cd();
	// TGraphErrors *firstareabin = new TGraphErrors(11, chf_cuts, eff_vtx[0], zero, err_eff_vtx[0]);
	// firstareabin->SetTitle("CHF cut efficiency");
	// firstareabin->GetXaxis()->SetTitle("CHF cut");
	// firstareabin->GetYaxis()->SetTitle("efficiency");
	// firstareabin->SetMarkerStyle(20);
	// firstareabin->Draw("AP");
	// for (int i = 1; i < 9; i++){
	// 	TGraphErrors *otherareabin = new TGraphErrors(11, chf_cuts, eff_vtx[i], zero, err_eff_vtx[i]);
	// 	otherareabin->SetMarkerStyle(20);
	// 	otherareabin->SetMarkerColor(i+1);
	// 	otherareabin->Draw("P");
	// }
  //


	output->Append(c1);
	output->Append(c2);
	output->Append(c3);
	// output->Append(c4);
  // output->Append(c5);

  output->Write();
  output->Close();
}
