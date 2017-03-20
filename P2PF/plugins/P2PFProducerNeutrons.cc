//-------------------------------------------------
//
//   Class: P2PFProducerNeutrons
//
//   P2PFProducerNeutrons
//
//
//   Author :
//   G. Flouris               VUB        Jan. 2016
//--------------------------------------------------

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include <FWCore/Framework/interface/ConsumesCollector.h>
#include <FWCore/Framework/interface/one/EDProducer.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>
#include <DataFormats/ParticleFlowCandidate/interface/PFCandidate.h>
#include <DataFormats/HepMCCandidate/interface/GenParticle.h>
#include <DataFormats/Math/interface/deltaR.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include "TRandom.h"
#include "TFile.h"
#include "TH1F.h"

using namespace std;

class P2PFProducerNeutrons: public edm::one::EDProducer<edm::one::SharedResources> {
public:
  P2PFProducerNeutrons(const edm::ParameterSet & pset);
  ~P2PFProducerNeutrons() {}
  void produce(edm::Event & e, const edm::EventSetup& c);
  double Resolution(double pt);
private:
  edm::EDGetToken m_partons, m_particlef;
  TRandom *rnd;// = new TRandom();
  TFile *f005;
  TFile *f0510;
  TFile *f1015;
  TFile *f1520;
  TFile * ftmp;
  //rnd->SetSeed(time(NULL));

};


P2PFProducerNeutrons::P2PFProducerNeutrons(const edm::ParameterSet & pset) {
m_partons      = consumes<vector<reco::GenParticle> >(pset.getParameter<edm::InputTag>("Partons_Source"));
m_particlef    = consumes<vector<reco::PFCandidate> >(pset.getParameter<edm::InputTag>("ParticleFlow_Source"));

produces<vector<reco::PFCandidate> >("particleFlowSIMPs");
rnd = new TRandom();

f005 = TFile::Open("/user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/Resolution005.root");
f0510 = TFile::Open("/user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/Resolution0510.root");
f1015 = TFile::Open("/user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/Resolution1015.root");
f1520 = TFile::Open("/user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/Resolution1520.root");

}


double P2PFProducerNeutrons::Resolution(double pt){
//a + b/(pow(x,c) +d*x)
  double res = 0;
  const double A = 1.37861*pow(10,-2);
  const double B = 2.09447*pow(10,-2);
  const double C = -3.08390*pow(10,-1);
  const double D = 4.27909*pow(10,-4);
  res = A + B/(pow(pt,C) + D*pt);
  return res;

}

