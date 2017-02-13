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
  //rnd->SetSeed(time(NULL));

};


P2PFProducerNeutrons::P2PFProducerNeutrons(const edm::ParameterSet & pset) {
m_partons      = consumes<vector<reco::GenParticle> >(pset.getParameter<edm::InputTag>("Partons_Source"));
m_particlef    = consumes<vector<reco::PFCandidate> >(pset.getParameter<edm::InputTag>("ParticleFlow_Source"));

produces<vector<reco::PFCandidate> >("particleFlowSIMPs");
rnd = new TRandom();
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


         double sig = Resolution(thepartons->pt());
         double xrnd = rnd->Gaus(1,sig);

         //cout<<thepartons->pt()<<"\t"<<thepartons->eta()<<"\t"<<thepartons->phi()<<"\t"<<sig<<"\t"<<xrnd<<endl;
         //tmpPfCand.SetPxPyPzE(thepartons->px()* xrnd,thepartons->py()* xrnd,thepartons->pz()* xrnd,thepartons->energy()); //neutron gun
         tmpPfCand.SetPxPyPzE(thepartons->px(),thepartons->py(),thepartons->pz(),thepartons->energy()); //neutron gun


	       out_particlepf->push_back(reco::PFCandidate(0,tmpPfCand,reco::PFCandidate::ParticleType::h0));
      }//genParticles
    }


  //PFCandidate( Charge q, const LorentzVector & p4, ParticleType particleId );
  e.put(out_particlepf,"particleFlowSIMPs");
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(P2PFProducerNeutrons);