void P2PFProducerNeutrons::produce(edm::Event& e, const edm::EventSetup& c) {

  typedef reco::Particle::LorentzVector LorentzVector;

  edm::Handle<vector<reco::GenParticle> > H_partons;
  edm::Handle<vector<reco::PFCandidate> > H_pfcandidate;
  e.getByToken(m_partons, H_partons);
  e.getByToken(m_particlef, H_pfcandidate);

  std::auto_ptr<vector<reco::PFCandidate> > out_particlepf(new vector<reco::PFCandidate>);
  ///PFCandidates
    for (vector<reco::PFCandidate>::const_iterator thepfcands = H_pfcandidate->begin();thepfcands != H_pfcandidate->end(); ++thepfcands){
    //if( thepfcands->pt()>100.) continue;  ///Only in neutron gun
    std::vector<double> dR;
    for (vector<reco::GenParticle>::const_iterator thepartons = H_partons->begin(); thepartons != H_partons->end(); ++thepartons){
       if(abs(thepartons->pdgId())==2112){
         //cout<<thepartons->eta()<<"\t"<<thepartons->phi()<<"\t"<<thepfcands->eta()<<"\t"<<thepfcands->phi()<<endl;
         dR.push_back(deltaR(thepartons->eta(), thepartons->phi(), thepfcands->eta(), thepfcands->phi()));
      }//genParticles
    }
    double mindR=*std::min_element(dR.begin(), dR.end());
    //std::cout<<"MinDr  "<<mindR<<std::endl;
   if(mindR<0.2) continue;
   out_particlepf->push_back(*thepfcands);

  }
  //cout<<endl<<endl;
  LorentzVector tmpPfCand;
  ///Partons
    for (vector<reco::GenParticle>::const_iterator thepartons = H_partons->begin();
    thepartons != H_partons->end(); ++thepartons){
       if(abs(thepartons->pdgId())==2112){


         //double sig = Resolution(thepartons->pt());
         //cout<<thepartons->pt()<<endl;

         double ppt = thepartons->pt();
         //cout<<ppt<<endl;

         ftmp = f005;
         if(thepartons->eta()>0.5 && thepartons->eta()<=1.0) ftmp = f0510;
         if(thepartons->eta()>1.0 && thepartons->eta()<=1.5) ftmp = f1015;
         if(thepartons->eta()>1.5 && thepartons->eta()<=2.0) ftmp = f1520;


         TH1F *tmp = (TH1F*)ftmp->Get("hresol0");
         if(ppt>300. && ppt<400.) tmp = (TH1F*)ftmp->Get("hresol1");
         if(ppt>400. && ppt<500.) tmp = (TH1F*)ftmp->Get("hresol2");
         if(ppt>500. && ppt<600.) tmp = (TH1F*)ftmp->Get("hresol3");
         if(ppt>600. && ppt<700.) tmp = (TH1F*)ftmp->Get("hresol4");
         if(ppt>700. && ppt<800.) tmp = (TH1F*)ftmp->Get("hresol5");
         if(ppt>800. && ppt<900.) tmp = (TH1F*)ftmp->Get("hresol6");
         if(ppt>900. && ppt<1000.) tmp = (TH1F*)ftmp->Get("hresol7");
         if(ppt>1000. && ppt<1100.) tmp = (TH1F*)ftmp->Get("hresol8");
         if(ppt>1100. && ppt<1200.) tmp = (TH1F*)ftmp->Get("hresol9");
         if(ppt>1200. && ppt<1300.) tmp = (TH1F*)ftmp->Get("hresol10");
         if(ppt>1300. && ppt<1400.) tmp = (TH1F*)ftmp->Get("hresol11");
         if(ppt>1400. && ppt<1500.) tmp = (TH1F*)ftmp->Get("hresol12");
         if(ppt>1500. && ppt<1600.) tmp = (TH1F*)ftmp->Get("hresol13");
         if(ppt>1600. && ppt<1700.) tmp = (TH1F*)ftmp->Get("hresol14");
         if(ppt>1700. && ppt<1800.) tmp = (TH1F*)ftmp->Get("hresol15");
         if(ppt>1800. && ppt<1900.) tmp = (TH1F*)ftmp->Get("hresol16");
         if(ppt>1900. && ppt<2000.) tmp = (TH1F*)ftmp->Get("hresol17");
         if(ppt>2000. && ppt<2100.) tmp = (TH1F*)ftmp->Get("hresol18");
         if(ppt>2100. && ppt<2200.) tmp = (TH1F*)ftmp->Get("hresol19");
         if(ppt>2200. && ppt<2300.) tmp = (TH1F*)ftmp->Get("hresol20");
         if(ppt>2300. ) tmp = (TH1F*)ftmp->Get("hresol21");


         //double xrnd = rnd->Gaus(1,sig);

         double xrnd = 1.+tmp->GetRandom();
         //cout<<xrnd<<endl;
         //cout<<"++++++++"<<endl;

         //cout<<thepartons->pt()<<"\t"<<thepartons->eta()<<"\t"<<thepartons->phi()<<"\t"<<sig<<"\t"<<xrnd<<endl;
         tmpPfCand.SetPxPyPzE(thepartons->px()* xrnd,thepartons->py()* xrnd,thepartons->pz()* xrnd,thepartons->energy() *xrnd); //neutron gun
         //tmpPfCand.SetPxPyPzE(thepartons->px(),thepartons->py(),thepartons->pz(),thepartons->energy()); //neutron gun


	       out_particlepf->push_back(reco::PFCandidate(0,tmpPfCand,reco::PFCandidate::ParticleType::h0));

      }//genParticles
    }


  //PFCandidate( Charge q, const LorentzVector & p4, ParticleType particleId );
  e.put(out_particlepf,"particleFlowSIMPs");
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(P2PFProducerNeutrons);
